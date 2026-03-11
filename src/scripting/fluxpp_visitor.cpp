#include "fluxpp_visitor.hpp"
#include "fluxpp/functions.hpp"

template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

std::any FluxPPTreeInterpreter::visitProgram(fluxppParser::ProgramContext *context) {
}

std::any FluxPPTreeInterpreter::visitFlux(fluxppParser::FluxContext *context) {
}

std::any FluxPPTreeInterpreter::visitSingle(fluxppParser::SingleContext *context) {
}

std::any FluxPPTreeInterpreter::visitStatement(fluxppParser::StatementContext *context) {
}

std::any FluxPPTreeInterpreter::visitAssignment(fluxppParser::AssignmentContext *context) {
}

std::any FluxPPTreeInterpreter::visitCreate(fluxppParser::CreateContext *context) {
}

std::any FluxPPTreeInterpreter::visitFilter(fluxppParser::FilterContext *context) {
}

std::any FluxPPTreeInterpreter::visitDrop_row(fluxppParser::Drop_rowContext *context) {
}

std::any FluxPPTreeInterpreter::visitDrop_col(fluxppParser::Drop_colContext *context) {
}

std::any FluxPPTreeInterpreter::visitClamp(fluxppParser::ClampContext *context) {
}

std::any FluxPPTreeInterpreter::visitSet(fluxppParser::SetContext *context) {
}

std::any FluxPPTreeInterpreter::visitRename(fluxppParser::RenameContext *context) {
}

std::any FluxPPTreeInterpreter::visitFill(fluxppParser::FillContext *context) {
}

std::any FluxPPTreeInterpreter::visitAssert(fluxppParser::AssertContext *context) {
}

std::any FluxPPTreeInterpreter::visitParens(fluxppParser::ParensContext *context) {
}

std::any FluxPPTreeInterpreter::visitAbs(fluxppParser::AbsContext *context) {
    scripting::fluxpp::ExprReturn ret;
    const auto expr = visitExpr(context->expr());
    ret.isConst = expr.isConst;
    ret.type = expr.type;
    ret.isNull = expr.isNull;
    ret.isVector = expr.isVector;
    // EMIT IR TAKE ABS IF NON CONST
    std::visit(Overloaded {
        [&](const double d) { ret.value = fabs(d); },
        [&](const Eigen::Ref<const EigenColDoubleVec>& vec) {ret.value = vec.norm();},
    }, expr.value);
    return ret;
}

std::any FluxPPTreeInterpreter::visitFunctionCall(fluxppParser::FunctionCallContext *context) {
    const bool isConstArgs = std::any_cast<bool>(visit(context->args()));
    const uint64_t fn_idx = scripting::fluxpp::get_fn_index(context->function->toString());
    if (fn_idx == std::numeric_limits<uint64_t>::max()) {
        // ERROR
    }
    const auto order = scripting::fluxpp::get_fn_order(fn_idx);
    const auto isAgg = scripting::fluxpp::is_aggregated(fn_idx);

    scripting::fluxpp::ExprReturn ret;
    ret.isVector = true;
    ret.isConst = isConstArgs;
    // if aggregate, simple.
    // Else if args are vectors, then its a vector vector scenario.
    // Else scalar scalar or vector scalar
    if (isAgg) {
        ret.value = scripting::fluxpp::resolve_scalar_function_vector(vector_register, fn_idx, ndims);
        ret.isVector = false;
        ret.isConst = true;
    }
    else if (!isConstArgs) {
        ret.value = scripting::fluxpp::resolve_vector_function_vector(vector_register, fn_idx, ndims);
        ret.isVector = true;
        ret.isConst = false;
    }
    else {
        if (order == scripting::fluxpp::FN_ORDER::SCALAR_SCALAR) {
            ret.value = scripting::fluxpp::resolve_scalar_function_scalar(scalar_register, fn_idx);
            ret.isVector = false;
            ret.isConst = true;
        }
        else {
            ret.value = scripting::fluxpp::resolve_vector_function_scalar(scalar_register, fn_idx, ndims);
            ret.isVector = true;
            ret.isConst = false;
        }
    }
    ret.isNull = false; // CHECK
}

std::any FluxPPTreeInterpreter::visitArgs(fluxppParser::ArgsContext *context) {
    bool isAnyVec = false;
    if (context->expr().size()) {

    }
    for (int i = 0; i < context->expr().size(); i++) {
        const auto expr = visitExpr(context->expr()[i]);
        isAnyVec = isAnyVec || expr.isVector ;
        // EMIT IR STORE ARGS
        // IF AT LEAST ONE ARG IS VECTOR, BROADCAST ALL SCALARS
        // MIRROR WITH IR
        std::visit(Overloaded{
            [&](const EigenColDoubleVec& vec){ vector_register[i] = vec;},
            [&](const double d) {
                if (isAnyVec)
                    vector_register[i] = Eigen::VectorXd::Constant(ndims, d);
                else
                    scalar_register[i] = d;
            }
        }, expr.value);
    }
    // If all arguments are scalars, the function we will be calling next will have a const value.
    // We need to broadcast this to the function call.
    return !isAnyVec; // isAnyVec is true if non const, invert to get isConst
}

std::any FluxPPTreeInterpreter::visitExponentiation(fluxppParser::ExponentiationContext *context) {
}

std::any FluxPPTreeInterpreter::visitNegate(fluxppParser::NegateContext *context) {
}

std::any FluxPPTreeInterpreter::visitLogicalNot(fluxppParser::LogicalNotContext *context) {
}

std::any FluxPPTreeInterpreter::visitMultiplicative(fluxppParser::MultiplicativeContext *context) {
}

std::any FluxPPTreeInterpreter::visitAdditive(fluxppParser::AdditiveContext *context) {
}

std::any FluxPPTreeInterpreter::visitChainedComparisonAscending(
    fluxppParser::ChainedComparisonAscendingContext *context) {
}

std::any FluxPPTreeInterpreter::visitChainedComparisonDescending(
    fluxppParser::ChainedComparisonDescendingContext *context) {
}

std::any FluxPPTreeInterpreter::visitComparison(fluxppParser::ComparisonContext *context) {
}

std::any FluxPPTreeInterpreter::visitLogicalAnd(fluxppParser::LogicalAndContext *context) {
}

std::any FluxPPTreeInterpreter::visitLogicalOr(fluxppParser::LogicalOrContext *context) {
}

std::any FluxPPTreeInterpreter::visitTernary(fluxppParser::TernaryContext *context) {
}

std::any FluxPPTreeInterpreter::visitIdentifier(fluxppParser::IdentifierContext *context) {

}

std::any FluxPPTreeInterpreter::visitNumber(fluxppParser::NumberContext *context) {
}

std::any FluxPPTreeInterpreter::visitStringLiteral(fluxppParser::StringLiteralContext *context) {
}

std::any FluxPPTreeInterpreter::visitTrueLiteral(fluxppParser::TrueLiteralContext *context) {
}

std::any FluxPPTreeInterpreter::visitFalseLiteral(fluxppParser::FalseLiteralContext *context) {
}

std::any FluxPPTreeInterpreter::visitNullLiteral(fluxppParser::NullLiteralContext *context) {
}

std::any FluxPPTreeInterpreter::visitDateTime(fluxppParser::DateTimeContext *context) {
}

std::any FluxPPTreeInterpreter::visitDate(fluxppParser::DateContext *context) {
}

std::any FluxPPTreeInterpreter::visitTime(fluxppParser::TimeContext *context) {
}

FluxPPTreeInterpreter::ArgReturn FluxPPTreeInterpreter::visitArgs(fluxppParser::ArgsContext *context,
    scripting::fluxpp::FN_DATA &fn_data, const std::string& fn_name) {

    bool isAnyVec = false;
    if (context->expr().size() != fn_data.arg_count) {
        RecordErrorFmt(context, "Function {} takes {} arguments. {} were given.", fn_name, fn_data.arg_count, context->expr().size());
    }
    for (int i = 0; i < context->expr().size(); i++) {
        const auto expr = visitExpr(context->expr()[i]);

        if (expr.type != fn_data.arg_type) {
            RecordErrorFmt(context, "Function {} expects arguments of type {}.", fn_name, "INSERT TYPE");
        }

        isAnyVec = isAnyVec || expr.isVector ;
        // EMIT IR STORE ARGS
        // IF AT LEAST ONE ARG IS VECTOR, BROADCAST ALL SCALARS
        // MIRROR WITH IR
        std::visit(Overloaded{
            [&](const EigenColDoubleVec& vec){ vector_register[i] = vec;},
            [&](const double d) {
                if (isAnyVec)
                    vector_register[i] = Eigen::VectorXd::Constant(ndims, d);
                else
                    scalar_register[i] = d;
            }
        }, expr.value);
    }
    // If all arguments are scalars, the function we will be calling next will have a const value.
    // We need to broadcast this to the function call.
    return {!isAnyVec}; // isAnyVec is true if non const, invert to get isConst
}
