#pragma once
#include <cstdint>

namespace scripting::fluxpp {



enum OPCODE : uint8_t {
    NOP = 0xFF,
    END = 0xEF,

    // REAL
    ADD_R = 0x00,
    SUB_R = 0x01,
    MUL_R = 0x02,
    DIV_R = 0x03,
    MOD_R = 0x04,
    POW_R = 0x05,
    NEG_R = 0x06,
    ABS_R = 0x07,
    EQ_R = 0x08,
    NEQ_R = 0x09,
    LT_R = 0x0A,
    LTE_R = 0x0B,
    GT_R = 0x0C,
    GTE_R = 0x0D,
    // --RESERVED--

    // TIME STAMP
    ADD_T = 0x20,
    SUB_T = 0x21,
    EQ_T = 0x22,
    NEQ_T = 0x23,
    LT_T = 0x24,
    LTE_T = 0x25,
    GT_T = 0x26,
    GTE_T = 0x27,
    // --RESERVED--

    // BOOL
    AND_B = 0x40,
    OR_B = 0x41,
    NOT_B = 0x42,
    EQ_B = 0x43,
    NEQ_B = 0x44,
    XOR_B = 0x45,
    // --RESERVED--

    // STRING
    EQ_S = 0x60,
    NEQ_S = 0x61,
    // --RESERVED--

    // CONTROL
    CALL = 0x72, // CALL FUNCTION INDEXED BY PARAM 1
    LDAS = 0x73, // LOAD ARG SCALAR
    LDAV = 0x74, // LOAD ARG VECTOR
    COPY = 0x75, // COPY PARAM1 to PARAM2
    ZERO = 0x76, // ZERO MEMORY OF PARAM1
    FILTER = 0x77, // KEEP IF THE PARAM2 EVALUATES TO TRUE
    DROP = 0x78,
    CLAMP = 0x79,
    FILL = 0x7A,
    ASSERT = 0x7B,
    CREATE = 0x7C,
    // --RESERVED--
};

};
