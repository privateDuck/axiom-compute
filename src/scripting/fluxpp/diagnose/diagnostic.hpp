#pragma once
// ============================================================
//  FluxPP — Diagnostic.h
//  The Diagnostic struct is the atom of the error system.
//  Every reported issue becomes one Diagnostic.
// ============================================================

#include "error_codes.hpp"
#include <string>
#include <optional>
#include <cstdint>
#include <antlr4-runtime.h>
#include <iomanip>

// Forward-declare only — callers that need these must include ANTLR headers.
namespace antlr4 {
    class Token;
    class ParserRuleContext;
}

namespace scripting::fluxpp {

// ── Source location ───────────────────────────────────────────────────────────
struct SourceLocation {
    uint32_t    line        = 0;  // 1-based
    uint32_t    column      = 0;  // 0-based (ANTLR convention)
    uint32_t    endColumn   = 0;  // exclusive end column (for squiggle underline)
    std::string sourceName;       // file / buffer name shown in messages

    bool isValid() const noexcept { return line != 0; }

    // Factory helpers — defined in Diagnostic.cpp
    static SourceLocation from(const antlr4::Token* token, const std::string_view sourceName = "<input>") {
        if (!token) return unknown();
        SourceLocation loc;
        loc.line       = static_cast<uint32_t>(token->getLine());
        loc.column     = static_cast<uint32_t>(token->getCharPositionInLine());
        loc.endColumn  = loc.column + static_cast<uint32_t>(token->getText().size());
        loc.sourceName = sourceName;
        return loc;
    }
    static SourceLocation from(const antlr4::ParserRuleContext* ctx, const std::string_view sourceName = "<input>") {
        if (!ctx) return unknown();
        return from(ctx->getStart(), sourceName);
    }
    static SourceLocation unknown() noexcept { return {}; }
};


class Helpers {
public:
    // Renders the source-line caret block:
    //
    //    |
    //  7 | LET x = 99
    //    |     ^^^^^^^
    //    |
    static std::string caretBlock(const SourceLocation& loc,
                            const std::vector<std::string>& lines) {
        if (!loc.isValid() || lines.empty()) return {};
        const uint32_t idx = loc.line - 1;
        if (idx >= lines.size()) return {};

        const std::string& srcLine = lines[idx];

        // Line-number gutter width
        const int gutterW = static_cast<int>(std::to_string(loc.line).size()) + 1;

        std::ostringstream out;

        // Blank gutter line
        out << std::string(gutterW, ' ') << " |\n";

        // Source line
        out << std::setw(gutterW) << loc.line << " | " << srcLine << "\n";

        // Caret line
        const uint32_t start = loc.column;
        const uint32_t end   = (loc.endColumn > start) ? loc.endColumn : start + 1;
        out << std::string(gutterW, ' ') << " | "
            << std::string(start, ' ')
            << std::string(end - start, '^') << "\n";

        // Trailing blank line
        out << std::string(gutterW, ' ') << " |\n";

        return out.str();
    }

    static void appendField(std::ostringstream& out,
                            std::string_view label,
                            const std::string& value) {
        if (!value.empty())
            out << "       = " << label << ": " << value << "\n";
    }
};

// ── Diagnostic ────────────────────────────────────────────────────────────────
//
//  Every field except `code` is optional; the DiagnosticBuilder fills them
//  progressively. The formatted output follows:
//
//  Single-line (terse):
//    error[SSA001]: Reassignment to immutable variable
//
//  Multi-line (full):
//    error[SSA001]: Reassignment to immutable variable
//      --> input.flx:7:5
//       |
//     7 |   LET x = 99
//       |       ^^^^^^^
//       |
//       = what:     Second assignment to immutable variable 'x'
//       = expected: LET variables are immutable; 'x' was declared at line 3
//       = found:    A second LET x = … at line 7
//       = fix:      Use a different name, or remove the duplicate declaration
//
struct Diagnostic {
    // ── Identity ──────────────────────────────────────────────
    ErrorCode   code;
    Severity    severity;       // filled automatically from code's meta

    // ── Location ──────────────────────────────────────────────
    SourceLocation location;

    // ── Message fields ────────────────────────────────────────
    std::string what;           // What went wrong (required)
    std::string expected;       // What was expected
    std::string found;          // What was actually found / observed
    std::optional<std::string> fix; // Concrete suggestion (omit if no clear fix)

    // ── Optional secondary note (e.g. "first declared here") ──
    struct Note {
        SourceLocation location;
        std::string    message;
    };
    std::optional<Note> note;

    // ── Formatting ────────────────────────────────────────────
    // Returns:  error[SSA001]: Reassignment to immutable variable
    [[nodiscard]] std::string formatTerse() const {
        const auto& meta = KMap::GetMeta(code);
        std::ostringstream out;
        out << severityLabel(severity) << '[' << meta.tag << "]: " << what;
        return out.str();
    }

    // Returns full multi-line diagnostic (with source caret if lines supplied).
    // `sourceLines` is the split source text; pass empty to skip caret display.
    [[nodiscard]] std::string formatFull(const std::vector<std::string>& sourceLines = {}) const {
        const auto& meta = KMap::GetMeta(code);
        std::ostringstream out;

        // Header:  error[SSA001]: Reassignment to immutable variable
        out << severityLabel(severity) << '[' << meta.tag << "]: " << what << "\n";

        // Location arrow:  --> input.flx:7:5
        if (location.isValid()) {
            out << "  --> " << (location.sourceName.empty() ? "<input>" : location.sourceName)
                << ':' << location.line << ':' << location.column << "\n";
        }

        // Source caret block
        out << Helpers::caretBlock(location, sourceLines);

        // Note (secondary location, e.g. "first declared here")
        if (note.has_value()) {
            out << "  note: " << note->message << "\n";
            out << Helpers::caretBlock(note->location, sourceLines);
        }

        // Message fields
        Helpers::appendField(out, "expected", expected);
        Helpers::appendField(out, "found   ", found);
        if (fix.has_value())
            Helpers::appendField(out, "fix     ", *fix);

        return out.str();
    }
};

} // namespace fluxpp