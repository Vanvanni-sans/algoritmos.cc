#include <stdio.h>
#include <stdbool.h>
#include "ListDE.h"

int main(){

TListDE L;
int erro = 0;

initList(&L);

  for (int i=0; i<5; i++){
    erro = insertLeft(i, &L);
    if(erro){
      printf("memoria insulficiente");
    }
  printList(L, false);
  puts("\n");
  }

  for (int i=0; i<5; i++){
    erro = insertRight(i, &L);
    if(erro){
      printf("memoria insulficiente");
    }
  printList(L, false);
  puts("\n");
  }

  deletnum(&L, 7);
  printList(L, false);
  puts("\n");
  

  deletList(&L);
  printList(L, false);
}
