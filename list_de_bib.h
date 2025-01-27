#include <stdbool.h>

typedef int Tdata;//tipo de dado de armazenamento

typedef struct Tnode{//def do tipo do nó
  Tdata info;//dado armazenado
  struct Tnode *prev;//ponteiro para o nó anterior
  struct Tnode *next;//ponteiro para o nó posterior
} Tnode;
//def do tipo listaDE

typedef struct TListDE{
  Tnode *first;
  Tnode *last;
  int len;
} TListDE;

//funçao de incialização da lista
void initList (TListDE *L);

void deletList (TListDE *L);

void deletfirst(TListDE *L);

void deletnum(TListDE *L, int n);

void deletlast(TListDE *L);

void printList(TListDE L, bool dir);

int insertLeft(Tdata x, TListDE *L);

int insertRight(Tdata x, TListDE *L);
