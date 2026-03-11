// Generated from E:/axiom/atlas/src/scripting/fluxpp/fluxpp.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link fluxppParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface fluxppVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link fluxppParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(fluxppParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#flux}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFlux(fluxppParser.FluxContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#single}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSingle(fluxppParser.SingleContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(fluxppParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#assignment}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignment(fluxppParser.AssignmentContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#create}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCreate(fluxppParser.CreateContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#filter}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFilter(fluxppParser.FilterContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#drop_row}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDrop_row(fluxppParser.Drop_rowContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#drop_col}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDrop_col(fluxppParser.Drop_colContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#clamp}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitClamp(fluxppParser.ClampContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#set}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSet(fluxppParser.SetContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#rename}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRename(fluxppParser.RenameContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#fill}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFill(fluxppParser.FillContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#assert}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssert(fluxppParser.AssertContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Ternary}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTernary(fluxppParser.TernaryContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Parens}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParens(fluxppParser.ParensContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Time}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTime(fluxppParser.TimeContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Exponentiation}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExponentiation(fluxppParser.ExponentiationContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ChainedComparisonAscending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitChainedComparisonAscending(fluxppParser.ChainedComparisonAscendingContext ctx);
	/**
	 * Visit a parse tree produced by the {@code DateTime}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDateTime(fluxppParser.DateTimeContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Date}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitDate(fluxppParser.DateContext ctx);
	/**
	 * Visit a parse tree produced by the {@code LogicalOr}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalOr(fluxppParser.LogicalOrContext ctx);
	/**
	 * Visit a parse tree produced by the {@code FalseLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFalseLiteral(fluxppParser.FalseLiteralContext ctx);
	/**
	 * Visit a parse tree produced by the {@code LogicalNot}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalNot(fluxppParser.LogicalNotContext ctx);
	/**
	 * Visit a parse tree produced by the {@code ChainedComparisonDescending}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitChainedComparisonDescending(fluxppParser.ChainedComparisonDescendingContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Multiplicative}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultiplicative(fluxppParser.MultiplicativeContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Additive}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAdditive(fluxppParser.AdditiveContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Abs}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAbs(fluxppParser.AbsContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Identifier}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifier(fluxppParser.IdentifierContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Number}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNumber(fluxppParser.NumberContext ctx);
	/**
	 * Visit a parse tree produced by the {@code StringLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStringLiteral(fluxppParser.StringLiteralContext ctx);
	/**
	 * Visit a parse tree produced by the {@code TrueLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTrueLiteral(fluxppParser.TrueLiteralContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Comparison}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitComparison(fluxppParser.ComparisonContext ctx);
	/**
	 * Visit a parse tree produced by the {@code LogicalAnd}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLogicalAnd(fluxppParser.LogicalAndContext ctx);
	/**
	 * Visit a parse tree produced by the {@code FunctionCall}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionCall(fluxppParser.FunctionCallContext ctx);
	/**
	 * Visit a parse tree produced by the {@code Negate}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNegate(fluxppParser.NegateContext ctx);
	/**
	 * Visit a parse tree produced by the {@code NullLiteral}
	 * labeled alternative in {@link fluxppParser#expr}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNullLiteral(fluxppParser.NullLiteralContext ctx);
	/**
	 * Visit a parse tree produced by {@link fluxppParser#args}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArgs(fluxppParser.ArgsContext ctx);
}