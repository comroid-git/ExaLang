grammar ExaLang;

// codebase
file: (stmt LF)*;

stmt
    : stmtControl               #vStmtControl
    | stmtUnary var             #vStmtUnary
    | stmtBinary var var        #vStmtBinary
    | stmtTrinary var var var   #vStmtTrinary
    | stmtTest                  #vStmtTest
    ;

stmtControl
    : HALT
    | KILL
    | REPL
    | MODE
    | MAKE
    | WIPE
    | NOOP
    ;
stmtUnary
    : MARK
    | JUMP
    | TJMP
    | FJMP
    | DROP
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
stmtTest
    : TEST var COMP_OP var  #stmtTestCompare
    | TEST MRD              #stmtTestMrd
    | TEST F_END            #stmtTestEof
    ;

var
    : ID        #varReg
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
NUMLIT: MINUS? DIGIT+;
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
