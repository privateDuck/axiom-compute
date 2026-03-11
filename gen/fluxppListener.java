// Generated from E:/axiom/atlas/src/scripting/fluxpp/fluxpp.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link fluxppParser}.
 */
public interface fluxppListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link fluxppParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(fluxppParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(fluxppParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#flux}.
	 * @param ctx the parse tree
	 */
	void enterFlux(fluxppParser.FluxContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#flux}.
	 * @param ctx the parse tree
	 */
	void exitFlux(fluxppParser.FluxContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#single}.
	 * @param ctx the parse tree
	 */
	void enterSingle(fluxppParser.SingleContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#single}.
	 * @param ctx the parse tree
	 */
	void exitSingle(fluxppParser.SingleContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(fluxppParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(fluxppParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(fluxppParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(fluxppParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#create}.
	 * @param ctx the parse tree
	 */
	void enterCreate(fluxppParser.CreateContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#create}.
	 * @param ctx the parse tree
	 */
	void exitCreate(fluxppParser.CreateContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#filter}.
	 * @param ctx the parse tree
	 */
	void enterFilter(fluxppParser.FilterContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#filter}.
	 * @param ctx the parse tree
	 */
	void exitFilter(fluxppParser.FilterContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#drop_row}.
	 * @param ctx the parse tree
	 */
	void enterDrop_row(fluxppParser.Drop_rowContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#drop_row}.
	 * @param ctx the parse tree
	 */
	void exitDrop_row(fluxppParser.Drop_rowContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#drop_col}.
	 * @param ctx the parse tree
	 */
	void enterDrop_col(fluxppParser.Drop_colContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#drop_col}.
	 * @param ctx the parse tree
	 */
	void exitDrop_col(fluxppParser.Drop_colContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#clamp}.
	 * @param ctx the parse tree
	 */
	void enterClamp(fluxppParser.ClampContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#clamp}.
	 * @param ctx the parse tree
	 */
	void exitClamp(fluxppParser.ClampContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#set}.
	 * @param ctx the parse tree
	 */
	void enterSet(fluxppParser.SetContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#set}.
	 * @param ctx the parse tree
	 */
	void exitSet(fluxppParser.SetContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#rename}.
	 * @param ctx the parse tree
	 */
	void enterRename(fluxppParser.RenameContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#rename}.
	 * @param ctx the parse tree
	 */
	void exitRename(fluxppParser.RenameContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#fill}.
	 * @param ctx the parse tree
	 */
	void enterFill(fluxppParser.FillContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#fill}.
	 * @param ctx the parse tree
	 */
	void exitFill(fluxppParser.FillContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#assert}.
	 * @param ctx the parse tree
	 */
	void enterAssert(fluxppParser.AssertContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#assert}.
	 * @param ctx the parse tree
	 */
	void exitAssert(fluxppParser.AssertContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Ternary}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterTernary(fluxppParser.TernaryContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Ternary}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitTernary(fluxppParser.TernaryContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Parens}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterParens(fluxppParser.ParensContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Parens}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitParens(fluxppParser.ParensContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Time}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterTime(fluxppParser.TimeContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Time}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitTime(fluxppParser.TimeContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Exponentiation}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExponentiation(fluxppParser.ExponentiationContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Exponentiation}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExponentiation(fluxppParser.ExponentiationContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ChainedComparisonAscending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterChainedComparisonAscending(fluxppParser.ChainedComparisonAscendingContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ChainedComparisonAscending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitChainedComparisonAscending(fluxppParser.ChainedComparisonAscendingContext ctx);
	/**
	 * Enter a parse tree produced by the {@code DateTime}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterDateTime(fluxppParser.DateTimeContext ctx);
	/**
	 * Exit a parse tree produced by the {@code DateTime}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitDateTime(fluxppParser.DateTimeContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Date}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterDate(fluxppParser.DateContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Date}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitDate(fluxppParser.DateContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalOr}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterLogicalOr(fluxppParser.LogicalOrContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalOr}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitLogicalOr(fluxppParser.LogicalOrContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FalseLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterFalseLiteral(fluxppParser.FalseLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FalseLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitFalseLiteral(fluxppParser.FalseLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalNot}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterLogicalNot(fluxppParser.LogicalNotContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalNot}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitLogicalNot(fluxppParser.LogicalNotContext ctx);
	/**
	 * Enter a parse tree produced by the {@code ChainedComparisonDescending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterChainedComparisonDescending(fluxppParser.ChainedComparisonDescendingContext ctx);
	/**
	 * Exit a parse tree produced by the {@code ChainedComparisonDescending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitChainedComparisonDescending(fluxppParser.ChainedComparisonDescendingContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Multiplicative}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterMultiplicative(fluxppParser.MultiplicativeContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Multiplicative}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitMultiplicative(fluxppParser.MultiplicativeContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Additive}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterAdditive(fluxppParser.AdditiveContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Additive}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitAdditive(fluxppParser.AdditiveContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Abs}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterAbs(fluxppParser.AbsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Abs}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitAbs(fluxppParser.AbsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Identifier}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(fluxppParser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Identifier}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(fluxppParser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Number}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNumber(fluxppParser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Number}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNumber(fluxppParser.NumberContext ctx);
	/**
	 * Enter a parse tree produced by the {@code StringLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterStringLiteral(fluxppParser.StringLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code StringLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitStringLiteral(fluxppParser.StringLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code TrueLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterTrueLiteral(fluxppParser.TrueLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code TrueLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitTrueLiteral(fluxppParser.TrueLiteralContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Comparison}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterComparison(fluxppParser.ComparisonContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Comparison}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitComparison(fluxppParser.ComparisonContext ctx);
	/**
	 * Enter a parse tree produced by the {@code LogicalAnd}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterLogicalAnd(fluxppParser.LogicalAndContext ctx);
	/**
	 * Exit a parse tree produced by the {@code LogicalAnd}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitLogicalAnd(fluxppParser.LogicalAndContext ctx);
	/**
	 * Enter a parse tree produced by the {@code FunctionCall}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterFunctionCall(fluxppParser.FunctionCallContext ctx);
	/**
	 * Exit a parse tree produced by the {@code FunctionCall}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitFunctionCall(fluxppParser.FunctionCallContext ctx);
	/**
	 * Enter a parse tree produced by the {@code Negate}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNegate(fluxppParser.NegateContext ctx);
	/**
	 * Exit a parse tree produced by the {@code Negate}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNegate(fluxppParser.NegateContext ctx);
	/**
	 * Enter a parse tree produced by the {@code NullLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterNullLiteral(fluxppParser.NullLiteralContext ctx);
	/**
	 * Exit a parse tree produced by the {@code NullLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitNullLiteral(fluxppParser.NullLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link fluxppParser#args}.
	 * @param ctx the parse tree
	 */
	void enterArgs(fluxppParser.ArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link fluxppParser#args}.
	 * @param ctx the parse tree
	 */
	void exitArgs(fluxppParser.ArgsContext ctx);
}