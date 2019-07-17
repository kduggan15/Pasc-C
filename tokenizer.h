#ifndef KDTK_PARSER
#define KDTK_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "kdtk.h"
#include "symtable.h"
//zoo equal cup alien reason warrior frost session crush mandate vintage hero
typedef int bool;
#define true 1
#define false 0


#include "tokentable.h"

struct token curToken;
struct double_list real_pool;

void print_token(){
  printf("Token Type: %d\tToken Value: %d\t Token Name: %s\t Token loc:%d",curToken.type,curToken.value,curToken.name,loc);
  if(curToken.type == TK_REAL_LIT){
    printf("\t Real Value: %f", get_double_list(&real_pool,curToken.value));
  }
  printf("\n\n");
}

#define CHUNK 2048

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler) {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);
       buffer = (char*) malloc(sizeof(char) * (string_size + 1));
       read_size = fread(buffer, sizeof(char), string_size, handler);
       buffer[string_size] = '\0';
       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }
       fclose(handler);
    }

    return buffer;
}

void CloseFile(char *buff)
{
	free(buff);
}

struct token curToken;
struct double_list real_pool;

void reset_curToken(){
	curToken.value = 0;
	curToken.type = 0;
}
void set_token_type(){
	if(strcmp(curToken.name,"AND")==0){
		curToken.type = TK_AND;
	}
  else if(strcmp(curToken.name,"OR")==0){
		curToken.type = TK_OR;
	}
  else if(strcmp(curToken.name,"XOR")==0){
		curToken.type = TK_XOR;
	}
  else if(strcmp(curToken.name,"NOT")==0){
		curToken.type = TK_NOT;
	}
	else if(strcmp(curToken.name,"BEGIN")==0){
		curToken.type = TK_BEGIN;
	}
	else if(strcmp(curToken.name,"END")==0){
		curToken.type = TK_END;
	}
	else if(strcmp(curToken.name,"BOOLEAN")==0){
		curToken.type = TK_BOOLEAN;
	}
	else if(strcmp(curToken.name,"INTEGER")==0){
		curToken.type = TK_INTEGER;
	}
  else if(strcmp(curToken.name,"REAL")==0){
		curToken.type = TK_REAL;
	}
	else if(strcmp(curToken.name,"BREAK")==0){
		curToken.type = TK_BREAK;
	}
	else if(strcmp(curToken.name,"CHAR")==0){
		curToken.type = TK_CHAR;
	}
	else if(strcmp(curToken.name,"CONTINUE")==0){
		curToken.type = TK_CONTINUE;
	}
  else if(strcmp(curToken.name,"REPEAT")==0){
		curToken.type = TK_REPEAT;
	}
  else if(strcmp(curToken.name,"UNTIL")==0){
		curToken.type = TK_UNTIL;
	}
  else if(strcmp(curToken.name,"WHILE")==0){
		curToken.type = TK_WHILE;
	}
  else if(strcmp(curToken.name,"DO")==0){
		curToken.type = TK_DO;
	}
  else if(strcmp(curToken.name,"IF")==0){
		curToken.type = TK_IF;
	}
  else if(strcmp(curToken.name,"THEN")==0){
		curToken.type = TK_THEN;
	}
  else if(strcmp(curToken.name,"ELSE")==0){
		curToken.type = TK_ELSE;
	}
	else if(strcmp(curToken.name,"WRITE")==0){
		curToken.type = TK_WRITE;
	}
  else if(strcmp(curToken.name,"READ")==0){
		curToken.type = TK_READ;
    curToken.value = 0;
	}
	else if(strcmp(curToken.name,"VAR")==0){
		curToken.type = TK_VAR;
	}
  else if(strcmp(curToken.name,"PROCEDURE")==0){
		curToken.type = TK_PROCEDURE;
	}
  else if(strcmp(curToken.name,"RETURN")==0){
		curToken.type = TK_RET;
	}
  else if(strcmp(curToken.name,"CALL")==0){
		curToken.type = TK_CALL;
	}
  else if(strcmp(curToken.name,"TRUE")==0){
		curToken.type = TK_INT_LIT;
    curToken.value = 1;
	}
  else if(strcmp(curToken.name,"FALSE")==0){
		curToken.type = TK_INT_LIT;
    curToken.value = 0;
	}
	//Not a keyword, it is an identifier. If it's already in the table, we use that. Else, just leave it as an identifier.
	else{
		if(symtab_contains(&main_tab, curToken)){
			curToken = symtab_get(&main_tab,curToken);
		}
		else{
			curToken.type = TK_ID;
		}
	}
}

//Precondition: Token name contains string representation of the integer and type==TK_INT_LIT
//Postcondition: Token value contains the integer
void int_lit_token(){
	int val = 0;
	int i=0;
	while(curToken.name[i]!='\0'){
		val = (curToken.name[i]-'0')+val*10;
		i++;
	}
	curToken.value = val;
}
//Precondition: Token name contains a string representation of the real number and type==TK_REAL_LIT
//Postcondition: Token value contains an index in the real pool
void real_lit_token(){
	double val = 0;
	int decimal = 0;
	int i = 0;
	while(curToken.name[i]!='\0'){
		if(curToken.name[i] == '.'){
			decimal = i+1;//digits from the left where the decimal point is found
			i++;
			continue;
		}
		val = (curToken.name[i]-'0')+val*10;
		i++;
	}
	decimal = i-decimal;
	for(i=0;i<decimal;i++){
		val=val/10.0;
	}
	curToken.value=append_double_list(&real_pool,val);
}

void clear_token()
{

}
void next_token(char *buff, int *aLoc, int len)
{
	int start;
	int loc = *aLoc;
	reset_curToken();
	if(loc>=len){
		curToken.type = TK_EOF;
		return;
	}
	if(isalpha(buff[loc])){
		start = loc;
		while(isalnum(buff[loc]) && (loc-start)<31){
			curToken.name[loc-start] = toupper(buff[loc]);
			loc++;
			//printf("We're at: %c",buff[loc]);
		}
		curToken.name[loc-start] = '\0';
		set_token_type();
	}
	else if(isdigit(buff[loc])){
		start = loc;
		curToken.value = 0;
		curToken.type = TK_INT_LIT;
		while(isdigit(buff[loc]) || buff[loc] == '.'){
			curToken.name[loc-start] = buff[loc];
			if(buff[loc] == '.' && buff[loc+1] != '.'){//TODO: Make ranges work by not parsing as an int
				curToken.type = TK_REAL_LIT;
			}
			loc++;
		}
		curToken.name[loc-start] = '\0';
		if(curToken.type == TK_REAL_LIT){
			real_lit_token();
		}
		else if(curToken.type == TK_INT_LIT){
			int_lit_token();
		}
	}
	else if(!isspace(buff[loc])){
		start = loc;
		if(buff[loc] == '.'){
			curToken.type = TK_PERIOD;
			curToken.name[0] = '.';
			curToken.name[1] = '\0';
			loc+=1;
		}
    else if(buff[loc] == '!' && buff[loc] == '='){
			curToken.type = TK_NOTEQ;
			curToken.name[0] = '!';
			curToken.name[1] = '=';
      curToken.name[2] = '\0';
			loc+=2;
		}
		else if(buff[loc] == '*'){
			curToken.type = TK_TIMES;
			curToken.name[0] = '*';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == '/'){
			curToken.type = TK_DIVIDE;
			curToken.name[0] = '/';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == '+'){
			curToken.type = TK_PLUS;
			curToken.name[0] = '+';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == '-'){
			curToken.type = TK_MINUS;
			curToken.name[0] = '-';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == '('){
			curToken.type = TK_LP;
			curToken.name[0] = '(';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == ')'){
			curToken.type = TK_RP;
			curToken.name[0] = ')';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == ':' && buff[loc+1] == '='){
			curToken.type = TK_ASSIGN;
			curToken.name[0] = ':';
			curToken.name[1] = '=';
			curToken.name[2] = '\0';
			loc+=2;
		}
		else if(buff[loc] == ':'){
			curToken.type = TK_COLON;
			curToken.name[0] = ':';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == ';'){
			curToken.type = TK_SEMICOLON;
			curToken.name[0] = ';';
			curToken.name[1] = '\0';
			loc+=1;
		}
		else if(buff[loc] == ','){
			curToken.type = TK_COMMA;
			curToken.name[0] = ',';
			curToken.name[1] = '\0';
			loc+=1;
		}
    else if(buff[loc] == '='){
			curToken.type = TK_EQ;
			curToken.name[0] = '=';
			curToken.name[1] = '\0';
			loc+=1;
		}
    else if(buff[loc] == '<'){
			curToken.type = TK_LESS;
			curToken.name[0] = '<';
			curToken.name[1] = '\0';
			loc+=1;
      if(buff[loc] == '='){//TODO: Make sure this works this way
        curToken.type = TK_LESSEQ;
  			curToken.name[1] = '=';
  			curToken.name[2] = '\0';
  			loc+=1;
      }
		}
    else if(buff[loc] == '>'){
			curToken.type = TK_GREAT;
			curToken.name[0] = '>';
			curToken.name[1] = '\0';
			loc+=1;
      if(buff[loc] == '='){//TODO: Make sure this works this way
        curToken.type = TK_GREATEQ;
  			curToken.name[1] = '=';
  			curToken.name[2] = '\0';
  			loc+=1;
      }
		}
	}
	else{
		loc++;
		next_token(buff, &loc,len);
	}
	*aLoc = loc;
}

#endif /*KDTK_PARSER*/
