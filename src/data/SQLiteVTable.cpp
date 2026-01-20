
#include "SQLiteVTable.hpp"
#include <sqlite/sqlite3.h>
#include <vector>
#include <string>
#include <format>

struct xVTable {
	sqlite3_vtab base; // Base class - must be first
	MatrixData* matrix; // Pointer to matrix data
};


struct xVCursor {
	sqlite3_vtab_cursor base; // Base class - must be first
	int row_index; // Current row index
};

int xConnect(sqlite3* db, void* pAux,
	const int argc, const char* const* argv,
	sqlite3_vtab** ppVTab, char** pzErr) 
{
	xVTable* pTab = new xVTable();
	MatrixData* pMatrix = static_cast<MatrixData*>(pAux);
	pTab->matrix = pMatrix;

	std::string sql = "CREATE TABLE x(";
	for (const auto& col_name : pMatrix->column_names) {
		sql += std::format("{} REAL, ", col_name);
	}
	sql = sql.substr(0, sql.size() - 2); // Remove last comma
	sql += ")";
	
	int result = sqlite3_declare_vtab(db, sql.c_str());

	if (result != SQLITE_OK) {
		delete pTab;
		*pzErr = sqlite3_mprintf("Failed to declare virtual table: %s", sqlite3_errmsg(db));
		return result;
	}

	*ppVTab = &pTab->base;

	return SQLITE_OK;
}

int xDisconnect(sqlite3_vtab* pVTab) 
{
	delete (xVTable*)pVTab;
	return SQLITE_OK;
}

int xOpen(sqlite3_vtab* pVTab, sqlite3_vtab_cursor** ppCursor) 
{
	xVCursor* pCur = new xVCursor();
	pCur->row_index = 0; // Initialize before first row
	*ppCursor = &pCur->base;
	return SQLITE_OK;
}

int xClose(sqlite3_vtab_cursor* cur) 
{
	delete (xVCursor*)cur;
	return SQLITE_OK;
}

int xNext(sqlite3_vtab_cursor* cur) 
{
	((xVCursor*)cur)->row_index++;
	return SQLITE_OK;
}

int xEof(sqlite3_vtab_cursor* cur) 
{
	xVCursor* pCur = (xVCursor*)cur;
	xVTable* pTab = (xVTable*)cur->pVtab;
	return pCur->row_index >= pTab->matrix->rows;
}

int xFilter(sqlite3_vtab_cursor* cur, int idxNum, const char* idxStr,
	int argc, sqlite3_value** argv) {
	((xVCursor*)cur)->row_index = 0;
	return SQLITE_OK;
}

int xColumn(sqlite3_vtab_cursor* cur, sqlite3_context* ctx, int col_idx) {
	xVCursor* pCur = (xVCursor*)cur;
	xVTable* pTab = (xVTable*)cur->pVtab;

	int row = pCur->row_index;
	int col = col_idx;
	int width = pTab->matrix->cols;

	float value = pTab->matrix->data_ptr[row * width + col];

	sqlite3_result_double(ctx, static_cast<double>(value));

	return SQLITE_OK;
}

int xRowid(sqlite3_vtab_cursor* cur, sqlite3_int64* pRowid) {
	xVCursor* pCur = (xVCursor*)cur;
	*pRowid = static_cast<sqlite3_int64>(pCur->row_index);
	return SQLITE_OK;
}

int xUpdate(sqlite3_vtab* pVTab, int argc, sqlite3_value** argv,
	sqlite3_int64* pRowid) 
{
	return SQLITE_READONLY;
}

void SetupVirtualTable(sqlite3* db, MatrixData* matrix) {
	//sqlite3_create_module(db, "MatrixView", &myModule, matrix);
}