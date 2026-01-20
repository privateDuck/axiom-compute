#pragma once

#include <arrow/api.h>
#include <arrow/csv/api.h>
#include <arrow/io/api.h>
#include <string>
#include <memory>
#include <vector>
#include <absl/container/flat_hash_map.h>
#include "FastHash.hpp"

struct DataColumn {
	std::string name;
	std::shared_ptr<arrow::DataType> type;
	std::shared_ptr<arrow::Array> data;
	uint64_t null_count;

	bool is_null(size_t i) const {
		if (null_count == 0) return false;
		const uint8_t* bitmap = data->null_bitmap_data();
		return (bitmap[i / 8] >> (i % 8)) & 1;
	}
};


class IMDataset {
private:
	absl::flat_hash_map<std::string, size_t> column_map;
	absl::flat_hash_map<std::string, FlatMap> string_maps;
	std::vector<DataColumn> columns;
	uint64_t rows;
public:
	IMDataset() = default;
	void ReadIntoFromFile(const std::string& filename);
	const DataColumn& GetColumn(size_t index) const;
	const DataColumn& GetColumn(const std::string& name) const;
	const uint64_t size() const { return rows; }
};


class DataIngester {
public:
	DataIngester() = delete;

	static std::shared_ptr<arrow::Table> GetArrowTableFromCSV(const std::string& file) {
		arrow::io::IOContext io_context = arrow::io::default_io_context();
		auto input_res = arrow::io::ReadableFile::Open(file);
		if (!input_res.ok()) {
			throw std::runtime_error("Failed to Open File");
		}
		std::shared_ptr<arrow::io::InputStream> input = *input_res;
		
		auto read_opt = arrow::csv::ReadOptions::Defaults();
		auto parse_options = arrow::csv::ParseOptions::Defaults();
		auto convert_options = arrow::csv::ConvertOptions::Defaults();

		read_opt.autogenerate_column_names = true;
		read_opt.use_threads = true;

		auto maybe_reader = arrow::csv::TableReader::Make(
			io_context,
			input,
			read_opt,
			parse_options,
			convert_options
		);

		if (!maybe_reader.ok()) {
			throw std::runtime_error("Failed to read file");
		}
		std::shared_ptr<arrow::csv::TableReader> reader = *maybe_reader;

		auto table_res = reader->Read();
		if (!table_res.ok()) {
			throw std::runtime_error("Failed to read table: " + table_res.status().ToString());
		}
		auto single_chunk_res = (*table_res)->CombineChunks();

		if (!single_chunk_res.ok()) {
			throw std::runtime_error("Failed to combine chunks: " + table_res.status().ToString());
		}
		
		return *single_chunk_res;
	}

	static void CleanUpStringArray(std::shared_ptr<arrow::StringArray> array) {
		for (size_t i = 0; i < array->length(); i++)
		{
			std::string_view sv = array->GetView(i);
		}
	}
};