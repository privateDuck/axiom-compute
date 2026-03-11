#pragma once
// ============================================================
//  FluxPP — DiagnosticEngine.h
//
//  Central store and dispatcher for all diagnostics.
//  One engine instance is shared across the static analyzer
//  and the IR generator.  Both visitors receive a reference.
//
//  Typical usage:
//
//    DiagnosticEngine engine("my_script.flx", sourceLines);
//
//    // Inside a visitor:
//    engine.report(ErrorCode::SSA001_IMMUTABLE_REASSIGNMENT)
//          .at(ctx)
//          .what("Second assignment to immutable variable '" + name + "'")
//          .expected("LET variables are immutable; '" + name
//                    + "' was declared at line " + firstLine)
//          .found("Second LET " + name + " = … on line " + thisLine)
//          .fix("Rename the new variable, or remove the duplicate LET");
//
//    // After all visitors complete:
//    if (engine.hasErrors()) {
//        engine.printAll(std::cerr);
//        return 1;
//    }
// ============================================================

#include "diagnostic.hpp"
#include <vector>
#include <functional>
#include <string>

namespace scripting::fluxpp {

// Forward declared to avoid circular include.
class DiagnosticBuilder;

class DiagnosticEngine {
public:
    // sink — optional callback invoked immediately each time a Diagnostic is
    // pushed.  Useful for IDE/LSP integrations that need real-time feedback.
    using Sink = std::function<void(const Diagnostic&)>;

    // ── Construction ──────────────────────────────────────────
    explicit DiagnosticEngine(std::string sourceName   = "<input>",
                              std::vector<std::string> sourceLines = {},
                              Sink                     sink        = nullptr);

    explicit DiagnosticEngine(std::string sourceName   = "<input>",
                              const std::string& source= "",
                              Sink         sink        = nullptr);

    // Non-copyable; move-only.
    DiagnosticEngine(const DiagnosticEngine&)            = delete;
    DiagnosticEngine& operator=(const DiagnosticEngine&) = delete;
    DiagnosticEngine(DiagnosticEngine&&)                 = default;
    DiagnosticEngine& operator=(DiagnosticEngine&&)      = default;

    // ── Primary API ───────────────────────────────────────────
    // Returns a builder that auto-emits when it goes out of scope.
    DiagnosticBuilder report(ErrorCode code);

    // ── Query ─────────────────────────────────────────────────
    [[nodiscard]] bool        hasErrors()    const noexcept;
    [[nodiscard]] bool        hasWarnings()  const noexcept;
    [[nodiscard]] std::size_t errorCount()   const noexcept;
    [[nodiscard]] std::size_t warningCount() const noexcept;
    [[nodiscard]] std::size_t totalCount()   const noexcept;

    [[nodiscard]] const std::vector<Diagnostic>& diagnostics() const noexcept;

    // ── Output ────────────────────────────────────────────────
    // Print all diagnostics in full format to a stream.
    void printAll(std::ostream& os) const;

    // Print a one-line summary:  "2 error(s), 1 warning(s)"
    void printSummary(std::ostream& os) const;

    // ── Called by DiagnosticBuilder — do not call directly ────
    void push(Diagnostic diag);

    // ── Accessors for sub-components ──────────────────────────
    [[nodiscard]] const std::string&              sourceName()  const noexcept;
    [[nodiscard]] const std::vector<std::string>& sourceLines() const noexcept;

private:
    std::string              sourceName_;
    std::vector<std::string> sourceLines_;
    Sink                     sink_;
    std::vector<Diagnostic>  diagnostics_;
    std::size_t              errorCount_   = 0;
    std::size_t              warningCount_ = 0;
};

} // namespace fluxpp