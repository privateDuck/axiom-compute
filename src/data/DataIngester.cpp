#include "DataIngester.hpp"

void IMDataset::ReadIntoFromFile(const std::string& filename)
{
	std::shared_ptr<arrow::Table> table = DataIngester::GetArrowTableFromCSV(filename);
	auto schema = table->schema();
	uint64_t cols = table->num_columns();
	rows = table->num_rows();

	for (uint64_t i = 0; i < cols; ++i)
	{
		auto field = schema->field(i);
		std::string name = field->name();
		std::shared_ptr<arrow::DataType> type = field->type();

		std::shared_ptr<arrow::Array> col_data = table->column(i)->chunk(0);
		uint64_t nullC = col_data->null_count();


		auto type_id = type->id();

		switch (type_id)
		{
		case arrow::Type::NA:
			break;
		case arrow::Type::BOOL:
			break;
		case arrow::Type::INT64:
			break;
		case arrow::Type::FLOAT:
		case arrow::Type::DOUBLE:
			break;
		case arrow::Type::STRING:
			break;
		case arrow::Type::BINARY:
			break;
		case arrow::Type::DATE32:
			break;
		case arrow::Type::TIMESTAMP:
			break;
		case arrow::Type::TIME32:
			break;
		case arrow::Type::STRING_VIEW:
			break;
		default:
			break;
		}




		DataColumn col{
			.name = name,
			.type = type,
			.data = col_data,
			.null_count = nullC
		};
	}
}
