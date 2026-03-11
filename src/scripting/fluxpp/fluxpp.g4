grammar fluxpp;

program: flux | single;

flux: statement* EOF;
single: expr EOF;

statement:
	create
	| assignment
	| filter
	| drop_row
	| drop_col
	| clamp
	| set
	| rename
	| fill
	| assert_statement;

assignment: LET ID '=' expr ENDLINE;
create: CREATE ID AS expr ENDLINE;
filter: KEEP IF expr ENDLINE;
drop_row: DROP IF expr ENDLINE;
drop_col: REMOVE ID (',' ID)* (IF cond = expr)? ENDLINE;
clamp: CLAMP ID FROM from = expr TO to = expr ENDLINE;
set: SET ID '=' expr ENDLINE;
rename: RENAME oldCol = ID TO newCol = ID ENDLINE;
fill: FILL ID WITH expr ENDLINE;
assert_statement: ASSERT expr ENDLINE;

expr:
	'(' expr ')'					# Parens
	| '|' expr '|'					# Abs
	| function = ID '(' args ')'	# FunctionCall

	// 1. Power
	| <assoc = right> left = expr op = '^' right = expr # Exponentiation

	// 2. Unary
	| '-' expr	# Negate
	| NOT expr	# LogicalNot

	// 3. Math
	| <assoc = left> left = expr op = ('*' | '/' | '%') right = expr	# Multiplicative
	| <assoc = left> left = expr op = ('+' | '-') right = expr			# Additive

	// 4. Chained Comparison (Specific cases first)
	| left = expr opleft = ('<' | '<=') middle = expr opright = (
		'<'
		| '<='
	) right = expr # ChainedComparisonAscending
	| left = expr opleft = ('>' | '>=') middle = expr opright = (
		'>'
		| '>='
	) right = expr # ChainedComparisonDescending

	// 5. Standard Comparison
	| <assoc = left> left = expr op = (
		'=='
		| '!='
		| '<'
		| '>'
		| '<='
		| '>='
	) right = expr # Comparison

	// 6. Logic
	| <assoc = left> left = expr op = AND right = expr	# LogicalAnd
	| <assoc = left> left = expr op = OR right = expr	# LogicalOr

	// 7. Ternary
	| <assoc = right> trueExpr = expr IF cond = expr ELSE falseExpr = expr # Ternary

	// 8. Terminals
	| ID				# Identifier
	| NUMBER			# Number
	| ISO_DATETIME      # DateTime
	| ISO_DATE          # Date
	| ISO_TIME          # Time
	| STRING_LITERAL	# StringLiteral
	| TRUE				# TrueLiteral
	| FALSE				# FalseLiteral
	| NULL				# NullLiteral;

args: expr (',' expr)*;

// Keywords
AS: 'as';
AND: 'and';
ELSE: 'else';
DROP: 'drop';
LET: 'let';
CREATE: 'create';
KEEP: 'keep';
REMOVE: 'remove';
CLAMP: 'clamp';
SET: 'set';
RENAME: 'rename';
FILL: 'fill';
ASSERT: 'assert';
WITH: 'with';
OR: 'or';
NOT: 'not';
IF: 'if';
IN: 'in';
FROM: 'from';
TO: 'to';

NULL: 'null';
TRUE: 'true';
FALSE: 'false';

ISO_DATETIME : DATE_FRAG 'T' TIME_FRAG (ZONE_FRAG)?;
ISO_DATE     : DATE_FRAG;
ISO_TIME     : TIME_FRAG;
NUMBER       : DIGIT+ ('.' DIGIT+)?;

// Matches YYYY-MM-DD
fragment DATE_FRAG : DIGIT DIGIT DIGIT DIGIT '-' DIGIT DIGIT '-' DIGIT DIGIT;
// Matches HH:MM:SS and optional .123 milliseconds
fragment TIME_FRAG : DIGIT DIGIT ':' DIGIT DIGIT ':' DIGIT DIGIT ('.' DIGIT+)?;
// Matches Z, +05:30, -0800, etc.

fragment ZONE_FRAG : 'Z' | ('+'|'-') DIGIT DIGIT (':'? DIGIT DIGIT)?;
fragment DIGIT     : [0-9];

STRING_LITERAL: UNTERMINATED_STRING_LITERAL '"';
UNTERMINATED_STRING_LITERAL: '"' (~["\\\r\n] | '\\' (. | EOF))*;

ID: [a-zA-Z][a-zA-Z_0-9]*;

ENDLINE: ';';
NEWLINE: ('\r' '\n'? | '\n') -> channel(HIDDEN);
WS: [ \t]+ -> channel(HIDDEN);
BLOCK_COMMENT: '/*' .*? '*/' -> channel(HIDDEN);
LINE_COMMENT: '//' ~[\r\n]* -> channel(HIDDEN);