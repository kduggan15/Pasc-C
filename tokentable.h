#ifndef KDTK_TKNTBL
#define KDTK_TKNTBL

#define TK_UNDEF				0
#define TK_AND          1
#define TK_BEGIN        2
#define TK_BOOLEAN      3
#define TK_BREAK        4
#define TK_CHAR         5
#define TK_CONTINUE     6
#define TK_DIV          7
#define TK_DO           8
#define TK_DOUBLE       9
#define TK_ELSE        10
#define TK_END         11
#define TK_FALSE       12
#define TK_IF          13
#define TK_INTEGER     14
#define TK_LONGINT     15
#define TK_MOD         16
#define TK_NOT         17
#define TK_OR          18
#define TK_REPEAT      19
#define TK_SHL         20
#define TK_SHORTINT    21
#define TK_SHR         22
#define TK_REAL      	 23
#define TK_THEN        24
#define TK_TRUE        25
#define TK_UNTIL       26
#define TK_WHILE       27
#define TK_WORD        28
#define TK_XOR         29
#define TK_TIMES       30
#define TK_PLUS        31
#define TK_MINUS       32
#define TK_DIVIDE      33
#define TK_SET         34
#define TK_LESS        35
#define TK_LESSEQ      36
#define TK_NOTEQ       37
#define TK_EQ          38
#define TK_GREAT       39
#define TK_GREATEQ     40
#define TK_SEMICOLON	 41
#define TK_LP		     	 42
#define TK_RP   			 43
#define TK_LBRACK			 44
#define TK_RBRACK      45
#define TK_PROGRAM		 46
#define TK_REAL_LIT    50
#define TK_INT_LIT     51
#define TK_CHAR_LIT    52
#define TK_STRING_LIT  53
#define TK_ID          54
#define TK_NULL        55
#define I              56
#define R              57
#define B              58
#define C              59
#define TK_EOF         60
#define TK_WRITE       61
#define TK_VAR         62
#define TK_COLON       63
#define TK_COMMA       64
#define TK_INT_VAR     65
#define TK_REAL_VAR    66
#define TK_BOOL_VAR    67
#define TK_CHAR_VAR    68
#define TK_ASSIGN      69
#define TK_PERIOD      70
#define TK_READ				 71
#define TK_PROCEDURE   72
#define TK_RET  			 73
#define TK_CALL  			 74

struct token
{
	int type;
	int value;
	char name[32];
};

#endif /*KDTK_TKNTBLE*/
