#ifndef KDTK_PASCC_ERROR
#define KDTK_PASCC_ERROR

#include "tokenizer.h"

#define E_MATCH   1
#define E_TYPE    2
#define E_UNKNOWN_TOKEN 3

void error(int E){
  switch (E){
    case E_MATCH:
      printf("There was an error in matching the token\n");
      print_token();
      break;
    case E_TYPE:
      printf("There was a type error\n");
      print_token();
      break;
    case E_UNKNOWN_TOKEN:
      printf("Unidentified token. Was this declared? %s\n",curToken.name);
      print_token();
      break;
  }
  exit(1);
}

#endif /*KDTK_PASCC_ERROR*/
