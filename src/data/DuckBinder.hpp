#pragma once

#include "DataFrame.hpp"
#include <cstring>


struct BindData {
    DataFrame* table_ptr; // Non-owning pointer to the DataFrame
};

// Scanner initialization data
struct InitData {
    size_t current_row;
    size_t total_rows;
};

// This binding function binds our columns to the database table schema
void col_bind_func(duckdb_bind_info info) {

    duckdb_value ptr_val = duckdb_bind_get_parameter(info, 0);
    int64_t ptr_int = duckdb_get_int64(ptr_val);
    duckdb_destroy_value(&ptr_val);

    DataFrame* table = reinterpret_cast<DataFrame*>(ptr_int);

    // Define the schema for DuckDB
    for (size_t i = 0; i < table->ColCount(); ++i) {
        auto type_id = table->GetColumn(i)->GetType();
        duckdb_logical_type dtype = nullptr;

        switch (type_id) {
        case ColType::INT64: dtype = duckdb_create_logical_type(DUCKDB_TYPE_BIGINT); break;
        case ColType::FLOAT: dtype = duckdb_create_logical_type(DUCKDB_TYPE_FLOAT); break;
        case ColType::VARCHAR: dtype = duckdb_create_logical_type(DUCKDB_TYPE_VARCHAR); break;
        default: break;
        }

        if (dtype) {
            duckdb_bind_add_result_column(info, table->GetName(i).c_str(), dtype);
            duckdb_destroy_logical_type(&dtype);
        }
    }

    // Store the table pointer for the execution phase
    // We have to allocate BindData on heap. 
    // DuckDB will (Hopefully) free it via the destroy callback
    BindData* bind_data = new BindData{ table };
    duckdb_bind_set_bind_data(info, bind_data, [](void* p) { delete (BindData*)p; });

    // Cardinality is required for query optimizer ?
    duckdb_bind_set_cardinality(info, table->RowCount(), true);
}

// Reset the cursor for a new query
void cursor_init_func(duckdb_init_info info) {
    // Retrieve bind data to get row count
    BindData* bind_data = (BindData*)duckdb_init_get_bind_data(info);

    InitData* init_data = new InitData;
    init_data->current_row = 0;
    init_data->total_rows = bind_data->table_ptr->RowCount();

    duckdb_init_set_init_data(info, init_data, [](void* p) { delete (InitData*)p; });
}

// Copy data from our DataFrame into DuckDB's output chunk
void mem_scan_func(duckdb_function_info info, duckdb_data_chunk output) {
    BindData* bind_data = (BindData*)duckdb_function_get_bind_data(info);
    InitData* init_data = (InitData*)duckdb_function_get_local_init_data(info); // local_init for thread safety

    if (init_data->current_row >= init_data->total_rows) {
        // Signal completion
        return;
    }

    // Compute how many rows to copy this time
    idx_t remaining = init_data->total_rows - init_data->current_row;
    idx_t max_size = duckdb_vector_size();
    idx_t copy_count = (remaining < max_size) ? remaining : max_size;

    duckdb_data_chunk_set_size(output, copy_count);

    // Copy loop
    DataFrame* table = bind_data->table_ptr;
    idx_t col_count = duckdb_data_chunk_get_column_count(output);

    // Duckdb_data_chunk_get_column_count includes projected columns only? 
    // Actually, DuckDB handles projection pushdown automatically or we query indices.
    // For simplicity, we assume strict column ordering here or use `duckdb_function_get_column_index`.

    // We should check which columns DuckDB actually wants
    // But scan functions often just fill everything and DuckDB filters later.

    for (idx_t col_idx = 0; col_idx < col_count; ++col_idx) {
        duckdb_vector out_vec = duckdb_data_chunk_get_vector(output, col_idx);
        auto& src_col_wrapper = table->GetColumn(col_idx);

        void* dest_ptr = duckdb_vector_get_data(out_vec);

        if (src_col_wrapper->GetType() == ColType::INT64) {
            auto* src_col = static_cast<Column<int64_t>*>(src_col_wrapper.get());
            const int64_t* src_ptr = src_col->GetData().data() + init_data->current_row;
            memcpy(dest_ptr, src_ptr, copy_count * sizeof(int64_t));
        }
        else if (src_col_wrapper->GetType() == ColType::FLOAT) {
            auto* src_col = static_cast<Column<float>*>(src_col_wrapper.get());
            const float* src_ptr = src_col->GetData().data() + init_data->current_row;
            memcpy(dest_ptr, src_ptr, copy_count * sizeof(float));
        }
        else if (src_col_wrapper->GetType() == ColType::VARCHAR) {
            // Strings cannot use memcpy because DuckDB has a specific string format
            auto* src_col = static_cast<Column<std::string>*>(src_col_wrapper.get());
            auto& src_vec = src_col->GetData();

            // We still have to iterate over the data for strings
            for (idx_t i = 0; i < copy_count; ++i) {
                const std::string& str = src_vec[init_data->current_row + i];
                duckdb_vector_assign_string_element(out_vec, i, str.c_str());
            }
        }
    }

    // Advance Cursor
    init_data->current_row += copy_count;
}


static void RegisterScanFunction(duckdb_connection conn, const char* func_name) {
    duckdb_table_function func = duckdb_create_table_function();
    duckdb_table_function_set_name(func, func_name);

    // Here we are passing the pointer to the underlying DataFrame object as a BIGINT (int64)
    duckdb_logical_type ptr_type = duckdb_create_logical_type(DUCKDB_TYPE_BIGINT);
    duckdb_table_function_add_parameter(func, ptr_type);
    duckdb_destroy_logical_type(&ptr_type);

    // Set Callbacks
    duckdb_table_function_set_bind(func, col_bind_func);
    duckdb_table_function_set_init(func, cursor_init_func); // main init
    duckdb_table_function_set_local_init(func, cursor_init_func); // thread-local init (required)
    duckdb_table_function_set_function(func, mem_scan_func);

    // Register
    duckdb_state state = duckdb_register_table_function(conn, func);
    duckdb_destroy_table_function(&func);

    if (state == DuckDBError) throw std::runtime_error("Failed to register scan function");
}
