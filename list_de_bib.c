#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ListDE.h"

void initList(TListDE *L){
  L->first = NULL;
  L->last = NULL;
  L->len = 0;
}

void deletList(TListDE *L){
  Tnode *aux = L -> first;
  while (aux){
    L->first = L->first->next;
    free(aux);
    aux=L->first;
  }
  L->len = 0;
}

void printList(TListDE L, bool dir){
  Tnode *aux;

  if(!dir){
    printf("First ->");
    aux = L.first;
    while(aux){
      printf("[%d]->", aux->info);
      aux = aux -> next;
    }
    printf("[NULL]");
  }else{
    printf("Last ->");
    aux = L.last;
    while(aux){
      printf("[%d]->", aux->info);
      aux = aux -> prev;
    }
    printf("[NULL]");
  }
  return;
}

int insertLeft(Tdata x, TListDE *L){
  Tnode *aux;
  aux = (Tnode*)malloc(sizeof(Tnode));
  if (aux == NULL)//falha na alocação
    return 1;//sinaliza com erro, deixando a lista original intacta 
  else{
    aux->info = x;        //atribui x para a informação
    aux->next = L->first;
    aux->prev = NULL;
    if(L->first != NULL)
      L->first->prev = aux;
    L->first = aux;
    if(L->last==NULL)
      L->last =aux;
    L->len++;
    return 0;
  }
}

int insertRight(Tdata x, TListDE *L){
  Tnode *aux =(Tnode*)malloc(sizeof(Tnode));
  if (aux == NULL)//falha na alocação
    return 1;//sinaliza com erro, deixando a lista original intacta 
  else{
    aux->info = x;        //atribui x para a informação
    aux->next = NULL;
    aux->prev = L->last;
    if(L->first == NULL)
      L->first = L->last = aux;
    else{  
    L->last->next = aux;
    L->last = aux;

    }
    L->len++;    
    return 0;
  }
}

void deletfirst(TListDE *L){
  Tnode *aux;
  aux = L->first;
  L->first = L->first->next;
  free(aux);
  L->first->prev=NULL;
  L->len --;
  if(L->len == 0)
    L->last = NULL;
  return;
}

void deletlast(TListDE *L){
  Tnode *aux;
  aux = L->last;
  L->last = L->last->prev;
  free(aux);
  L->last->next=NULL;
  L->len --;
  if(L->len == 0)
    L->first = NULL;
  return;
}

void deletnum(TListDE *L, int n){
Tnode *aux = L-> first, *aux2, *aux3, *auxpos;
  if(n==0)
    deletfirst(L);
  else if(n==L->len-1)
    deletlast(L);
  else if(n==1){
    aux = L->first->next;
    L->first->next=aux->next;
    free(aux);
    aux2 = L->first->next;
    aux2 -> prev = L->first;
  }else if(n==L->len-2){
      aux = L->last->prev;
      L->last->prev=aux->prev;
      free(aux);
      aux2 = L->last->prev;
      aux2 -> next = L->last;
  }
  else if(n>1 && n<L->len-2){
    for(int i = 0; i<n/2 ;i++){
      aux2 = aux->next;
      aux = aux2->next;
    }
    if(n%2==0){//numeros pares
      aux3=aux->next;
      free(aux);
      aux2->next = aux3;
      aux3->prev = aux2;
    }else{//numeros impares
      aux3=aux->next;
      aux2=aux3->next;
      free(aux3);
      aux->next=aux2;
      aux2->prev=aux;
    }
  }
}

