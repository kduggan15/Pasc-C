#ifndef PASCC_OPCODE
#define PASCC_OPCODE

#define OP_PUSH     1//
#define OP_POP      2//
#define OP_REM      3//
#define OP_DUP      4//
#define OP_EXCH     5//
#define OP_ADD      6//
#define OP_NEG      7//
#define OP_SUB      8//
#define OP_MUL      9//
#define OP_DIV      10//
#define OP_SHL      11//
#define OP_SHR      12//
#define OP_AND      13//
#define OP_XOR      14//
#define OP_FADD     15//
#define OP_FSUB     16
#define OP_FMUL     17
#define OP_FDIV     18
#define OP_FNEG     19
#define OP_NOT      20
#define OP_CVI      21
#define OP_CVR      22
#define OP_EQL      23
#define OP_NEQ      24
#define OP_LSS      25//19
#define OP_LEQ      26//1a
#define OP_GTR      27
#define OP_GEQ      28
#define OP_HALT     29//1d
#define OP_JMP      30//1e
#define OP_JTRU     31//1f
#define OP_JFAL     32//20
#define OP_CALL     33
#define OP_RET      34
#define OP_JTBL     35
#define OP_PRNTINT  36//24
#define OP_PRNTCHR  37
#define OP_PUSHI    38//26
#define OP_POPI     39
#define OP_OR       40//
#define OP_PRNTFLT  41//
#define OP_PRNTBOOL 42
#define OP_OR_B     43
#define OP_AND_B    44
#define OP_XOR_B    45
#define OP_READINT  46
#define OP_READFLT  47
#endif /*PASCC_OPCODE*/
