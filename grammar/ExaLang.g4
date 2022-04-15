grammar ExaLang;

// codebase
file: (stmt LF)*;

stmt
    : stmtBlank
    | stmtUnary var
    | stmtBinary var var
    | stmtTrinary var var var
    | stmtSpecial
    ;

stmtBlank
    : HALT
    | KILL
    | MODE
    | MAKE
    | DROP
    | WIPE
    | NOOP
    ;
stmtUnary
    : MARK
    | JUMP
    | TJMP
    | FJMP
    | REPL
    | LINK
    | HOST
    | VOID
    | GRAB
    | FILE
    | SEEK
    ;
stmtBinary
    : COPY
    ;
stmtTrinary
    : SWIZ
    | RAND
    | ADDI
    | SUBI
    | MULI
    | DIVI
    | MODI
    ;
stmtSpecial
    : TEST var COMP_OP var  #testCompare
    | TEST MRD              #testMrd
    | TEST F_END            #testEof
    ;

var
    : LETTER    #varReg
    | NUMLIT    #varNum
    | STRLIT    #varStr
    ;

// manipulating values
COPY: 'COPY';
ADDI: 'ADDI';
SUBI: 'SUBI';
MULI: 'MULI';
DIVI: 'DIVI';
MODI: 'MODI';
SWIZ: 'SWIZ';

// branching
MARK: 'MARK';
JUMP: 'JUMP';
TJMP: 'TJMP';
FJMP: 'FJMP';

// testing values
TEST: 'TEST';

// lifecycle
REPL: 'REPL';
HALT: 'HALT';
KILL: 'KILL';

// movement
LINK: 'LINK';
HOST: 'HOST';

// communication
MODE: 'MODE';
VOID: 'VOID';

// file manipulation
MAKE: 'MAKE';
GRAB: 'GRAB';
FILE: 'FILE';
SEEK: 'SEEK';
DROP: 'DROP';
WIPE: 'WIPE';

// miscellaneous
NOTE: 'NOTE' ~[\r\n]* -> channel(HIDDEN);
NOOP: 'NOOP';
RAND: 'RAND';

// comparison operators
COMP_OP: EQUALS | NOTEQUALS | LESSER | GREATER;
EQUALS: '=';
NOTEQUALS: '!';
LESSER: '<';
GREATER: '>';

// keywords
MRD: 'mrd';
F_END: 'eof';
ID: LETTER (DIGIT | LETTER)*;
NUMLIT: MINUS? DIGIT+ (DOT DIGIT+)?;
STRLIT: QUOTE (ESCAPE_QUOTE | (~[\r\n"]))*? (QUOTE);
DIGIT: [0-9];
LETTER: [a-zA-Z_$£#];
MINUS: '-';
DOT: '.';
QUOTE: '"';
ESCAPE_QUOTE: '\\"';

// other
LF: [\n\r];
WS: [ \t] -> channel(HIDDEN);
