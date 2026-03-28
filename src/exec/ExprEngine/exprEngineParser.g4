parser grammar exprEngineParser;

options {
	tokenVocab = exprEngineLexer;
}

expression: expr | aggregateOver | EOF;

expr
	returns[ int returnType = 0 ]:
	LPAREN expr RPAREN									# exprParen
	| PIPE expr PIPE									# exprAbs
	| functionCall										# exprCall
	| <assoc = right> left = expr CARET right = expr	# exprExp
	| MINUS expr										# exprNegate
	| NOT expr											# exprNot
	| <assoc = left> left = expr STAR right = expr		# exprMul
	| <assoc = left> left = expr SLASH right = expr		# exprDiv
	| <assoc = left> left = expr PERCENT right = expr	# exprMod
	| <assoc = left> left = expr DSLASH right = expr	# exprIntDiv
	| <assoc = left> left = expr PLUS right = expr		# exprAdd
	| <assoc = left> left = expr MINUS right = expr		# exprSub
	| <assoc = left> left = expr EQ right = expr		# exprEq
	| <assoc = left> left = expr NEQ right = expr		# exprNeq
	| <assoc = left> left = expr LT right = expr		# exprLt
	| <assoc = left> left = expr LTE right = expr		# exprLte
	| <assoc = left> left = expr GT right = expr		# exprGt
	| <assoc = left> left = expr GTE right = expr		# exprGte
	| <assoc = left> left = expr AND right = expr		# exprAnd
	| <assoc = left> left = expr OR right = expr		# exprOr
	| <assoc = left> left = expr CONCAT right = expr	# exprConcat
	| literal											# exprLiteral
	| identifier										# exprIndentifier;

aggregateOver: AGGREGATE aggregateFn OVER identifier;

identifier: IDENTIFIER | QUOTED_IDENTIFIER;
functionCall: statelessFn | aggregateFn;
statelessFn: mathFn | stringFn | timestampFn;

aggregateFn:
	MEAN LPAREN expr RPAREN			# fnAgg_Mean
	| MEDIAN LPAREN expr RPAREN		# fnAgg_Median
	| STDDEV LPAREN expr RPAREN		# fnAgg_StdDev
	| VARIANCE LPAREN expr RPAREN	# fnAgg_Variance
	| MAX LPAREN expr RPAREN		# fnAgg_Max
	| MIN LPAREN expr RPAREN		# fnAgg_Min
	| SUM LPAREN expr RPAREN		# fnAgg_Sum
	| PROD LPAREN expr RPAREN		# fnAgg_Prod;

mathFn:
	ABS LPAREN expr RPAREN								        # fnSL_Abs
	| SIGN LPAREN expr RPAREN							        # fnSL_Sign
	| SQRT LPAREN expr RPAREN							        # fnSL_Sqrt
	| POW LPAREN left = expr COMMA right = expr RPAREN	        # fnSL_Pow
	| LOG LPAREN expr RPAREN							        # fnSL_Log
	| LOG2 LPAREN expr RPAREN							        # fnSL_Log2
	| LOG10 LPAREN expr RPAREN							        # fnSL_Log10
	| EXP LPAREN expr RPAREN							        # fnSL_Exp
	| ERF LPAREN expr RPAREN							        # fnSL_Erf
	| CDFNORM LPAREN expr RPAREN						        # fnSL_CdfNorm
	| FLOOR LPAREN expr RPAREN							        # fnSL_Floor
	| CEIL LPAREN expr RPAREN							        # fnSL_Ceil
	| ROUND LPAREN expr RPAREN							        # fnSL_Round
	| SIN LPAREN expr RPAREN							        # fnSL_Sin
	| COS LPAREN expr RPAREN							        # fnSL_Cos
	| TAN LPAREN expr RPAREN							        # fnSL_Tan
	| CLOSEENOUGH LPAREN arg1 = expr COMMA arg2 = expr RPAREN   # fnSL_CloseEnough;

stringFn:
	// UPPER LPAREN expr RPAREN # fnSL_Upper | LOWER LPAREN expr RPAREN # fnSL_Lower | TRIM LPAREN
	// expr RPAREN # fnSL_Trim | SUBSTRING LPAREN expr COMMA expr COMMA expr RPAREN # fnSL_Substring
	LENGTH LPAREN expr RPAREN										# fnSL_Length
	| CONTAINS LPAREN input = expr COMMA pattern = expr RPAREN		# fnSL_Contains
	| STARTSWITH LPAREN input = expr COMMA pattern = expr RPAREN	# fnSL_StartsWith
	| ENDSWITH LPAREN input = expr COMMA pattern = expr RPAREN		# fnSL_EndsWith
	| LIKE LPAREN input = expr COMMA pattern = expr RPAREN			# fnSL_Like;

timestampFn:
	YEAR LPAREN expr RPAREN																# fnSL_Year
	| MONTH LPAREN expr RPAREN															# fnSL_Month
	| DAY LPAREN expr RPAREN															# fnSL_Day
	| HOUR LPAREN expr RPAREN															# fnSL_Hour
	| MINUTE LPAREN expr RPAREN															# fnSL_Minute
	| SECOND LPAREN expr RPAREN															# fnSL_Second
	| SECONDOFDAY LPAREN expr RPAREN													# fnSL_SecondOfDay
	| WEEKOFMONTH LPAREN expr RPAREN													# fnSL_WeekOfMonth
	| DAYOFWEEK LPAREN expr RPAREN														# fnSL_DayOfWeek
	| WEEKOFYEAR LPAREN expr RPAREN														# fnSL_WeekOfYear
	| DATEDIFF LPAREN date1 = expr COMMA date2 = expr COMMA unit = timeUnit RPAREN		# fnSL_DateDiff
	| DATEADD LPAREN date1 = expr COMMA duration = expr COMMA unit = timeUnit RPAREN	# fnSL_DateAdd;

literal:
	realLit
	| intLit
	| boolLit
	| stringLit
	| timestampLit
	| nullLit;

realLit: REAL_LITERAL;
intLit: INT_LITERAL;
boolLit: TRUE | FALSE;
stringLit: STRING_LITERAL;
timestampLit: ISO_DATETIME | ISO_DATE | ISO_TIME;
nullLit: NULL_;

timeUnit:
	YEARS
	| MONTHS
	| DAYS
	| WEEKS
	| HOURS
	| MINUTES
	| SECONDS;