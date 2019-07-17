#ifndef PASCC_PARSER
#define PASCC_PARSER

#define P_DEBUG 0

type E();
void decls();
void stat();
void stats();
void begin_stat();
//int ip;

#define DECL_LIST_LEN 5
struct token id_list[DECL_LIST_LEN];//Technical limitation. declaration list length

void gen_op(unsigned char b){
	//fprintf(outf, "%c", b);
	if(P_DEBUG) printf("Generating OP %x at %lx\n",b,ftell(outf));
	fputc(b,outf);
	ip+=1;
}

void gen_i(int b){
  unsigned char* p = (unsigned char*)&b;
	//fprintf(outf,"%c",p[0]);
	//fprintf(outf,"%c",p[1]);
	//fprintf(outf,"%c",p[2]);
	//fprintf(outf,"%c",p[3]);
	if(P_DEBUG) printf("Generating int %x at %lx\n",b,ftell(outf));
	fputc(p[0],outf);
	fputc(p[1],outf);
	fputc(p[2],outf);
	fputc(p[3],outf);
	ip+=4;
}

void gen_f(float b){
  unsigned char* p = (unsigned char*)&b;
	//fprintf(outf,"%c",p[0]);
	//fprintf(outf,"%c",p[1]);
	//fprintf(outf,"%c",p[2]);
	//fprintf(outf,"%c",p[3]);
	fputc(p[0],outf);
	fputc(p[1],outf);
	fputc(p[2],outf);
	fputc(p[3],outf);
	ip+=4;
}

void gen_addr(int b){
  unsigned char* p = (unsigned char*)&b;
	//fprintf(outf,"%c",p[0]);
	//fprintf(outf,"%c",p[1]);
	//fprintf(outf,"%c",p[2]);
	//fprintf(outf,"%c",p[3]);
	if(P_DEBUG) printf("Generating addr %x at %lx\n",b,ftell(outf));
	fputc(p[0],outf);
	fputc(p[1],outf);
	fputc(p[2],outf);
	fputc(p[3],outf);
	ip+=4;
}

//t1 is just under t2 on the stack, t1 is to the left of t2
type code_gen_and(type t1, type t2){
	if(t1 == B && t2 == B){
		gen_op(OP_AND_B);
		return B;
	}
	else if(t1 == I && t2 == I){
		gen_op(OP_AND);
		return I;
	}
}
type code_gen_or(type t1, type t2){
	if(t1 == B && t2 == B){
		gen_op(OP_OR_B);
		return B;
	}
	else if(t1 == I && t2 == I){
		gen_op(OP_OR);
		return I;
	}
}
type code_gen_xor(type t1, type t2){
	if(t1 == B && t2 == B){
		gen_op(OP_XOR_B);
		return B;
	}
	else if(t1 == I && t2 == I){
		gen_op(OP_XOR);
		return I;
	}
}
type code_gen_eq(type t1, type t2){
	gen_op(OP_EQL);
	return B;
}
type code_gen_add(type t1, type t2){
  if(t1 == I && t2 == I){
    gen_op(OP_ADD);
    return I;
  }
  else if(t1 == I && t2 == R){
    gen_op(OP_EXCH);
    gen_op(OP_CVR);
    gen_op(OP_EXCH);
    gen_op(OP_FADD);
    return R;
  }
  else if(t1 == R && t2 == I){
    gen_op(OP_CVR);
    gen_op(OP_FADD);
    return R;
  }
  else if(t1 == R && t2 == R){
    gen_op(OP_FADD);
    return R;
  }
  else{
    error(E_TYPE);
  }
}

type code_gen_sub(type t1, type t2){
  if(t1 == I && t2 == I){
    gen_op(OP_SUB);
    return I;
  }
  else if(t1 == I && t2 == R){
    gen_op(OP_EXCH);
    gen_op(OP_CVR);
    gen_op(OP_EXCH);
    gen_op(OP_FSUB);
    return R;
  }
  else if(t1 == R && t2 == I){
    gen_op(OP_CVR);
    gen_op(OP_FSUB);
    return R;
  }
  else if(t1 == R && t2 == R){
    gen_op(OP_FSUB);
    return R;
  }
  else{
    error(E_TYPE);
  }
}

type code_gen_mul(type t1, type t2){
  if(t1 == I && t2 == I){
    gen_op(OP_MUL);
    return I;
  }
  else if(t1 == I && t2 == R){
    gen_op(OP_EXCH);
    gen_op(OP_CVR);
    gen_op(OP_EXCH);
    gen_op(OP_FMUL);
    return R;
  }
  else if(t1 == R && t2 == I){
    gen_op(OP_CVR);
    gen_op(OP_FMUL);
    return R;
  }
  else if(t1 == R && t2 == R){
    gen_op(OP_FMUL);
    return R;
  }
  else{
    error(E_TYPE);
  }
}

type code_gen_divide(type t1, type t2){
  if(t1 == I && t2 == I){
    gen_op(OP_DIV);
    return I;
  }
  else if(t1 == I && t2 == R){
    gen_op(OP_EXCH);
    gen_op(OP_CVR);
    gen_op(OP_EXCH);
    gen_op(OP_FDIV);
    return R;
  }
  else if(t1 == R && t2 == I){
    gen_op(OP_CVR);
    gen_op(OP_FDIV);
    return R;
  }
  else if(t1 == R && t2 == R){
    gen_op(OP_FDIV);
    return R;
  }
  else{
    error(E_TYPE);
  }
}

void match(int t){
  //printf("Matched!\n");
  //print_token();
	if(curToken.type!=t){
    printf("Expecting token %d\n", t);
		error(E_MATCH);
	}
	else{
		next_token(source, &loc,len);
	}
}

type F(){
  type t1;
	switch (curToken.type) {
		case TK_INT_LIT:
			printf("INTLIT %d\n", curToken.value);
			gen_op(OP_PUSHI);
			gen_i(curToken.value);
			match(TK_INT_LIT);
			t1 = I;
			break;
		case TK_REAL_LIT:
			printf("REALLIT %f\n", get_double_list(&real_pool,curToken.value));
      gen_op(OP_PUSHI);
			gen_f(get_double_list(&real_pool,curToken.value));
			match(TK_REAL_LIT);
			t1 = R;
			break;
    case TK_LP:
      match(TK_LP);
      t1 = E();
      match(TK_RP);
      break;
		case TK_INT_VAR:
      printf("INTVAR %s\n", curToken.name);
      gen_op(OP_PUSH);
      gen_addr(symtab_get(&main_tab, curToken).value);
      match(TK_INT_VAR);
      t1 = I;
			break;
		case TK_REAL_VAR://Needs to be modified at tokenizer, decl, and stats
			printf("FLOATVAR %s\n", curToken.name);
			gen_op(OP_PUSH);
      gen_addr(symtab_get(&main_tab, curToken).value);//:thinking_emoji:
      match(TK_REAL_VAR);
      t1 = R;
			break;
		case TK_BOOL_VAR:
			printf("BOOLVAR %s\n", curToken.name);
      gen_op(OP_PUSH);
      gen_addr(symtab_get(&main_tab, curToken).value);
      match(TK_BOOL_VAR);
      t1 = B;
			break;
		case TK_CHAR_VAR:
			printf("CHARVAR %s\n", curToken.name);
      gen_op(OP_PUSH);
      gen_addr(symtab_get(&main_tab, curToken).value);
      match(TK_CHAR_VAR);
      t1 = C;
			break;
		case TK_MINUS://TODO: UNTESTED
			printf("NEGATE\n");
			t1 = F();
			if(t1 == I)
				gen_op(OP_NEG);
			else if(t1 == R);
				gen_op(OP_FNEG);
			break;
	}
  return t1;
}

type T(){
	type t1, t2;
	t1 = F();
	while(curToken.type == TK_TIMES || curToken.type == TK_DIVIDE){
		if(curToken.type == TK_TIMES){
			match(TK_TIMES);
			t2 = F();
			printf("TIMES\n");//CODE GEN
      t1 = code_gen_mul(t1,t2);
		}
		else if(curToken.type == TK_DIVIDE){
			match(TK_DIVIDE);
			t2 = T();
			printf("DIVIDE\n");//CODE GEN
      t1 = code_gen_divide(t1,t2);
		}
	}
  return t1;
}

type E(){
	type t1,t2;
	t1 = T();
	while(curToken.type == TK_PLUS || curToken.type == TK_MINUS ||
				curToken.type == TK_OR || curToken.type == TK_XOR || curToken.type == TK_EQ ||
				curToken.type == TK_LESS || curToken.type == TK_LESSEQ ||
				curToken.type == TK_GREAT || curToken.type == TK_GREATEQ){
		if(curToken.type == TK_PLUS){
			match(TK_PLUS);
			t2 = T();
			printf("PLUS\n");//CODE GEN
			t1 = code_gen_add(t1,t2);
		}
		else if(curToken.type == TK_MINUS){
			match(TK_MINUS);
			t2 = T();
			printf("MINUS\n");//CODE GEN
      t1 = code_gen_sub(t1,t2);
		}
		else if(curToken.type == TK_OR){
			match(TK_OR);
			t2 = T();
			printf("OR\n");//CODE GEN
      t1 = code_gen_or(t1,t2);
		}
		else if(curToken.type == TK_XOR){
			match(TK_XOR);
			t2 = T();
			printf("XOR\n");//CODE GEN
      t1 = code_gen_xor(t1,t2);
		}
		else if(curToken.type == TK_EQ){
			match(TK_EQ);
			t2 = T();
			printf("EQ\n");//CODE GEN
      t1 = code_gen_eq(t1,t2);
		}
		else if(curToken.type == TK_LESS){
			match(TK_LESS);
			t2 = T();
			printf("LESS\n");//CODE GEN
			gen_op(OP_LSS);
			t1 = B;
		}
		else if(curToken.type == TK_LESSEQ){
			match(TK_LESSEQ);
			t2 = T();
			printf("LESSEQ\n");//CODE GEN
			gen_op(OP_LEQ);
			t1 = B;
		}
		else if(curToken.type == TK_GREAT){
			match(TK_GREAT);
			t2 = T();
			printf("GREAT\n");//CODE GEN
			gen_op(OP_GTR);
			t1 = B;
		}
		else if(curToken.type == TK_GREATEQ){
			match(TK_GREATEQ);
			t2 = T();
			printf("GREATEQ\n");//CODE GEN
			gen_op(OP_GEQ);
			t1 = B;
		}
	}
  return t1;
}

//Toy parser used to test expressions
void parse_all(){
  type t1;
	next_token(source, &loc,len);
	match(TK_WRITE);
	match(TK_LP);
	t1 = E();
	match(TK_RP);
	match(TK_EOF);
  if(t1 == I){
	  gen_op(OP_PRNTINT);
  }
  else if(t1 == R){
    gen_op(OP_PRNTFLT);
  }
	gen_op(OP_HALT);
}


/*
Grammaer idea:
  <var_decl> ->
                  TK_VAR <name_list> TK_COLON <name_type>
  <name_list> ->  TK_ID TK_COMMA <name_list>
*/
void name_type(int i){
	//printf("There are %d vars here\ntoken type should be integer %d\n",i,curToken.type);
	if(curToken.type == TK_INTEGER){
		match(TK_INTEGER);
		for(int j=0;j<=i;j++){
			id_list[j].type = TK_INT_VAR;
			symtab_add_key(&main_tab,id_list[j]);
		}
	}
	else if(curToken.type == TK_REAL){
		match(TK_REAL);
		for(int j=0;j<=i;j++){
			id_list[j].type = TK_REAL_VAR;
			symtab_add_key(&main_tab,id_list[j]);
		}
	}
	else if(curToken.type == TK_BOOLEAN){
		match(TK_BOOLEAN);
		for(int j=0;j<=i;j++){
			id_list[j].type = TK_BOOL_VAR;
			symtab_add_key(&main_tab,id_list[j]);
		}
	}
	else if(curToken.type == TK_CHAR){
		match(TK_CHAR);
		for(int j=0;j<=i;j++){
			id_list[j].type = TK_CHAR_VAR;
			symtab_add_key(&main_tab,id_list[j]);
		}
	}
  	//Only works for integer now and doesn't do anything. This should go back and modify stuff added to the symtab
}
void var_decl(){
	int i=0;
  match(TK_VAR);
  while(curToken.type == TK_ID){
    curToken.value = datap++;
    //curToken.type = TK_INT_VAR;
    //symtab_add_key(&main_tab,curToken);
		if(i<=DECL_LIST_LEN)
			id_list[i++] = curToken;
		//printf("number of ids found: %d\nGiven pointer: %d\n",i,datap);
    match(TK_ID);
    if(curToken.type == TK_COMMA){
      match(TK_COMMA);
    }
  }
  match(TK_COLON);
  name_type(i);
}

void proc_decl(){
	match(TK_PROCEDURE);
	if(curToken.type == TK_ID){
		curToken.value = ftell(outf);
		curToken.type = TK_PROCEDURE;
		symtab_add_key(&main_tab,curToken);
	}
	int hole = ftell(outf);
	begin_stat();
	gen_op(OP_RET);
	int save = ftell(outf);
	fseek(outf,hole,SEEK_SET);
	gen_addr(save);
	fseek(outf,save,SEEK_SET);

}

void decl_tail(){
  if(curToken.type == TK_SEMICOLON){
    match(TK_SEMICOLON);
    decls();
  }
}

void decls(){
  while(curToken.type == TK_VAR || curToken.type == TK_PROCEDURE){
    if(curToken.type == TK_VAR){
      var_decl();
      decl_tail();
    }
		else if(curToken.type == TK_PROCEDURE){
			proc_decl();
			decl_tail();
		}
  }
}

void condition(){
	type t = E();
	if(t!=B){
		printf("Condition does not evaluate to a boolean\n");
		error(E_TYPE);
	}
}

void repeat_st(){
	match(TK_REPEAT);
	int label = ftell(outf);//not exactly sure why -4 makes this work. nvm... OP_JFAL was broken
	printf("LABEL R %d\n",label);
	printf("LABEL R %d\n",ip);
	stats();
	match(TK_UNTIL);
	condition();
	printf("REPEAT %d\n",label);
	gen_op(OP_JFAL);
	gen_addr(label);
}

void while_st(){
	match(TK_WHILE);
	int label = ftell(outf);
	printf("LABEL W %x\n",label);
	printf("LABEL W %x\n",ip);
	condition();
	match(TK_DO);
	gen_op(OP_JFAL);
	int hole = ftell(outf);
	printf("HOLE W %x\n", hole);
	gen_addr(0);
	stat();
	gen_op(OP_JMP);
	gen_addr(label);
	int save = ftell(outf);
	printf("SAVE W %x\n", save);
	printf("SAVE W %x\n", ip);
	fseek(outf,hole,SEEK_SET);
	gen_addr(save);
	fseek(outf,save,SEEK_SET);
}

void if_st(){
	int save,hole2;
	match(TK_IF);
	condition();
	gen_op(OP_JFAL);
	int hole = ftell(outf);
	gen_addr(0);
	match(TK_THEN);
	stat();
	if(curToken.type == TK_ELSE){//NOT WORKING AT THE MOMENT
		match(TK_ELSE);
		gen_op(OP_JMP);
		hole2 = ftell(outf);
		gen_addr(0);
		save = ftell(outf);
		fseek(outf,hole,SEEK_SET);
		gen_addr(save);
		fseek(outf,save,SEEK_SET);
		stat();

		save = ftell(outf);
		fseek(outf,hole2,SEEK_SET);
		gen_addr(save);
		fseek(outf,save,SEEK_SET);

	}
	else{
		save = ftell(outf);
		fseek(outf,hole,SEEK_SET);
		gen_addr(save);
		fseek(outf,save,SEEK_SET);
	}

}

void stat(){
  type t1;
  int addr;
  switch(curToken.type){
    case TK_INT_VAR:
      addr = symtab_get(&main_tab, curToken).value;
      match(TK_INT_VAR);
      match(TK_ASSIGN);
      t1 = E();
      printf("ASSIGNMENT\n");
			if(t1==R)
				gen_op(OP_CVI);
      gen_op(OP_POP);
      gen_addr(addr);
      break;
		case TK_REAL_VAR:
			addr = symtab_get(&main_tab, curToken).value;
			match(TK_REAL_VAR);
			match(TK_ASSIGN);
			t1 = E();
			printf("ASSIGNMENT\n");
			if(t1!=R)//This logic allows typecasting of anything into a real. Might not be the best idea...
				gen_op(OP_CVR);
			gen_op(OP_POP);
	    gen_addr(addr);
			break;
		case TK_BOOL_VAR:
			addr = symtab_get(&main_tab, curToken).value;
			match(TK_BOOL_VAR);
      match(TK_ASSIGN);
      t1 = E();
      printf("ASSIGNMENT\n");
			if(t1==R)
				gen_op(OP_CVI);
			if(t1!=B){//convert to a proper boolean
				gen_op(OP_PUSHI);
				gen_i(1);
				gen_op(OP_AND);
			}
      gen_op(OP_POP);
      gen_addr(addr);
      break;
		case TK_CHAR_VAR:
			addr = symtab_get(&main_tab, curToken).value;
			match(TK_CHAR_VAR);
      match(TK_ASSIGN);
      t1 = E();
      printf("ASSIGNMENT\n");
			if(t1==R)
				gen_op(OP_CVI);
      gen_op(OP_POP);
      gen_addr(addr);
      break;
    case TK_WRITE:
      match(TK_WRITE);
      match(TK_LP);
      t1 = E();
      match(TK_RP);
      printf("PRINT %d\n", t1);
      if(t1 == I){
    	  gen_op(OP_PRNTINT);
      }
      else if(t1 == R){
        gen_op(OP_PRNTFLT);
      }
			else if(t1 == B){
        gen_op(OP_PRNTBOOL);
      }
			else if(t1 == C){
        gen_op(OP_PRNTCHR);
      }
			break;
		case TK_READ:
			match(TK_READ);
			match(TK_LP);
			addr = addr = symtab_get(&main_tab, curToken).value;
			if(curToken.type == TK_INT_VAR){
				match(TK_INT_VAR);
				gen_op(OP_READINT);
				gen_op(OP_POP);
				gen_addr(addr);
			}
			else if(curToken.type == TK_REAL_VAR){//TODO: not working
				match(TK_REAL_VAR);
				gen_op(OP_READFLT);
				gen_op(OP_POP);
				gen_addr(addr);
			}
			//something here to save int an into the program
			match(TK_RP);
			break;
		case TK_REPEAT:
			repeat_st();
			break;
		case TK_WHILE:
			while_st();
			break;
		case TK_IF:
			if_st();
			break;
		case TK_ELSE:
			break;
		case TK_BEGIN:
			begin_stat();
			break;
		case TK_CALL:
			match(TK_CALL);
			gen_op(OP_CALL);
			gen_addr(symtab_get(&main_tab,curToken).value);
			match(TK_PROCEDURE);
			break;
		case TK_RET:
			match(TK_RET);
			gen_op(OP_RET);
			break;
		case TK_ID:
			error(E_UNKNOWN_TOKEN);
  }
}

void stat_tail(){
  if(curToken.type == TK_SEMICOLON){
    match(TK_SEMICOLON);
    stats();
  }
}

void stats(){
  stat();
  stat_tail();
}

void begin_stat(){
  match(TK_BEGIN);
  stats();
  match(TK_END);
}

void body(){
  begin_stat();
}
void program(){
  next_token(source, &loc,len);
  decls();
  body();
  match(TK_PERIOD);
  match(TK_EOF);
  gen_op(OP_HALT);
}

#endif /*PASCC_PARSER*/
