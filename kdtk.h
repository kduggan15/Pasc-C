#ifndef KDTK_LIST
#define KDTK_LIST
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct list
{
  int* arr;
  unsigned int len;
  unsigned int max;
};

struct list make_list()
{
  struct list temp;
  temp.max = 2;
  temp.arr = malloc(temp.max*sizeof(int));
  temp.len = 0;
  return temp;
}

struct list make_list_n(int n)
{
  int max = 2;
  while (max<n) max*=2;
  struct list temp;
  temp.max = max;
  temp.arr = calloc(temp.max, sizeof(int));
  temp.len = n;
  return temp;
}

void destroy_list(struct list *l)
{
  free(l->arr);
}

int append_list(struct list *l, int n)
{
  if(l->len>=l->max)
  {
    printf("len>=max\n");
    int* temp = malloc(l->max*2*sizeof(int));
    memcpy(temp,l->arr,l->len*sizeof(int));
    free(l->arr);
    l->arr = temp;
    l->max = l->max*2;
  }
  l->arr[l->len] = n;
  l->len++;
  return l->len-1;
}

int get_list(struct list *l, int i)
{
  if(i>=l->len)
  {
    printf("Out of Bounds Error");
  }
  return l->arr[i];
}

void set_list(struct list *l, int i, int n)
{
  if(i<=l->len)
  {
    printf("Out of Bounds Error");
  }
  l->arr[i] = n;
}
void print_list(struct list l)
{
  for(int i=0; i<l.len; i++)
  {
    printf("%d, ", l.arr[i]);
  }
  printf("\n");
}


struct double_list
{
  double* arr;
  unsigned int len;
  unsigned int max;
};

struct double_list make_double_list()
{
  struct double_list temp;
  temp.max = 2;
  temp.arr = malloc(temp.max*sizeof(double));
  temp.len = 0;
  return temp;
}

struct double_list make_double_list_n(int n)
{
  int max = 2;
  while (max<n) max*=2;
  struct double_list temp;
  temp.max = max;
  temp.arr = calloc(temp.max, sizeof(double));
  temp.len = n;
  return temp;
}

void destroy_double_list(struct double_list *l)
{
  free(l->arr);
}

int append_double_list(struct double_list *l, double n)
{
  if(l->len>=l->max)
  {
    printf("len>=max\n");
    double* temp = malloc(l->max*2*sizeof(double));
    memcpy(temp,l->arr,l->len*sizeof(double));
    free(l->arr);
    l->arr = temp;
    l->max = l->max*2;
  }
  l->arr[l->len] = n;
  l->len++;
  return l->len-1;
}

double get_double_list(struct double_list *l, int i)
{
  if(i>=l->len)
  {
    printf("Out of Bounds Error");
  }
  return l->arr[i];
}

void set_double_list(struct double_list *l, int i, double n)
{
  if(i<=l->len)
  {
    printf("Out of Bounds Error");
  }
  l->arr[i] = n;
}
void print_double_list(struct double_list l)
{
  for(int i=0; i<l.len; i++)
  {
    printf("%f, ", l.arr[i]);
  }
  printf("\n");
}
#endif /*KDTK_LIST*/
