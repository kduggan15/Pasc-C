/*
Basic stack machine idea. Every value on the stack is 32 bit represented as 4 char bytes
Code array is byte array
Data array is byte array
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STACK_SIZE  1024
#define DATA_SIZE   1024

#define DEBUG 0
#include "opcodes.h"


int ip,dp,sp;
int* stack;
char* code;
int* data;

void run(){
  float* p;
  int running =1;
  int addr;
  int val;
  float fval;
  ip = 0;
  sp = 0;
  dp = 0;

  while(running){
    if(DEBUG){
      printf("Code at ip: %x\n ip is: %x\n",ip,code[ip]);
      for(int i=0; i<=sp; i++){
        printf(" %d,%d\n",i,stack[i]);
      }
    }

    switch (code[ip++]){
      case OP_HALT:
        exit(0);
      case OP_PUSH:
        addr = *(int*)(code+ip);
        ip+= sizeof(int);
        val = *(int*)(data+addr);
        stack[sp++] = val;
        break;
      case OP_POP:
        addr = *(int*)(code+ip);
        ip+= sizeof(int);
        val = stack[--sp];//*(int*)(data+addr);
        *(int*)(data+addr) = val;
        break;
      case OP_PUSHI:
        val = *(int*)(code+ip);
        ip+= sizeof(int);
        stack[sp++] = val;
        break;
      case OP_POPI:
        sp--;
        break;
      case OP_REM:
        sp--;
        break;
      case OP_DUP:
        stack[++sp] = stack[sp];
        break;
      case OP_EXCH:
        val = stack[sp-2];
        stack[sp-2] = stack[sp-1];
        stack[sp-1] = val;
        break;
      case OP_ADD:
        stack[sp-2]+=stack[sp-1];
        --sp;
        break;
      case OP_NEG:
        stack[sp-1] = -stack[sp-1];
        break;
      case OP_SUB:
        stack[sp-2]-=stack[sp-1];
        --sp;
        break;
      case OP_MUL:
        stack[sp-2]*=stack[sp-1];
        --sp;
        break;
      case OP_DIV:
        stack[sp-2]/=stack[sp-1];
        --sp;
        break;
      case OP_SHL:
        stack[sp-2]<<=stack[sp-1];
        --sp;
        break;
      case OP_SHR:
        stack[sp-2]>>=stack[sp-1];
        --sp;
        break;
      case OP_PRNTINT:
        printf("%d\n",stack[sp-1]);
        --sp;
        break;
      case OP_PRNTFLT:
        p = (float*)&stack[sp-1];
        printf("%f\n",p[0]);
        --sp;
        break;
      case OP_PRNTCHR:
        printf("%c\n", stack[sp-1]);
        --sp;
        break;
      case OP_PRNTBOOL://TODO: Could be implemented better
        if(stack[sp-1] == 0)
          printf("False\n");
        else
          printf("True\n");
        --sp;
        break;
      case OP_READINT:
        scanf("%d",&stack[sp]);
        sp++;
        break;
      case OP_READFLT:
        p = (float*)&stack[sp];
        scanf("%f",&p[0]);
        sp++;
      case OP_AND:
        stack[sp-2]&=stack[sp-1];
        --sp;
        break;
      case OP_OR:
        stack[sp-2]|=stack[sp-1];
        --sp;
        break;
      case OP_XOR:
        stack[sp-2]^=stack[sp-1];
        --sp;
        break;
      case OP_AND_B:
        stack[sp-2] = stack[sp-2]&&stack[sp-1];
        --sp;
        break;
      case OP_OR_B:
        stack[sp-2] = stack[sp-2]||stack[sp-1];
        --sp;
        break;
      case OP_XOR_B:
        stack[sp-2] = stack[sp-2]!=stack[sp-1];
        --sp;
        break;
      case OP_EQL:
        stack[sp-2] = stack[sp-2]==stack[sp-1];
        --sp;
        break;
      case OP_LEQ:
        stack[sp-2] = stack[sp-2]<=stack[sp-1];
        --sp;
        break;
      case OP_LSS:
        stack[sp-2] = stack[sp-2]<stack[sp-1];
        --sp;
        break;
      case OP_GEQ:
        stack[sp-2] = stack[sp-2]>=stack[sp-1];
        --sp;
        break;
      case OP_GTR:
        stack[sp-2] = stack[sp-2]>stack[sp-1];
        --sp;
        break;
      case OP_NOT:
        stack[sp-2] = !stack[sp-2];
        --sp;
        break;
      case OP_JMP:
        addr = *(int*)(code+ip);
        ip = addr;
        --sp;
        break;
      case OP_JTRU:
        addr = *(int*)(code+ip);
        if(stack[sp-1])
          ip = addr;
        else
          ip += sizeof(int);
        --sp;
        break;
      case OP_JFAL:
        addr = *(int*)(code+ip);
        if(!stack[sp-1])
          ip = addr;
        else
          ip += sizeof(int);
        --sp;
        break;
      case OP_CVR:
        p = (float*)&stack[sp-1];
        p[0] = (float)stack[sp-1];
        break;
      case OP_CVI:
        p = (float*)&stack[sp-1];
        stack[sp-1] = (int)p[0];
        break;
      case OP_FADD:
        p = (float*)&stack[sp-2];
        p[0]+=p[1];
        --sp;
        break;
      case OP_FSUB:
        p = (float*)&stack[sp-2];
        p[0]-=p[1];
        --sp;
        break;
      case OP_FMUL:
        p = (float*)&stack[sp-2];
        p[0]*=p[1];
        --sp;
        break;
      case OP_FDIV:
        p = (float*)&stack[sp-2];
        p[0]/=p[1];
        --sp;
        break;
      case OP_FNEG:
        p = (float*)&stack[sp-1];
        p[0] = -p[0];
        break;
      case OP_CALL:
        addr = stack[sp];
        stack[sp] = ip;
        ip = addr;
        break;
      case OP_RET:
        ip = stack[sp];
        sp--;
        break;
    }

  }
}

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

void make_fake_data(){
  data[0]=2;
  data[1]=0;
  data[2]=0;
  data[3]=0;
}

int main(){
  code = ReadFile("out.o");
  data = malloc(DATA_SIZE*sizeof(char));
  //make_fake_data();
  stack = malloc(STACK_SIZE*sizeof(int));
  run();
  free(code);
  return 0;
}
