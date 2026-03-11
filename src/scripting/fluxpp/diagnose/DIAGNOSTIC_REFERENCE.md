# FluxPP Diagnostic Reference

## Error Message Format

```
{severity}[{CODE}]: {what}
  --> {file}:{line}:{col}
   |
{n} | {source line}
   |  {^^^^ caret}
   |
   = expected: {expected}
   = found:    {found}
   = fix:      {fix}            ← omitted when no concrete fix exists
```

---

## Error Code Index

### SSA — Immutability / Single Static Assignment

| Code | Severity | Title |
|------|----------|-------|
| SSA001 | error | Reassignment to immutable variable |
| SSA002 | error | LET variable name conflicts with existing column |

**SSA001** — `LET x = …` appears after `x` was already declared with `LET`,
or `SET x = …` is used on a `LET` variable.

**SSA002** — The identifier chosen for `LET` already exists as a data frame column.
Use `SET` to modify a column, or pick a different variable name.

---

### REF — Reference / Identifier Resolution

| Code | Severity | Title |
|------|----------|-------|
| REF001 | error | CREATE identifier already declared as variable |
| REF002 | error | CREATE identifier already exists as column |
| REF003 | error | Reference to undeclared column |
| REF004 | error | Reference to undeclared identifier |
| REF005 | error | RENAME source column does not exist |
| REF006 | error | RENAME destination name already in use |
| REF007 | error | Call to undeclared function |

---

### TYP — Type System

| Code | Severity | Title |
|------|----------|-------|
| TYP001 | error | Type mismatch between operands |
| TYP002 | error | Operator does not support this operand type |
| TYP003 | error | Condition expression must evaluate to bool |
| TYP004 | error | Ternary branches evaluate to different types |
| TYP005 | error | CLAMP 'from' and 'to' bounds have different types |
| TYP006 | error | CLAMP bound must be real or timestamp |
| TYP007 | error | SET expression type differs from column type |
| TYP008 | error | FILL expression type differs from column type |
| TYP009 | error | Function argument type mismatch |
| TYP010 | error | Function arguments must share the same type |
| TYP011 | error | Comparison operands have different types |
| TYP012 | error | Inequality operator requires real or timestamp |
| TYP013 | error | Arithmetic operands have different types |
| TYP014 | error | Operator does not support this arithmetic type |
| TYP015 | error | Logical operator requires bool operands |
| TYP016 | error | Unary negation requires a real operand |
| TYP017 | error | ABS requires a real operand |

---

### DIM — Dimensionality (Scalar vs. Vector)

| Code | Severity | Title |
|------|----------|-------|
| DIM001 | error | Expected vector expression, got scalar |
| DIM002 | error | Expected scalar expression, got vector |
| DIM003 | error | Function argument has wrong dimensionality |
| DIM004 | error | Ternary sub-expressions have mixed dimensionality |

**Broadcasting rules that suppress errors:**  
`binary_arithmetic`, `binary_comparison`, `logical_and_or`, and `chained_comparison`
all auto-broadcast when one side is scalar and the other is a vector.
DIM errors are only raised when broadcasting is *not* allowed (e.g., CLAMP bounds,
REMOVE condition, FILL value).

---

### ARG — Function Call Arguments

| Code | Severity | Title |
|------|----------|-------|
| ARG001 | error | Wrong number of arguments in function call |

---

### RNG — Value Range / Domain

| Code | Severity | Title |
|------|----------|-------|
| RNG001 | error | CLAMP range is empty or inverted (to ≤ from) |

---

### SEM — Semantic (Whole-Statement)

| Code | Severity | Title |
|------|----------|-------|
| SEM001 | error | Assertion failed at runtime |

---

### RUN — Runtime (IR Generator only)

| Code | Severity | Title |
|------|----------|-------|
| RUN001 | error | Division by zero at runtime |
| RUN002 | error | KEEP IF mask is all-false; data frame emptied |
| RUN003 | error | DROP IF mask is all-true; data frame emptied |
| RUN004 | error | Implicit cast failed for one or more elements |

RUN errors are emitted only by the IR Generator visitor.
The static analyser cannot detect them because they depend on actual data values.

---

### W — Warnings

| Code | Severity | Title |
|------|----------|-------|
| W-SEM001 | warning | REMOVE will drop all columns from data frame |
| W-TYP001 | warning | Implicit type cast will be applied |
| W-SEM002 | warning | Scalar expression in CREATE will be broadcast to vector |
| W-SEM003 | warning | Scalar expression in SET will be broadcast to column |

Warnings do not halt compilation or execution but indicate likely mistakes.

---

## Numeric Code Ranges

| Range | Category |
|-------|----------|
| 1000–1999 | SSA |
| 2000–2999 | REF |
| 3000–3999 | TYP |
| 4000–4999 | DIM |
| 5000–5999 | ARG |
| 6000–6999 | RNG |
| 7000–7999 | SEM |
| 8000–8999 | RUN |
| 9000–9999 | Warnings (W-*) |

Gaps within each range are reserved for future codes.

---

## Output Examples

### Static analysis — SSA001
```
error[SSA001]: Reassignment to immutable variable 'revenue'
  --> pipeline.flx:12:5
   |
12 |   LET revenue = price * qty
   |       ^^^^^^^
   |
   note: 'revenue' was first declared here
   |
 4 |   LET revenue = raw_revenue
   |       ^^^^^^^
   |
   = expected: LET variables are immutable and cannot be reassigned
   = found:    Second assignment to 'revenue' (first declared at line 4)
   = fix:      Use a different name, e.g. 'revenue2', or remove the duplicate LET
```

### Static analysis — TYP003 (KEEP IF condition not bool)
```
error[TYP003]: KEEP IF condition does not evaluate to bool
  --> pipeline.flx:19:8
   |
19 |   KEEP IF price
   |           ^^^^^
   |
   = expected: bool vector expression (condition)
   = found:    real vector expression
   = fix:      Apply a comparison operator, e.g.  KEEP IF price > 0
```

### Static analysis — W-SEM002 (scalar broadcast warning)
```
warning[W-SEM002]: Scalar expression in CREATE will be broadcast to vector
  --> pipeline.flx:7:14
   |
 7 |   CREATE tax_rate AS 0.2
   |                      ^^^
   |
   = expected: vector expression (one value per row)
   = found:    real scalar literal
```

### Runtime — RUN002 (all-false filter)
```
error[RUN002]: KEEP IF mask is all-false; all 1024 rows were dropped
  --> pipeline.flx:23:3
   |
23 |   KEEP IF category == "premium"
   |   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   |
   = expected: At least one row to satisfy the filter condition
   = found:    No row matched the condition; data frame is now empty
   = fix:      Re-examine the filter condition or the data —
               no input row had category == "premium"
```

---

## Adding a New Error Code

1. Add an enumerator to `ErrorCode` in `ErrorCodes.h` (respect the numeric range).
2. Add a matching `ErrorMeta` row to the `kMetaTable` in `ErrorCodes.cpp`.
3. Update the count in `static constexpr std::array<ErrorMeta, N>`.
4. Add a usage example in `DiagnosticUsageExamples.cpp`.
5. Add a row to this reference document.
