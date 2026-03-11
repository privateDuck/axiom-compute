#pragma once
// ============================================================
//  FluxPP — DiagnosticBuilder.h
//
//  Fluent RAII builder returned by DiagnosticEngine::report().
//  Emits the Diagnostic to the engine automatically on
//  destruction, so callers never need to call .emit() manually.
//
//  Design notes:
//    • Every setter returns *this so calls chain naturally.
//    • Chaining is safe even after emit() — extra setters are
//      silently ignored once the diagnostic has been pushed.
//    • The builder is move-only; copies are deleted so that
//      there is always exactly one owner.
// ============================================================

#include "diagnostic.hpp"
#include <string>

namespace antlr4 {
    class Token;
    class ParserRuleContext;
}

namespace scripting::fluxpp {

class DiagnosticEngine;

class DiagnosticBuilder {
public:
    // ── Construction / destruction ────────────────────────────
    DiagnosticBuilder(DiagnosticEngine& engine, ErrorCode code);
    ~DiagnosticBuilder();

    // Move-only.
    DiagnosticBuilder(DiagnosticBuilder&&)            noexcept;
    DiagnosticBuilder& operator=(DiagnosticBuilder&&) noexcept;

    DiagnosticBuilder(const DiagnosticBuilder&)            = delete;
    DiagnosticBuilder& operator=(const DiagnosticBuilder&) = delete;

    // ── Location setters ──────────────────────────────────────
    DiagnosticBuilder& at(const antlr4::Token* token);
    DiagnosticBuilder& at(const antlr4::ParserRuleContext* ctx);
    DiagnosticBuilder& at(SourceLocation loc);

    // Optional secondary note (e.g., "first declared here")
    DiagnosticBuilder& note(std::string message, const antlr4::Token* token);
    DiagnosticBuilder& note(std::string message, SourceLocation loc);

    // ── Message field setters ─────────────────────────────────
    // what()    — required; describes what went wrong
    DiagnosticBuilder& what(std::string msg);

    // expected() — what the language / type system required
    DiagnosticBuilder& expected(std::string msg);

    // found()   — what the analyser / runtime actually observed
    DiagnosticBuilder& found(std::string msg);

    // fix()     — concrete, actionable suggestion (omit when none exists)
    DiagnosticBuilder& fix(std::string msg);

    // ── Explicit emit (optional — destructor calls this too) ──
    void emit();

private:
    DiagnosticEngine* engine_;   // nullable after move
    Diagnostic        diag_;
    bool              emitted_ = false;
};

} // namespace fluxpp