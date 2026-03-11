#include <antlr4-runtime.h>
#include "error_checker.hpp"
#include "fluxppLexer.h"
#include "fluxppParser.h"

int main() {
    std::string input_str;
    std::string line;
    while (std::getline(std::cin, line)) {
        input_str += line + "\n";
    }

    antlr4::ANTLRInputStream input(input_str);
    fluxppLexer lexer(&input);
    antlr4::CommonTokenStream tknstrm(&lexer);
    fluxppParser parser(&tknstrm);

    scripting::fluxpp::DiagnosticEngine engine("<input>", input_str);
    std::shared_ptr<scripting::fluxpp::DiagnosticEngine> engine_ptr = std::make_shared<scripting::fluxpp::DiagnosticEngine>(std::move(engine));
    scripting::fluxpp::ErrorListener errlis(engine_ptr);
    parser.removeErrorListeners();
    parser.addErrorListener(&errlis);

    fluxppParser::ProgramContext* tree = parser.program();

    if (engine_ptr->hasErrors()) {
        engine_ptr->printAll(std::cout);
        return 1;
    }

    df::DataFrame df;
    std::shared_ptr<df::DataFrame> df_ptr = std::make_shared<df::DataFrame>(std::move(df));
    scripting::fluxpp::StaticAnalyzer analyzer(df_ptr, engine_ptr);
    df_ptr->AddColumnReal("a", { 1, 2, 3 });
    df_ptr->AddColumnReal("b", { 2, 3, 4 });

    try {
        analyzer.visit(tree);
    }
    catch (const std::bad_any_cast& e) {
    }


    if (engine_ptr->hasErrors() || engine_ptr->hasWarnings()) {
        engine_ptr->printAll(std::cout);
        return 1;
    }

    return 0;
}