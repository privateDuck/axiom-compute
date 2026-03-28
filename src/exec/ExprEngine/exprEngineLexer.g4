lexer grammar exprEngineLexer;

YEARS: Y | Y E A R S;
MONTHS: M O N | M O N T H S;
DAYS: D | D A Y S;
WEEKS: W | W E E K S;
HOURS: H | H O U R S;
MINUTES: M I N U T E S;
SECONDS: S | S E C O N D S;

POPULATION: P O P | P O P U L A T I O N;
SAMPLE: S A M P L E;

ABS: A B S;
SIGN: S I G N;
SQRT: S Q R T;
POW: P O W;
LOG: L O G;
LOG2: L O G '2';
LOG10: L O G '1' '0';
EXP: E X P;
ERF: E R F;
CDFNORM: C D F N O R M;
FLOOR: F L O O R;
CEIL: C E I L;
ROUND: R O U N D;
SIN: S I N;
COS: C O S;
TAN: T A N;
CLOSEENOUGH: C L O S E E N O U G H;

AGGREGATE: A G G R E G A T E;
OVER: O V E R;

MEAN: M E A N;
MEDIAN: M E D I A N;
STDDEV: S T D D E V;
VARIANCE: V A R | V A R I A N C E;
MAX: M A X;
MIN: M I N;
SUM: S U M;
PROD: P R O D;

// UPPER: U P P E R; LOWER: L O W E R; TRIM: T R I M; SUBSTRING: S U B S T R I N G;
LENGTH: L E N G T H;
CONTAINS: C O N T A I N S;
STARTSWITH: S T A R T S W I T H;
ENDSWITH: E N D S W I T H;
LIKE: L I K E;

// Date functions
DATEDIFF: D A T E D I F F;
DATEADD: D A T E A D D;
// -- 
WEEKOFYEAR: W E E K O F Y E A R;
WEEKOFMONTH: W E E K O F M O N T H;
DAYOFWEEK: D A Y O F W E E K;
SECONDOFDAY: S E C O N D O F D A Y;

// Extractions
YEAR: Y E A R;
MONTH: M O N T H;
DAY: D A Y;
HOUR: H O U R;
MINUTE: M I N U T E;
SECOND: S E C O N D;

TRUE: T R U E;
FALSE: F A L S E;
NULL_: N U L L;

NOT: N O T;
AND: A N D;
OR: O R;

EQ: '=';
NEQ: '!=';
LT: '<';
GT: '>';
LTE: '<=';
GTE: '>=';
PLUS: '+';
MINUS: '-';
STAR: '*';
SLASH: '/';
DSLASH: '//';
PERCENT: '%';
CARET: '^';
CONCAT: '||';
COMMA: ',';
LPAREN: '(';
RPAREN: ')';
PIPE: '|';
LBRACKET: '[';
RBRACKET: ']';
SQUOTE: '\'';
BACKTICK: '`';

QUOTED_IDENTIFIER: '\'' ~['\r\n]* '\'';
IDENTIFIER: [a-zA-Z][a-zA-Z0-9_]*;

// Floating-point:  3.14   .5   1e10   1.5E-3
REAL_LITERAL:
	DIGIT+ '.' DIGIT* EXPONENT?
	| '.' DIGIT+ EXPONENT?
	| DIGIT+ EXPONENT;

// Integer:  42   0   1_000_000  (underscores for readability)
INT_LITERAL: DIGIT+ ('_' DIGIT+)*;

// Timestamp ISO 8601: 2024-01-15T09:30:00Z 2024-01-15T09:30:00+05:30 Matched before STRING_LITERAL
// to avoid ambiguity.
ISO_DATETIME: DATE_FRAG 'T' TIME_FRAG (ZONE_FRAG)?;
ISO_DATE: DATE_FRAG;
ISO_TIME: TIME_FRAG;

// Matches YYYY-MM-DD
fragment DATE_FRAG:
	DIGIT DIGIT DIGIT DIGIT '-' DIGIT DIGIT '-' DIGIT DIGIT;

// Matches HH:MM:SS
fragment TIME_FRAG: DIGIT DIGIT ':' DIGIT DIGIT ':' DIGIT DIGIT;

// Matches Z, +05:30, -0800, etc.
fragment ZONE_FRAG:
	'Z'
	| ('+' | '-') DIGIT DIGIT (':'? DIGIT DIGIT)?;

// Single-quoted string; escape '' for a literal single quote (SQL convention)
STRING_LITERAL: UNTERMINATED_STRING_LITERAL '"';
UNTERMINATED_STRING_LITERAL: '"' (~["\\\r\n] | '\\' (. | EOF))*;

// IDENTIFIER: [a-zA-Z_] [a-zA-Z_0-9]*;

WS: [ \t\r\n]+ -> skip;

fragment DIGIT: [0-9];
fragment EXPONENT: [eE] [+\-]? DIGIT+;
fragment SIGN_CHAR: [+\-];

// Case-insensitive letter fragments, one per letter of the alphabet.
fragment A: [aA];
fragment B: [bB];
fragment C: [cC];
fragment D: [dD];
fragment E: [eE];
fragment F: [fF];
fragment G: [gG];
fragment H: [hH];
fragment I: [iI];
fragment J: [jJ];
fragment K: [kK];
fragment L: [lL];
fragment M: [mM];
fragment N: [nN];
fragment O: [oO];
fragment P: [pP];
fragment Q: [qQ];
fragment R: [rR];
fragment S: [sS];
fragment T: [tT];
fragment U: [uU];
fragment V: [vV];
fragment W: [wW];
fragment X: [xX];
fragment Y: [yY];
fragment Z: [zZ];