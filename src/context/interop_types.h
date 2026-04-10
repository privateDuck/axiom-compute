#ifndef ATLAS_INTEROP_TYPES_H
#define ATLAS_INTEROP_TYPES_H


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum CValueType {
    C_VALUE_NULL    = 0,
    C_VALUE_BOOL    = 1,
    C_VALUE_INT64   = 2,
    C_VALUE_FLOAT64 = 3,
    C_VALUE_STRING  = 4,
    C_VALUE_BYTES   = 5,
    C_VALUE_LIST    = 6,
    C_VALUE_MAP     = 7,
    C_VALUE_DATAFRAME = 8,
} CValueType;


typedef struct {
    const char* ptr;   // UTF-8, null-terminated
    size_t      len;   // byte length (excluding null)
} CString;

typedef struct {
    const uint8_t* ptr;
    size_t         len;
} CBytes;


typedef struct CValue CValue;


typedef struct {
    CValue* items;
    size_t  count;
} CList;


typedef struct {
    CString* keys;
    CValue*  values;
    size_t   count;
} CMap;


//  Each column carries its own element type + a void* typed array.
typedef enum CColumnType {
    COL_BOOL    = 0,
    COL_INT64   = 1,
    COL_FLOAT64 = 2,
    COL_TIMESTAMP = 3, // INT64[]
    COL_STRING  = 4,  // CString[]
} CColumnType;

typedef struct {
    CString     name;
    CColumnType element_type;
    const void* data;       // cast per element_type
    const bool* null_mask;  // nullable: 1=null, or NULL ptr if no nulls. Maybe switched to a bitmask later
    size_t      row_count;
} CColumn;

typedef struct {
    CColumn* columns;
    size_t   column_count;
    size_t   row_count;
} CDataFrame;


struct CValue {
    CValueType type;
    union {
        bool        bool_val;
        int64_t     int64_val;
        double      float64_val;
        CString     string_val;
        CBytes      bytes_val;
        CList       list_val;
        CMap        map_val;
        CDataFrame  dataframe_val;
    };
};


typedef struct {
    bool    is_error;
    CString error_message;  // only valid when is_error == true
    CValue  payload;
} CResult;

#ifdef __cplusplus
}
#endif


#endif //ATLAS_INTEROP_TYPES_H