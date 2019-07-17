#ifndef KDTK_SYMTBLE
#define KDTK_SYMTBLE

#include "tokentable.h"

#define TABLE_SIZE 1024

struct token nullToken;

struct symtab
{
  struct token* arr;
  unsigned int len;
  unsigned int max;
};

struct symtab make_symtab(){
	nullToken.value = 0;
	nullToken.type = TK_NULL;
	struct symtab temp;
  temp.max = 2;//TODO: This is the maximum number of variable. Make it properly dynamic.
  temp.arr = malloc(temp.max*sizeof(struct token));
  temp.len = 0;
  return temp;
}

void destroy_symtab(struct symtab *l)
{
  free(l->arr);
}

int symtab_contains(struct symtab *l, struct token n){
	//printf("Checking from table\n");
	for(int i=0;i<l->len;i++){
		if(strcmp(l->arr[i].name,n.name)==0){
			return 1;
		}
	}
	return 0;
}

struct token symtab_get(struct symtab *l, struct token n){
	//printf("Getting from table\n");
	for(int i=0;i<l->len;i++){
		if(strcmp(l->arr[i].name,n.name)==0){
			return l->arr[i];
		}
	}
	return nullToken;
}

int symtab_add_key(struct symtab *l, struct token n)
{
	//printf("Sizeof token: %ld\n", sizeof(struct token));
  if(l->len>=l->max)
  {
		//printf("h\n");
    struct token* temp = malloc(l->max*2*sizeof(struct token));
    memcpy(temp,l->arr,l->len*sizeof(struct token));
    free(l->arr);
    l->arr = temp;
    l->max = l->max*2;
  }
	//printf("%s\n",n.name);
  l->arr[l->len] = n;
  l->len++;
  return l->len-1;
}

int symtab_print(struct symtab *l){
	printf("printing table\n");
	for(int i=0;i<l->len;i++){
		printf("i: %d\t name:%s\n",i,l->arr[i].name);
	}
	return 0;
}
#endif /*KDTK_SYMTBLE*/
