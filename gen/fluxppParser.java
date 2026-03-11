// Generated from E:/axiom/atlas/src/scripting/fluxpp/fluxpp.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class fluxppParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		AS=18, AND=19, ELSE=20, DROP=21, CREATE=22, KEEP=23, REMOVE=24, CLAMP=25, 
		SET=26, RENAME=27, FILL=28, ASSERT=29, WITH=30, OR=31, NOT=32, IF=33, 
		IN=34, FROM=35, TO=36, NULL=37, TRUE=38, FALSE=39, ISO_DATETIME=40, ISO_DATE=41, 
		ISO_TIME=42, NUMBER=43, STRING_LITERAL=44, UNTERMINATED_STRING_LITERAL=45, 
		ID=46, ENDLINE=47, NEWLINE=48, WS=49, BLOCK_COMMENT=50, LINE_COMMENT=51;
	public static final int
		RULE_program = 0, RULE_flux = 1, RULE_single = 2, RULE_statement = 3, 
		RULE_assignment = 4, RULE_create = 5, RULE_filter = 6, RULE_drop_row = 7, 
		RULE_drop_col = 8, RULE_clamp = 9, RULE_set = 10, RULE_rename = 11, RULE_fill = 12, 
		RULE_assert = 13, RULE_expr = 14, RULE_args = 15;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "flux", "single", "statement", "assignment", "create", "filter", 
			"drop_row", "drop_col", "clamp", "set", "rename", "fill", "assert", "expr", 
			"args"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'='", "','", "'('", "')'", "'|'", "'^'", "'-'", "'*'", "'/'", 
			"'%'", "'+'", "'<'", "'<='", "'>'", "'>='", "'=='", "'!='", "'as'", "'and'", 
			"'else'", "'drop'", "'create'", "'keep'", "'remove'", "'clamp'", "'set'", 
			"'rename'", "'fill'", "'assert'", "'with'", "'or'", "'not'", "'if'", 
			"'in'", "'from'", "'to'", "'null'", "'true'", "'false'", null, null, 
			null, null, null, null, null, "';'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, "AS", "AND", "ELSE", "DROP", "CREATE", 
			"KEEP", "REMOVE", "CLAMP", "SET", "RENAME", "FILL", "ASSERT", "WITH", 
			"OR", "NOT", "IF", "IN", "FROM", "TO", "NULL", "TRUE", "FALSE", "ISO_DATETIME", 
			"ISO_DATE", "ISO_TIME", "NUMBER", "STRING_LITERAL", "UNTERMINATED_STRING_LITERAL", 
			"ID", "ENDLINE", "NEWLINE", "WS", "BLOCK_COMMENT", "LINE_COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "fluxpp.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public fluxppParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public FluxContext flux() {
			return getRuleContext(FluxContext.class,0);
		}
		public SingleContext single() {
			return getRuleContext(SingleContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitProgram(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			setState(34);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(32);
				flux();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(33);
				single();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FluxContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(fluxppParser.EOF, 0); }
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public FluxContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_flux; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterFlux(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitFlux(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitFlux(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FluxContext flux() throws RecognitionException {
		FluxContext _localctx = new FluxContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_flux);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(39);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 70369815822336L) != 0)) {
				{
				{
				setState(36);
				statement();
				}
				}
				setState(41);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(42);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SingleContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode EOF() { return getToken(fluxppParser.EOF, 0); }
		public SingleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_single; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterSingle(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitSingle(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitSingle(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SingleContext single() throws RecognitionException {
		SingleContext _localctx = new SingleContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_single);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(44);
			expr(0);
			setState(45);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StatementContext extends ParserRuleContext {
		public CreateContext create() {
			return getRuleContext(CreateContext.class,0);
		}
		public AssignmentContext assignment() {
			return getRuleContext(AssignmentContext.class,0);
		}
		public FilterContext filter() {
			return getRuleContext(FilterContext.class,0);
		}
		public Drop_rowContext drop_row() {
			return getRuleContext(Drop_rowContext.class,0);
		}
		public Drop_colContext drop_col() {
			return getRuleContext(Drop_colContext.class,0);
		}
		public ClampContext clamp() {
			return getRuleContext(ClampContext.class,0);
		}
		public SetContext set() {
			return getRuleContext(SetContext.class,0);
		}
		public RenameContext rename() {
			return getRuleContext(RenameContext.class,0);
		}
		public FillContext fill() {
			return getRuleContext(FillContext.class,0);
		}
		public AssertContext assert_() {
			return getRuleContext(AssertContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitStatement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_statement);
		try {
			setState(57);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CREATE:
				enterOuterAlt(_localctx, 1);
				{
				setState(47);
				create();
				}
				break;
			case ID:
				enterOuterAlt(_localctx, 2);
				{
				setState(48);
				assignment();
				}
				break;
			case KEEP:
				enterOuterAlt(_localctx, 3);
				{
				setState(49);
				filter();
				}
				break;
			case DROP:
				enterOuterAlt(_localctx, 4);
				{
				setState(50);
				drop_row();
				}
				break;
			case REMOVE:
				enterOuterAlt(_localctx, 5);
				{
				setState(51);
				drop_col();
				}
				break;
			case CLAMP:
				enterOuterAlt(_localctx, 6);
				{
				setState(52);
				clamp();
				}
				break;
			case SET:
				enterOuterAlt(_localctx, 7);
				{
				setState(53);
				set();
				}
				break;
			case RENAME:
				enterOuterAlt(_localctx, 8);
				{
				setState(54);
				rename();
				}
				break;
			case FILL:
				enterOuterAlt(_localctx, 9);
				{
				setState(55);
				fill();
				}
				break;
			case ASSERT:
				enterOuterAlt(_localctx, 10);
				{
				setState(56);
				assert_();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignmentContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public AssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignment; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterAssignment(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitAssignment(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitAssignment(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignmentContext assignment() throws RecognitionException {
		AssignmentContext _localctx = new AssignmentContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_assignment);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(59);
			match(ID);
			setState(60);
			match(T__0);
			setState(61);
			expr(0);
			setState(62);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class CreateContext extends ParserRuleContext {
		public TerminalNode CREATE() { return getToken(fluxppParser.CREATE, 0); }
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public TerminalNode AS() { return getToken(fluxppParser.AS, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public CreateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_create; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterCreate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitCreate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitCreate(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CreateContext create() throws RecognitionException {
		CreateContext _localctx = new CreateContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_create);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(64);
			match(CREATE);
			setState(65);
			match(ID);
			setState(66);
			match(AS);
			setState(67);
			expr(0);
			setState(68);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FilterContext extends ParserRuleContext {
		public TerminalNode KEEP() { return getToken(fluxppParser.KEEP, 0); }
		public TerminalNode IF() { return getToken(fluxppParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public FilterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_filter; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterFilter(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitFilter(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitFilter(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FilterContext filter() throws RecognitionException {
		FilterContext _localctx = new FilterContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_filter);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(70);
			match(KEEP);
			setState(71);
			match(IF);
			setState(72);
			expr(0);
			setState(73);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Drop_rowContext extends ParserRuleContext {
		public TerminalNode DROP() { return getToken(fluxppParser.DROP, 0); }
		public TerminalNode IF() { return getToken(fluxppParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public Drop_rowContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_drop_row; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterDrop_row(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitDrop_row(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitDrop_row(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Drop_rowContext drop_row() throws RecognitionException {
		Drop_rowContext _localctx = new Drop_rowContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_drop_row);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(75);
			match(DROP);
			setState(76);
			match(IF);
			setState(77);
			expr(0);
			setState(78);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Drop_colContext extends ParserRuleContext {
		public ExprContext cond;
		public TerminalNode REMOVE() { return getToken(fluxppParser.REMOVE, 0); }
		public List<TerminalNode> ID() { return getTokens(fluxppParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(fluxppParser.ID, i);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public TerminalNode IF() { return getToken(fluxppParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Drop_colContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_drop_col; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterDrop_col(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitDrop_col(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitDrop_col(this);
			else return visitor.visitChildren(this);
		}
	}

	public final Drop_colContext drop_col() throws RecognitionException {
		Drop_colContext _localctx = new Drop_colContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_drop_col);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(80);
			match(REMOVE);
			setState(81);
			match(ID);
			setState(86);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(82);
				match(T__1);
				setState(83);
				match(ID);
				}
				}
				setState(88);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(91);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IF) {
				{
				setState(89);
				match(IF);
				setState(90);
				((Drop_colContext)_localctx).cond = expr(0);
				}
			}

			setState(93);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClampContext extends ParserRuleContext {
		public ExprContext from;
		public ExprContext to;
		public TerminalNode CLAMP() { return getToken(fluxppParser.CLAMP, 0); }
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public TerminalNode FROM() { return getToken(fluxppParser.FROM, 0); }
		public TerminalNode TO() { return getToken(fluxppParser.TO, 0); }
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ClampContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_clamp; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterClamp(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitClamp(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitClamp(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ClampContext clamp() throws RecognitionException {
		ClampContext _localctx = new ClampContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_clamp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(95);
			match(CLAMP);
			setState(96);
			match(ID);
			setState(97);
			match(FROM);
			setState(98);
			((ClampContext)_localctx).from = expr(0);
			setState(99);
			match(TO);
			setState(100);
			((ClampContext)_localctx).to = expr(0);
			setState(101);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SetContext extends ParserRuleContext {
		public TerminalNode SET() { return getToken(fluxppParser.SET, 0); }
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public SetContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_set; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterSet(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitSet(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitSet(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SetContext set() throws RecognitionException {
		SetContext _localctx = new SetContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_set);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(103);
			match(SET);
			setState(104);
			match(ID);
			setState(105);
			match(T__0);
			setState(106);
			expr(0);
			setState(107);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RenameContext extends ParserRuleContext {
		public Token oldCol;
		public Token newCol;
		public TerminalNode RENAME() { return getToken(fluxppParser.RENAME, 0); }
		public TerminalNode TO() { return getToken(fluxppParser.TO, 0); }
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public List<TerminalNode> ID() { return getTokens(fluxppParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(fluxppParser.ID, i);
		}
		public RenameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rename; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterRename(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitRename(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitRename(this);
			else return visitor.visitChildren(this);
		}
	}

	public final RenameContext rename() throws RecognitionException {
		RenameContext _localctx = new RenameContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_rename);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(109);
			match(RENAME);
			setState(110);
			((RenameContext)_localctx).oldCol = match(ID);
			setState(111);
			match(TO);
			setState(112);
			((RenameContext)_localctx).newCol = match(ID);
			setState(113);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FillContext extends ParserRuleContext {
		public TerminalNode FILL() { return getToken(fluxppParser.FILL, 0); }
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public TerminalNode WITH() { return getToken(fluxppParser.WITH, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public FillContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fill; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterFill(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitFill(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitFill(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FillContext fill() throws RecognitionException {
		FillContext _localctx = new FillContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_fill);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(115);
			match(FILL);
			setState(116);
			match(ID);
			setState(117);
			match(WITH);
			setState(118);
			expr(0);
			setState(119);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssertContext extends ParserRuleContext {
		public TerminalNode ASSERT() { return getToken(fluxppParser.ASSERT, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ENDLINE() { return getToken(fluxppParser.ENDLINE, 0); }
		public AssertContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assert; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterAssert(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitAssert(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitAssert(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssertContext assert_() throws RecognitionException {
		AssertContext _localctx = new AssertContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_assert);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(ASSERT);
			setState(122);
			expr(0);
			setState(123);
			match(ENDLINE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TernaryContext extends ExprContext {
		public ExprContext trueExpr;
		public ExprContext cond;
		public ExprContext falseExpr;
		public TerminalNode IF() { return getToken(fluxppParser.IF, 0); }
		public TerminalNode ELSE() { return getToken(fluxppParser.ELSE, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TernaryContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterTernary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitTernary(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitTernary(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParensContext extends ExprContext {
		public ArgsContext args() {
			return getRuleContext(ArgsContext.class,0);
		}
		public ParensContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterParens(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitParens(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitParens(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TimeContext extends ExprContext {
		public TerminalNode ISO_TIME() { return getToken(fluxppParser.ISO_TIME, 0); }
		public TimeContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterTime(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitTime(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitTime(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ExponentiationContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ExponentiationContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterExponentiation(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitExponentiation(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitExponentiation(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ChainedComparisonAscendingContext extends ExprContext {
		public ExprContext left;
		public Token opleft;
		public ExprContext middle;
		public Token opright;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ChainedComparisonAscendingContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterChainedComparisonAscending(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitChainedComparisonAscending(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitChainedComparisonAscending(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DateTimeContext extends ExprContext {
		public TerminalNode ISO_DATETIME() { return getToken(fluxppParser.ISO_DATETIME, 0); }
		public DateTimeContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterDateTime(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitDateTime(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitDateTime(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DateContext extends ExprContext {
		public TerminalNode ISO_DATE() { return getToken(fluxppParser.ISO_DATE, 0); }
		public DateContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterDate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitDate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitDate(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicalOrContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode OR() { return getToken(fluxppParser.OR, 0); }
		public LogicalOrContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterLogicalOr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitLogicalOr(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitLogicalOr(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FalseLiteralContext extends ExprContext {
		public TerminalNode FALSE() { return getToken(fluxppParser.FALSE, 0); }
		public FalseLiteralContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterFalseLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitFalseLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitFalseLiteral(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicalNotContext extends ExprContext {
		public TerminalNode NOT() { return getToken(fluxppParser.NOT, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public LogicalNotContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterLogicalNot(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitLogicalNot(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitLogicalNot(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ChainedComparisonDescendingContext extends ExprContext {
		public ExprContext left;
		public Token opleft;
		public ExprContext middle;
		public Token opright;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ChainedComparisonDescendingContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterChainedComparisonDescending(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitChainedComparisonDescending(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitChainedComparisonDescending(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class MultiplicativeContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public MultiplicativeContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterMultiplicative(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitMultiplicative(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitMultiplicative(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AdditiveContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public AdditiveContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterAdditive(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitAdditive(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitAdditive(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AbsContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AbsContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterAbs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitAbs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitAbs(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IdentifierContext extends ExprContext {
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public IdentifierContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterIdentifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitIdentifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitIdentifier(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NumberContext extends ExprContext {
		public TerminalNode NUMBER() { return getToken(fluxppParser.NUMBER, 0); }
		public NumberContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterNumber(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitNumber(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitNumber(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class StringLiteralContext extends ExprContext {
		public TerminalNode STRING_LITERAL() { return getToken(fluxppParser.STRING_LITERAL, 0); }
		public StringLiteralContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterStringLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitStringLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitStringLiteral(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TrueLiteralContext extends ExprContext {
		public TerminalNode TRUE() { return getToken(fluxppParser.TRUE, 0); }
		public TrueLiteralContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterTrueLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitTrueLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitTrueLiteral(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ComparisonContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ComparisonContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterComparison(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitComparison(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitComparison(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LogicalAndContext extends ExprContext {
		public ExprContext left;
		public Token op;
		public ExprContext right;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode AND() { return getToken(fluxppParser.AND, 0); }
		public LogicalAndContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterLogicalAnd(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitLogicalAnd(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitLogicalAnd(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionCallContext extends ExprContext {
		public Token function;
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode ID() { return getToken(fluxppParser.ID, 0); }
		public FunctionCallContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterFunctionCall(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitFunctionCall(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitFunctionCall(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NegateContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public NegateContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterNegate(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitNegate(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitNegate(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NullLiteralContext extends ExprContext {
		public TerminalNode NULL() { return getToken(fluxppParser.NULL, 0); }
		public NullLiteralContext(ExprContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterNullLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitNullLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitNullLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 28;
		enterRecursionRule(_localctx, 28, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(152);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				{
				_localctx = new ParensContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(126);
				match(T__2);
				setState(127);
				args();
				setState(128);
				match(T__3);
				}
				break;
			case 2:
				{
				_localctx = new AbsContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(130);
				match(T__4);
				setState(131);
				expr(0);
				setState(132);
				match(T__4);
				}
				break;
			case 3:
				{
				_localctx = new FunctionCallContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(134);
				((FunctionCallContext)_localctx).function = match(ID);
				setState(135);
				match(T__2);
				setState(136);
				expr(0);
				setState(137);
				match(T__3);
				}
				break;
			case 4:
				{
				_localctx = new NegateContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(139);
				match(T__6);
				setState(140);
				expr(19);
				}
				break;
			case 5:
				{
				_localctx = new LogicalNotContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(141);
				match(NOT);
				setState(142);
				expr(18);
				}
				break;
			case 6:
				{
				_localctx = new IdentifierContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(143);
				match(ID);
				}
				break;
			case 7:
				{
				_localctx = new NumberContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(144);
				match(NUMBER);
				}
				break;
			case 8:
				{
				_localctx = new DateTimeContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(145);
				match(ISO_DATETIME);
				}
				break;
			case 9:
				{
				_localctx = new DateContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(146);
				match(ISO_DATE);
				}
				break;
			case 10:
				{
				_localctx = new TimeContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(147);
				match(ISO_TIME);
				}
				break;
			case 11:
				{
				_localctx = new StringLiteralContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(148);
				match(STRING_LITERAL);
				}
				break;
			case 12:
				{
				_localctx = new TrueLiteralContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(149);
				match(TRUE);
				}
				break;
			case 13:
				{
				_localctx = new FalseLiteralContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(150);
				match(FALSE);
				}
				break;
			case 14:
				{
				_localctx = new NullLiteralContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(151);
				match(NULL);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(192);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(190);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
					case 1:
						{
						_localctx = new ExponentiationContext(new ExprContext(_parentctx, _parentState));
						((ExponentiationContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(154);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(155);
						((ExponentiationContext)_localctx).op = match(T__5);
						setState(156);
						((ExponentiationContext)_localctx).right = expr(20);
						}
						break;
					case 2:
						{
						_localctx = new MultiplicativeContext(new ExprContext(_parentctx, _parentState));
						((MultiplicativeContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(157);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(158);
						((MultiplicativeContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 1792L) != 0)) ) {
							((MultiplicativeContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(159);
						((MultiplicativeContext)_localctx).right = expr(18);
						}
						break;
					case 3:
						{
						_localctx = new AdditiveContext(new ExprContext(_parentctx, _parentState));
						((AdditiveContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(160);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(161);
						((AdditiveContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__6 || _la==T__10) ) {
							((AdditiveContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(162);
						((AdditiveContext)_localctx).right = expr(17);
						}
						break;
					case 4:
						{
						_localctx = new ChainedComparisonAscendingContext(new ExprContext(_parentctx, _parentState));
						((ChainedComparisonAscendingContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(163);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(164);
						((ChainedComparisonAscendingContext)_localctx).opleft = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__11 || _la==T__12) ) {
							((ChainedComparisonAscendingContext)_localctx).opleft = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(165);
						((ChainedComparisonAscendingContext)_localctx).middle = expr(0);
						setState(166);
						((ChainedComparisonAscendingContext)_localctx).opright = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__11 || _la==T__12) ) {
							((ChainedComparisonAscendingContext)_localctx).opright = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(167);
						((ChainedComparisonAscendingContext)_localctx).right = expr(16);
						}
						break;
					case 5:
						{
						_localctx = new ChainedComparisonDescendingContext(new ExprContext(_parentctx, _parentState));
						((ChainedComparisonDescendingContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(169);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(170);
						((ChainedComparisonDescendingContext)_localctx).opleft = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__13 || _la==T__14) ) {
							((ChainedComparisonDescendingContext)_localctx).opleft = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(171);
						((ChainedComparisonDescendingContext)_localctx).middle = expr(0);
						setState(172);
						((ChainedComparisonDescendingContext)_localctx).opright = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==T__13 || _la==T__14) ) {
							((ChainedComparisonDescendingContext)_localctx).opright = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(173);
						((ChainedComparisonDescendingContext)_localctx).right = expr(15);
						}
						break;
					case 6:
						{
						_localctx = new ComparisonContext(new ExprContext(_parentctx, _parentState));
						((ComparisonContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(175);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(176);
						((ComparisonContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 258048L) != 0)) ) {
							((ComparisonContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(177);
						((ComparisonContext)_localctx).right = expr(14);
						}
						break;
					case 7:
						{
						_localctx = new LogicalAndContext(new ExprContext(_parentctx, _parentState));
						((LogicalAndContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(178);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(179);
						((LogicalAndContext)_localctx).op = match(AND);
						setState(180);
						((LogicalAndContext)_localctx).right = expr(13);
						}
						break;
					case 8:
						{
						_localctx = new LogicalOrContext(new ExprContext(_parentctx, _parentState));
						((LogicalOrContext)_localctx).left = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(181);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(182);
						((LogicalOrContext)_localctx).op = match(OR);
						setState(183);
						((LogicalOrContext)_localctx).right = expr(12);
						}
						break;
					case 9:
						{
						_localctx = new TernaryContext(new ExprContext(_parentctx, _parentState));
						((TernaryContext)_localctx).trueExpr = _prevctx;
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(184);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(185);
						match(IF);
						setState(186);
						((TernaryContext)_localctx).cond = expr(0);
						setState(187);
						match(ELSE);
						setState(188);
						((TernaryContext)_localctx).falseExpr = expr(10);
						}
						break;
					}
					} 
				}
				setState(194);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,7,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgsContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ArgsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_args; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).enterArgs(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof fluxppListener ) ((fluxppListener)listener).exitArgs(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof fluxppVisitor ) return ((fluxppVisitor<? extends T>)visitor).visitArgs(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgsContext args() throws RecognitionException {
		ArgsContext _localctx = new ArgsContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_args);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(195);
			expr(0);
			setState(200);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(196);
				match(T__1);
				setState(197);
				expr(0);
				}
				}
				setState(202);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 14:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 20);
		case 1:
			return precpred(_ctx, 17);
		case 2:
			return precpred(_ctx, 16);
		case 3:
			return precpred(_ctx, 15);
		case 4:
			return precpred(_ctx, 14);
		case 5:
			return precpred(_ctx, 13);
		case 6:
			return precpred(_ctx, 12);
		case 7:
			return precpred(_ctx, 11);
		case 8:
			return precpred(_ctx, 10);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u00013\u00cc\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0001\u0000\u0001\u0000\u0003\u0000#\b\u0000\u0001\u0001\u0005\u0001"+
		"&\b\u0001\n\u0001\f\u0001)\t\u0001\u0001\u0001\u0001\u0001\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0003\u0003:\b\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001"+
		"\b\u0001\b\u0001\b\u0005\bU\b\b\n\b\f\bX\t\b\u0001\b\u0001\b\u0003\b\\"+
		"\b\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\f\u0001"+
		"\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0003\u000e\u0099\b\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001"+
		"\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0005\u000e\u00bf"+
		"\b\u000e\n\u000e\f\u000e\u00c2\t\u000e\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0005\u000f\u00c7\b\u000f\n\u000f\f\u000f\u00ca\t\u000f\u0001\u000f\u0000"+
		"\u0001\u001c\u0010\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014"+
		"\u0016\u0018\u001a\u001c\u001e\u0000\u0005\u0001\u0000\b\n\u0002\u0000"+
		"\u0007\u0007\u000b\u000b\u0001\u0000\f\r\u0001\u0000\u000e\u000f\u0001"+
		"\u0000\f\u0011\u00df\u0000\"\u0001\u0000\u0000\u0000\u0002\'\u0001\u0000"+
		"\u0000\u0000\u0004,\u0001\u0000\u0000\u0000\u00069\u0001\u0000\u0000\u0000"+
		"\b;\u0001\u0000\u0000\u0000\n@\u0001\u0000\u0000\u0000\fF\u0001\u0000"+
		"\u0000\u0000\u000eK\u0001\u0000\u0000\u0000\u0010P\u0001\u0000\u0000\u0000"+
		"\u0012_\u0001\u0000\u0000\u0000\u0014g\u0001\u0000\u0000\u0000\u0016m"+
		"\u0001\u0000\u0000\u0000\u0018s\u0001\u0000\u0000\u0000\u001ay\u0001\u0000"+
		"\u0000\u0000\u001c\u0098\u0001\u0000\u0000\u0000\u001e\u00c3\u0001\u0000"+
		"\u0000\u0000 #\u0003\u0002\u0001\u0000!#\u0003\u0004\u0002\u0000\" \u0001"+
		"\u0000\u0000\u0000\"!\u0001\u0000\u0000\u0000#\u0001\u0001\u0000\u0000"+
		"\u0000$&\u0003\u0006\u0003\u0000%$\u0001\u0000\u0000\u0000&)\u0001\u0000"+
		"\u0000\u0000\'%\u0001\u0000\u0000\u0000\'(\u0001\u0000\u0000\u0000(*\u0001"+
		"\u0000\u0000\u0000)\'\u0001\u0000\u0000\u0000*+\u0005\u0000\u0000\u0001"+
		"+\u0003\u0001\u0000\u0000\u0000,-\u0003\u001c\u000e\u0000-.\u0005\u0000"+
		"\u0000\u0001.\u0005\u0001\u0000\u0000\u0000/:\u0003\n\u0005\u00000:\u0003"+
		"\b\u0004\u00001:\u0003\f\u0006\u00002:\u0003\u000e\u0007\u00003:\u0003"+
		"\u0010\b\u00004:\u0003\u0012\t\u00005:\u0003\u0014\n\u00006:\u0003\u0016"+
		"\u000b\u00007:\u0003\u0018\f\u00008:\u0003\u001a\r\u00009/\u0001\u0000"+
		"\u0000\u000090\u0001\u0000\u0000\u000091\u0001\u0000\u0000\u000092\u0001"+
		"\u0000\u0000\u000093\u0001\u0000\u0000\u000094\u0001\u0000\u0000\u0000"+
		"95\u0001\u0000\u0000\u000096\u0001\u0000\u0000\u000097\u0001\u0000\u0000"+
		"\u000098\u0001\u0000\u0000\u0000:\u0007\u0001\u0000\u0000\u0000;<\u0005"+
		".\u0000\u0000<=\u0005\u0001\u0000\u0000=>\u0003\u001c\u000e\u0000>?\u0005"+
		"/\u0000\u0000?\t\u0001\u0000\u0000\u0000@A\u0005\u0016\u0000\u0000AB\u0005"+
		".\u0000\u0000BC\u0005\u0012\u0000\u0000CD\u0003\u001c\u000e\u0000DE\u0005"+
		"/\u0000\u0000E\u000b\u0001\u0000\u0000\u0000FG\u0005\u0017\u0000\u0000"+
		"GH\u0005!\u0000\u0000HI\u0003\u001c\u000e\u0000IJ\u0005/\u0000\u0000J"+
		"\r\u0001\u0000\u0000\u0000KL\u0005\u0015\u0000\u0000LM\u0005!\u0000\u0000"+
		"MN\u0003\u001c\u000e\u0000NO\u0005/\u0000\u0000O\u000f\u0001\u0000\u0000"+
		"\u0000PQ\u0005\u0018\u0000\u0000QV\u0005.\u0000\u0000RS\u0005\u0002\u0000"+
		"\u0000SU\u0005.\u0000\u0000TR\u0001\u0000\u0000\u0000UX\u0001\u0000\u0000"+
		"\u0000VT\u0001\u0000\u0000\u0000VW\u0001\u0000\u0000\u0000W[\u0001\u0000"+
		"\u0000\u0000XV\u0001\u0000\u0000\u0000YZ\u0005!\u0000\u0000Z\\\u0003\u001c"+
		"\u000e\u0000[Y\u0001\u0000\u0000\u0000[\\\u0001\u0000\u0000\u0000\\]\u0001"+
		"\u0000\u0000\u0000]^\u0005/\u0000\u0000^\u0011\u0001\u0000\u0000\u0000"+
		"_`\u0005\u0019\u0000\u0000`a\u0005.\u0000\u0000ab\u0005#\u0000\u0000b"+
		"c\u0003\u001c\u000e\u0000cd\u0005$\u0000\u0000de\u0003\u001c\u000e\u0000"+
		"ef\u0005/\u0000\u0000f\u0013\u0001\u0000\u0000\u0000gh\u0005\u001a\u0000"+
		"\u0000hi\u0005.\u0000\u0000ij\u0005\u0001\u0000\u0000jk\u0003\u001c\u000e"+
		"\u0000kl\u0005/\u0000\u0000l\u0015\u0001\u0000\u0000\u0000mn\u0005\u001b"+
		"\u0000\u0000no\u0005.\u0000\u0000op\u0005$\u0000\u0000pq\u0005.\u0000"+
		"\u0000qr\u0005/\u0000\u0000r\u0017\u0001\u0000\u0000\u0000st\u0005\u001c"+
		"\u0000\u0000tu\u0005.\u0000\u0000uv\u0005\u001e\u0000\u0000vw\u0003\u001c"+
		"\u000e\u0000wx\u0005/\u0000\u0000x\u0019\u0001\u0000\u0000\u0000yz\u0005"+
		"\u001d\u0000\u0000z{\u0003\u001c\u000e\u0000{|\u0005/\u0000\u0000|\u001b"+
		"\u0001\u0000\u0000\u0000}~\u0006\u000e\uffff\uffff\u0000~\u007f\u0005"+
		"\u0003\u0000\u0000\u007f\u0080\u0003\u001e\u000f\u0000\u0080\u0081\u0005"+
		"\u0004\u0000\u0000\u0081\u0099\u0001\u0000\u0000\u0000\u0082\u0083\u0005"+
		"\u0005\u0000\u0000\u0083\u0084\u0003\u001c\u000e\u0000\u0084\u0085\u0005"+
		"\u0005\u0000\u0000\u0085\u0099\u0001\u0000\u0000\u0000\u0086\u0087\u0005"+
		".\u0000\u0000\u0087\u0088\u0005\u0003\u0000\u0000\u0088\u0089\u0003\u001c"+
		"\u000e\u0000\u0089\u008a\u0005\u0004\u0000\u0000\u008a\u0099\u0001\u0000"+
		"\u0000\u0000\u008b\u008c\u0005\u0007\u0000\u0000\u008c\u0099\u0003\u001c"+
		"\u000e\u0013\u008d\u008e\u0005 \u0000\u0000\u008e\u0099\u0003\u001c\u000e"+
		"\u0012\u008f\u0099\u0005.\u0000\u0000\u0090\u0099\u0005+\u0000\u0000\u0091"+
		"\u0099\u0005(\u0000\u0000\u0092\u0099\u0005)\u0000\u0000\u0093\u0099\u0005"+
		"*\u0000\u0000\u0094\u0099\u0005,\u0000\u0000\u0095\u0099\u0005&\u0000"+
		"\u0000\u0096\u0099\u0005\'\u0000\u0000\u0097\u0099\u0005%\u0000\u0000"+
		"\u0098}\u0001\u0000\u0000\u0000\u0098\u0082\u0001\u0000\u0000\u0000\u0098"+
		"\u0086\u0001\u0000\u0000\u0000\u0098\u008b\u0001\u0000\u0000\u0000\u0098"+
		"\u008d\u0001\u0000\u0000\u0000\u0098\u008f\u0001\u0000\u0000\u0000\u0098"+
		"\u0090\u0001\u0000\u0000\u0000\u0098\u0091\u0001\u0000\u0000\u0000\u0098"+
		"\u0092\u0001\u0000\u0000\u0000\u0098\u0093\u0001\u0000\u0000\u0000\u0098"+
		"\u0094\u0001\u0000\u0000\u0000\u0098\u0095\u0001\u0000\u0000\u0000\u0098"+
		"\u0096\u0001\u0000\u0000\u0000\u0098\u0097\u0001\u0000\u0000\u0000\u0099"+
		"\u00c0\u0001\u0000\u0000\u0000\u009a\u009b\n\u0014\u0000\u0000\u009b\u009c"+
		"\u0005\u0006\u0000\u0000\u009c\u00bf\u0003\u001c\u000e\u0014\u009d\u009e"+
		"\n\u0011\u0000\u0000\u009e\u009f\u0007\u0000\u0000\u0000\u009f\u00bf\u0003"+
		"\u001c\u000e\u0012\u00a0\u00a1\n\u0010\u0000\u0000\u00a1\u00a2\u0007\u0001"+
		"\u0000\u0000\u00a2\u00bf\u0003\u001c\u000e\u0011\u00a3\u00a4\n\u000f\u0000"+
		"\u0000\u00a4\u00a5\u0007\u0002\u0000\u0000\u00a5\u00a6\u0003\u001c\u000e"+
		"\u0000\u00a6\u00a7\u0007\u0002\u0000\u0000\u00a7\u00a8\u0003\u001c\u000e"+
		"\u0010\u00a8\u00bf\u0001\u0000\u0000\u0000\u00a9\u00aa\n\u000e\u0000\u0000"+
		"\u00aa\u00ab\u0007\u0003\u0000\u0000\u00ab\u00ac\u0003\u001c\u000e\u0000"+
		"\u00ac\u00ad\u0007\u0003\u0000\u0000\u00ad\u00ae\u0003\u001c\u000e\u000f"+
		"\u00ae\u00bf\u0001\u0000\u0000\u0000\u00af\u00b0\n\r\u0000\u0000\u00b0"+
		"\u00b1\u0007\u0004\u0000\u0000\u00b1\u00bf\u0003\u001c\u000e\u000e\u00b2"+
		"\u00b3\n\f\u0000\u0000\u00b3\u00b4\u0005\u0013\u0000\u0000\u00b4\u00bf"+
		"\u0003\u001c\u000e\r\u00b5\u00b6\n\u000b\u0000\u0000\u00b6\u00b7\u0005"+
		"\u001f\u0000\u0000\u00b7\u00bf\u0003\u001c\u000e\f\u00b8\u00b9\n\n\u0000"+
		"\u0000\u00b9\u00ba\u0005!\u0000\u0000\u00ba\u00bb\u0003\u001c\u000e\u0000"+
		"\u00bb\u00bc\u0005\u0014\u0000\u0000\u00bc\u00bd\u0003\u001c\u000e\n\u00bd"+
		"\u00bf\u0001\u0000\u0000\u0000\u00be\u009a\u0001\u0000\u0000\u0000\u00be"+
		"\u009d\u0001\u0000\u0000\u0000\u00be\u00a0\u0001\u0000\u0000\u0000\u00be"+
		"\u00a3\u0001\u0000\u0000\u0000\u00be\u00a9\u0001\u0000\u0000\u0000\u00be"+
		"\u00af\u0001\u0000\u0000\u0000\u00be\u00b2\u0001\u0000\u0000\u0000\u00be"+
		"\u00b5\u0001\u0000\u0000\u0000\u00be\u00b8\u0001\u0000\u0000\u0000\u00bf"+
		"\u00c2\u0001\u0000\u0000\u0000\u00c0\u00be\u0001\u0000\u0000\u0000\u00c0"+
		"\u00c1\u0001\u0000\u0000\u0000\u00c1\u001d\u0001\u0000\u0000\u0000\u00c2"+
		"\u00c0\u0001\u0000\u0000\u0000\u00c3\u00c8\u0003\u001c\u000e\u0000\u00c4"+
		"\u00c5\u0005\u0002\u0000\u0000\u00c5\u00c7\u0003\u001c\u000e\u0000\u00c6"+
		"\u00c4\u0001\u0000\u0000\u0000\u00c7\u00ca\u0001\u0000\u0000\u0000\u00c8"+
		"\u00c6\u0001\u0000\u0000\u0000\u00c8\u00c9\u0001\u0000\u0000\u0000\u00c9"+
		"\u001f\u0001\u0000\u0000\u0000\u00ca\u00c8\u0001\u0000\u0000\u0000\t\""+
		"\'9V[\u0098\u00be\u00c0\u00c8";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}