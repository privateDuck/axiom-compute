#pragma once

#include <vector>
#include <variant>
#include <string>
#include <format>
#include <unordered_map>
#include <arrow/c/bridge.h>
#include <arrow/api.h>
//#include <duckdb/duckdb.hpp>
#include <duckdb/duckdb.h>


enum class SematicType {
	NUMERIC,
	NOMINAL,
	ORDINAL,
	TEMPORAL
};

struct ColumnMeta {
	std::string name;
	std::string db_type;
	SematicType sematic_type;
};

struct DFMeta {
	std::string view_name;
	std::vector<ColumnMeta> columns;

	DFMeta() = default;
	explicit DFMeta(const uint32_t id) : view_name("view_" + std::to_string(id)) {}
	DFMeta(const uint32_t id, const std::vector<ColumnMeta>& cols)
		: view_name(std::format("view_{}", id)), columns(cols) {
	}

	void AddColumn(const ColumnMeta& col_meta) {
		columns.push_back(col_meta);
	}

	void DropColumn(const std::string& col_name) {
		
	}

	const ColumnMeta* getCol(const std::string& name) const {
		for (const auto& c : columns) if (c.name == name) return &c;
		return nullptr;
	}
};

struct ColumnInfo {
	std::string name;
	std::string type;
	bool is_numeric;
};

using NodeData = DFMeta; // std::string; // Represents a view name in DuckDB
using NodeVector = std::vector<NodeData>;

struct DBContext {
	//duckdb::Connection& conn;
	//explicit DBContext(duckdb::Connection& connection) : conn(connection) {}
	
	void ExecuteQuery(const std::string& query) {
		auto result = conn.Query(query);
		if (result->HasError()) {
			throw std::runtime_error("Query failed: " + result->GetError());
		}

		auto res = conn.Query("SELECT COUNT(*) FROM sqlite_master;");
		duckdb_database db;
		duckdb_connection con;
		duckdb_open(nullptr, &db);
		duckdb_connect(db, &con);

		std::shared_ptr<arrow::Table> arrow;
		duckdb_arrow_scan(con, "table", arrow)
	}

	std::vector<ColumnInfo> GetTableSchema(const std::string& view_name) {
		std::vector<ColumnInfo> columns;

		auto result = conn.Query("PRAGMA table_info('" + view_name + "')");

		for (auto& row : *result) {
			std::string name = row.GetValue<std::string>(1); // col 1: name
			std::string type = row.GetValue<std::string>(2); // col 2: type

			bool is_num = (type == "DOUBLE" || type == "FLOAT" ||
				type == "BIGINT" || type == "INTEGER");

			columns.push_back({ name, type, is_num });
		}
		return columns;
	}
};


struct InjectionNode {
public:
	InjectionNode(const uint32_t id, const std::string& dataFile, const DFMeta& metadata) : _id(id), _dataFile(dataFile), metadata(metadata) {}

	NodeVector compute(const NodeVector& inputs, DBContext& ctx) {
		NodeData output = NodeData(_id);

		ctx.ExecuteQuery("DROP VIEW IF EXISTS " + output.view_name);

		// Uses read_csv_auto for automatic type inference
		std::string sql = std::format(
			"CREATE VIEW {} AS SELECT * FROM read_csv_auto('{}')",
			output.view_name, _dataFile
		);

		ctx.ExecuteQuery(sql);

		return { output };
	}

private:
	uint32_t _id;
	std::string _dataFile;
	DFMeta metadata;
};


struct ColumnSelectorNode {
	uint32_t _id;
	std::vector<std::string> selection;

	explicit ColumnSelectorNode(uint32_t id, const std::vector<std::string>& selection) : _id(id), selection(std::move(selection)) {}

	NodeVector compute(const NodeVector& inputs, DBContext& ctx) {

		NodeData input_view = inputs[0];
		NodeData output_view = NodeData(_id);
		std::unordered_set<std::string> selected_columns;
		selected_columns.reserve(input_view.columns.size()); // At max all columns

		for (const auto& sc : selection) {
			if (sc == "NUMERIC") {
				// Select all numeric columns
				for (const auto& col : input_view.columns) {
					if (col.sematic_type == SematicType::NUMERIC) {
						selected_columns.insert(col.name);
					}
				}
			}
			else if (sc == "CATEGORICAL") {
				// Select all categorical columns
				for (const auto& col : input_view.columns) {
					if (col.sematic_type == SematicType::NOMINAL || col.sematic_type == SematicType::ORDINAL) {
						selected_columns.insert(col.name);
					}
				}
			}
			else if (sc == "NOMINAL") {
				// Select all nominal columns
				for (const auto& col : input_view.columns) {
					if (col.sematic_type == SematicType::NOMINAL) {
						selected_columns.insert(col.name);
					}
				}
			}
			else if (sc == "NOMINAL") {
				// Select all ordinal columns
				for (const auto& col : input_view.columns) {
					if (col.sematic_type == SematicType::ORDINAL) {
						selected_columns.insert(col.name);
					}
				}
			}
			else {
				for (const auto& col : input_view.columns) {
					if (col.name == sc) {
						selected_columns.insert(col.name);
						break;
					}
				}
			}
		}

		std::string select_clause;
	}
};


struct ScalerNode {
	uint32_t id_;

	explicit ScalerNode(uint32_t id) : id_(id) {}

	std::vector<NodeData> compute(const std::vector<NodeData>& inputs, DBContext& ctx) {

		NodeData input_view = inputs[0];
		NodeData output_view = NodeData(id_, inputs[0].columns);
		//auto columns = ctx.GetTableSchema(input_view);

		std::string select_clause;
		for (size_t i = 0; i < inputs[0].columns.size(); ++i) {
			const auto& col = inputs[0].columns[i];

			if (col.sematic_type == SematicType::NUMERIC) {
				// (col - Mean) / StdDev
				select_clause += std::format(
					"({0} - AVG({0}) OVER()) / NULLIF(STDDEV({0}) OVER(), 0) AS {0}",
					col.name
				);
			}
			else {
				// Pass non-numeric
				select_clause += col.name;
			}

			if (i < inputs[0].columns.size() - 1) select_clause += ", ";
		}

		ctx.ExecuteQuery("DROP VIEW IF EXISTS " + output_view.view_name);

		std::string sql = std::format(
			"CREATE VIEW {} AS SELECT {} FROM {}",
			output_view.view_name, select_clause, input_view.view_name
		);

		ctx.ExecuteQuery(sql);

		return { output_view };
	}
};
