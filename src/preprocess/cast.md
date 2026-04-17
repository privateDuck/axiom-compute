## Custom Type Inference with Arrow Compute

### The Pipeline

Your pipeline maps cleanly to three compute functions chained together:

```
StringArray  →  replace_substring_regex  →  cast (safe)  →  count nulls
```

---

### Step 1: Regex Cleaning — `replace_substring_regex`

```cpp
arrow::compute::ReplaceSubstringRegexOptions opts{
    /*pattern=*/ "[^0-9.\\-]",   // example: strip non-numeric chars for float check
    /*replacement=*/ ""
};
auto cleaned = arrow::compute::CallFunction(
    "replace_substring_regex", {string_array}, &opts
);
```

Note: this replaces **all** matches in-place per string. The result is still a `StringArray`.

---

### Step 2: Safe Cast — the critical piece

`CastOptions::Safe()` is what makes this work. It downgrades cast failures from errors to **nulls**, which is exactly what you want.

```cpp
auto cast_options = arrow::compute::CastOptions::Safe();
auto cast_result = arrow::compute::Cast(
    cleaned.ValueOrDie(),
    arrow::int64(),       // or float64, bool, etc.
    cast_options
);
```

**Exception — timestamps**: Don't use `Cast` for strings → timestamps. Use `strptime` instead, which accepts a format string and also produces nulls on failure:

```cpp
arrow::compute::StrptimeOptions ts_opts{
    /*format=*/ "%Y-%m-%d %H:%M:%S",
    /*unit=*/ arrow::TimeUnit::SECOND,
    /*error_is_null=*/ true    // <-- this is the safe-mode equivalent
};
auto ts_result = arrow::compute::CallFunction(
    "strptime", {cleaned.ValueOrDie()}, &ts_opts
);
```

---

### Step 3: Counting for Confidence Score

```cpp
// Count nulls (failed casts)
arrow::compute::CountOptions null_opts{arrow::compute::CountOptions::ONLY_NULL};
auto null_count = arrow::compute::CallFunction(
    "count", {cast_result.ValueOrDie()}, &null_opts
);

// Count valid (successful casts)
arrow::compute::CountOptions valid_opts{arrow::compute::CountOptions::NON_NULL};
auto valid_count = arrow::compute::CallFunction(
    "count", {cast_result.ValueOrDie()}, &valid_opts
);
```

Your confidence score is then `valid_count / total_rows`.

---

### Caveats — Several Worth Thinking Through Carefully

**1. Pre-existing nulls inflate your null count.**
If the original `StringArray` already has nulls (empty cells, explicit nulls), those pass through as nulls in the cast result. A naive null count conflates "was already missing" with "failed to parse." You should snapshot the original null count before the pipeline and subtract it:

```
parseable_rows = valid_count
failure_rows   = null_count_after_cast - null_count_before_cast
```

**2. Aggressive regex cleaning produces false positives.**
`"abc123"` stripped of non-digits becomes `"123"`, which casts to int successfully — but the original value was not an integer. This is likely the biggest design decision in your scheme. You have two philosophies:
- **Strict**: only clean genuinely cosmetic characters (thousands separators, currency symbols, whitespace). A value that has letters in it fails.
- **Permissive**: strip everything foreign and see what survives. Better for messy data, but confidence scores become less meaningful.

**3. Empty strings are not null — they will fail casts.**
`""` after regex cleaning will fail to cast to any numeric type and become null. Depending on your data source, empty strings might mean "missing" rather than "unparseable." You may want to replace empty strings with actual nulls before the pipeline using the `if_else` / `is_valid` kernels, or `replace_with_mask`.

**4. Integer vs. Float type ordering matters.**
`"3.0"` will fail to cast to `int64` (Arrow's string-to-int cast is strict — no decimal point allowed) but succeed for `float64`. If you test `int64` first and it fails, the confidence for int64 will be lower even though the column is arguably numeric. You probably want to test `float64` separately from `int64` and not treat a float-success as an int-failure.

**5. Integer width sensitivity.**
Arrow's safe cast will produce a null if the value overflows the target type. `"99999999999"` fits `int64` but not `int32`. If you're testing multiple integer widths, you'll get different confidence scores. Decide whether you want to test against the widest type (`int64`) and then consider downcasting separately, or test each width explicitly.

**6. Boolean is extremely promiscuous.**
Arrow's string-to-bool cast accepts `"true"`, `"false"`, `"1"`, `"0"` (case-insensitive). Many columns that are not booleans will score high confidence for bool — e.g., a numeric column of 0s and 1s. You should either test bool last, set a very high confidence threshold for it, or require that the column contains *only* the recognized boolean tokens by checking `valid_count == total_non_null_rows`.

**7. Decimal vs. Float.**
If you need exact decimal semantics (financial data), Arrow has a `Decimal128` type. String-to-decimal cast via `CastOptions::Safe()` works but requires you to specify precision and scale upfront, which you may not know. A practical approach is to cast to `float64` first for the confidence check, and if confidence is high, then attempt to infer a suitable `Decimal128(precision, scale)` from the string lengths.

**8. Timezone handling in timestamps.**
`strptime` produces timezone-naive timestamps. If your strings have timezone offsets (e.g., `+05:30`), you need `arrow::compute::AssumeTimezone` or format-string tokens for the offset. Missing this will produce nulls for strings that are technically valid timestamps.
