#include "diagnostic_engine.hpp"
#include "diagnostic_builder.hpp"
#include <antlr/antlr4-runtime.h>
#include <utility>
#include <ostream>
#include <sstream>

namespace exec::expr {

DiagnosticEngine::DiagnosticEngine(std::string              sourceName,
                                   std::vector<std::string> sourceLines,
                                   Sink                     sink)
    : sourceName_(std::move(sourceName))
    , sourceLines_(std::move(sourceLines))
    , sink_(std::move(sink))
{}

DiagnosticEngine::DiagnosticEngine(std::string sourceName, const std::string &source, Sink sink)
    : sourceName_(std::move(sourceName)),
    sink_(std::move(sink))
{
    std::istringstream ss(source);
    std::vector<std::string> lines;
    std::string line;

	while (std::getline(ss, line)) {
        lines.push_back(std::move(line));
    }

    sourceLines_ = std::move(lines);
}

DiagnosticBuilder DiagnosticEngine::report(ErrorCode code) {
    return DiagnosticBuilder(*this, code);
}

void DiagnosticEngine::push(Diagnostic diag) {
    if (diag.severity == Severity::Error)   ++errorCount_;
    else                                    ++warningCount_;

    if (sink_) sink_(diag);
    diagnostics_.push_back(std::move(diag));
}

bool        DiagnosticEngine::hasErrors()    const noexcept { return errorCount_   > 0; }
bool        DiagnosticEngine::hasWarnings()  const noexcept { return warningCount_ > 0; }
std::size_t DiagnosticEngine::errorCount()   const noexcept { return errorCount_;   }
std::size_t DiagnosticEngine::warningCount() const noexcept { return warningCount_; }
std::size_t DiagnosticEngine::totalCount()   const noexcept { return diagnostics_.size(); }

const std::vector<Diagnostic>& DiagnosticEngine::diagnostics() const noexcept {
    return diagnostics_;
}

const std::string& DiagnosticEngine::sourceName() const noexcept {
    return sourceName_;
}

const std::vector<std::string>& DiagnosticEngine::sourceLines() const noexcept {
    return sourceLines_;
}

void DiagnosticEngine::printAll(std::ostream& os) const {
    for (const auto& d : diagnostics_)
        os << d.formatFull(sourceLines_) << '\n';
    printSummary(os);
}

void DiagnosticEngine::printSummary(std::ostream& os) const {
    if (errorCount_ == 0 && warningCount_ == 0) return;
    os << errorCount_   << " error(s), "
       << warningCount_ << " warning(s)\n";
}

DiagnosticBuilder::DiagnosticBuilder(DiagnosticEngine& engine, ErrorCode code)
    : engine_(&engine)
{
    const auto& meta  = KMap::GetMeta(code);
    diag_.code        = code;
    diag_.severity    = meta.severity;
    // Pre-fill `what` with the title so callers get a sensible message
    // even if they forget to call .what().  Overridable.
    diag_.what        = std::string(meta.title);
    diag_.location    = SourceLocation::unknown();
}

DiagnosticBuilder::~DiagnosticBuilder() {
    emit();
}

DiagnosticBuilder::DiagnosticBuilder(DiagnosticBuilder&& other) noexcept
    : engine_(other.engine_)
    , diag_(std::move(other.diag_))
    , emitted_(other.emitted_)
{
    other.engine_  = nullptr;
    other.emitted_ = true; // prevent double-emit from moved-from object
}

DiagnosticBuilder& DiagnosticBuilder::operator=(DiagnosticBuilder&& other) noexcept {
    if (this != &other) {
        emit(); // flush current before overwriting
        engine_        = other.engine_;
        diag_          = std::move(other.diag_);
        emitted_       = other.emitted_;
        other.engine_  = nullptr;
        other.emitted_ = true;
    }
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::at(const antlr4::Token* token) {
    if (!emitted_ && engine_)
        diag_.location = SourceLocation::from(token, engine_->sourceName());
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::at(const antlr4::ParserRuleContext* ctx) {
    if (!emitted_ && engine_)
        diag_.location = SourceLocation::from(ctx, engine_->sourceName());
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::at(SourceLocation loc) {
    if (!emitted_)
        diag_.location = std::move(loc);
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::note(std::string message,
                                            const antlr4::Token* token) {
    if (!emitted_ && engine_) {
        diag_.note = Diagnostic::Note{
            SourceLocation::from(token, engine_->sourceName()),
            std::move(message)
        };
    }
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::note(std::string message, SourceLocation loc) {
    if (!emitted_) {
        diag_.note = Diagnostic::Note{ std::move(loc), std::move(message) };
    }
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::what(std::string msg) {
    if (!emitted_) diag_.what = std::move(msg);
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::expected(std::string msg) {
    if (!emitted_) diag_.expected = std::move(msg);
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::found(std::string msg) {
    if (!emitted_) diag_.found = std::move(msg);
    return *this;
}

DiagnosticBuilder& DiagnosticBuilder::fix(std::string msg) {
    if (!emitted_) diag_.fix = std::move(msg);
    return *this;
}

void DiagnosticBuilder::emit() {
    if (emitted_ || !engine_) return;
    emitted_ = true;
    engine_->push(std::move(diag_));
}

} // namespace expr