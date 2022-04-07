parser grammar ExaLangParser;
options { tokenVocab = ExaLangLexer; }

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
    : TEST var COMP_OP var
    | TEST MRD
    | TEST F_END
    ;

var
    : LETTER
    | NUMLIT
    | STRLIT
    ;
