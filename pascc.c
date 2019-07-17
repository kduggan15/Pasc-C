#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0
typedef int type;
int ip;
int loc;
int len;
int datap=0;
char *source;
struct symtab main_tab;
FILE *outf;
char *outc;

#include "error.h"
#include "kdtk.h"
#include "symtable.h"
#include "tokenizer.h"
#include "opcodes.h"
#include "parser.h"




//Inserts something into symtab and checks if it's there
int symtab_test(){
	struct token test_token;
	test_token.type = TK_ID;
	test_token.value = 32;
	test_token.name[0] = '3';
	test_token.name[1] = '2';
	test_token.name[2] = '\0';
	printf("%s\n",test_token.name);
	symtab_add_key(&main_tab, test_token);
	test_token.name[0]='4';
	symtab_add_key(&main_tab, test_token);
	test_token.name[0]='5';
	symtab_add_key(&main_tab, test_token);
	test_token.name[0]='6';
	symtab_add_key(&main_tab, test_token);
	test_token.name[0]='7';
	symtab_add_key(&main_tab, test_token);
	printf("Contains: %d\n",symtab_get(&main_tab, test_token).value);
}

void token_all(){
	while(loc<len){
		print_token();
		printf("Current loc: %d\n", loc);
		next_token(source, &loc,len);
		printf("Token Type: %d\tToken Value: %d\t Token Name: %s",curToken.type,curToken.value,curToken.name);
		if(curToken.type == TK_REAL_LIT){
			printf("\t Real Value: %f", get_double_list(&real_pool,curToken.value));
		}
		printf("\n\n");
	}
}

int main(int argc, char const *argv[])
{
	ip=0;
	outf = fopen("out.o", "wb");
	if (outf == NULL)
	{
    printf("Error opening file!\n");
    exit(1);
	}
	//outc = ReadFile("out.o");
	main_tab = make_symtab();
	//symtab_test();
	loc = 0;
	source = ReadFile("test.txt");
	real_pool = make_double_list();
	len = strlen(source);
	//token_all();
	//parse_all();
	program();
	fclose(outf);
	return 0;
}
