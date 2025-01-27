// ordena2.c
// Testa a estabilidade dos algoritmos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Declaração do tipo de dado booleano 
typedef enum {false, true} bool;

// Declaração do tipo TNum
typedef short Tnum;

// Tipo de dado a ser ordenado
typedef struct {
	short key; // chave de ordenação
	short seq; // sequência de inserção no conjunto
} Tdado;

// Função de troca
void troca(Tdado *x, Tdado *y) {
	Tdado aux = *x;
	*x = *y;
	*y = aux;
}

// Função para escrever um vetor
void escreve(Tdado V[], Tnum n) {
	printf("[");
	for (Tnum i = 0; i < n; i++) {
		printf("(%hd, %hd)", V[i].key, V[i].seq);
		if (i < n - 1) {
			printf(", ");
      }
	}
	printf("]\n");
}

// Função bubbleSort
void bubbleSort(Tdado dados[], Tnum  n) {
  	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
			if (dados[j].key < dados[j - 1].key) {
				troca(&dados[j], &dados[j - 1]);
         }
      }
   }
} 

// Função shakerSort
void shakerSort(Tdado dados[], Tnum n) {
	bool trocou;
	
   do {
		trocou = false;
		for (Tnum i = (n - 1); i > 0; i--) {
			if(dados[i - 1].key > dados[i].key) {
				troca(&dados[i - 1], &dados[i]);
            trocou = true;
         }
		}
		for (Tnum i = 1; i < n; i++) {
			if (dados[i - 1].key > dados[i].key){
            troca(&dados[i - 1], &dados[i]);
         	trocou = true;
         }
      }
   } while (trocou); 
}

// Função insertionSort
void insertionSort(Tdado dados[], Tnum n) {
   for (Tnum i = 1; i < n; i++) {
		Tdado aux = dados[i];
		Tnum j = 0;
      for (j = i; (j > 0) && (aux.key < dados[j-1].key); j--) {
         dados[j] = dados[j - 1];
      }
      dados[j] = aux;
   }
}

// Função selectionSort
void selectionSort(Tdado dados[], Tnum n) {
	for (Tnum i = 0; i < (n - 1); i++) {
   	// encontra o menor elemento
		Tnum min = i;
		for (Tnum j = i + 1; j < n; j ++) {
			if (dados[j].key < dados[min].key) {
				min = j;
         }
      }
      // Troca a posição atual com o menor elemento do vetor
      troca(&dados[min], &dados[i]);
   }
}

// Algoritmo de particao merge
void merge(Tdado V[], Tnum low, Tnum mid, Tnum high) {
	Tnum n1 = mid - low + 1; 
	Tnum n2 = high - mid;          
	Tdado left[n1 + 1], right[n2 + 1];
	Tnum i = 0, j = 0;
	
	for (Tnum i = 0; i < n1; i++) {
		left[i] = V[low + i];
   }
	for (Tnum j = 0; j < n2; j++) {
		right[j] = V[mid + 1 + j];
	}
	left[n1].key = SHRT_MAX;
	right[n2].key = SHRT_MAX;
	for (Tnum k = low; k <= high; k++) {
		if (left[i].key <= right[j].key) {
			V[k] = left[i++];
      } else {
			V[k] = right[j++];
		}
   }
}

// algoritmo de ordencão mergesort
void mergeSort(Tdado V[], Tnum low, Tnum high) {
	if (low < high) {
		Tnum mid = (low + high) / 2;
		mergeSort(V, low, mid);
		mergeSort(V, mid + 1, high);
		merge(V, low, mid, high);
	}
}

// algoritmo de partição quickSort
int partition(Tdado V[], Tnum low, Tnum high)
{
   Tdado pivot = V[low];
   Tnum i = low - 1, j = high + 1;
  
   while (true){
      do {
         i++;
		} while (V[i].key < pivot.key);
      do {
         j--;
      } while (V[j].key > pivot.key);
      if (i >= j) {
         return j;
      }
		troca(&V[i], &V[j]);
   }
}

// algoritmo de ordenação quickSort
void quickSort(Tdado V[], Tnum low, Tnum high) {
   if (low < high) {
      int pi = partition(V, low, high);  
      quickSort(V, low, pi);
      quickSort(V, pi + 1, high);
   }
}

// Função busca sequencial
Tnum seqSearch(Tnum elem, Tdado dados[], Tnum n) {
	Tnum i;
   for (i = 0; (i < n) && (dados[i].key != elem); i++);
	if (i == n) { // não achou
		return -1;
   } else {
		return i;
   }
}

int binSearch(Tdado elem, Tdado dados[], Tnum n) {
   Tnum lo = 0;
   Tnum hi  = n - 1;
   Tnum i = 0;
   while (lo <= hi) {
      i = (lo + hi) / 2;
      if (dados[i] == elem) {
         return i; // Achou
      }
      if (elem < dados[i]) {
         hi  = i - 1; // Pesquisa na metade esquerda
      } else {
         lo = i +1; // Pesquisa na metade direita
      }
   }
   return -1;
}


int main() {
   const short MAX = 12;
	Tdado V[SHRT_MAX];
	Tnum n, k, p; // quantidade de números a serem gerados e indice
	clock_t tempo;
	
	scanf("%hd", &n);
	srand(time(NULL));	// inicializa o gerador de números aleatórios
	
	for (int i = 0; i < n; i++) {
		V[i].key = rand() % MAX + 1;
		V[i].seq = i + 1;
	}
	escreve(V, n);
	tempo = clock();
	
	// descomente abaixo o algoritmo que deseja testar
	bubbleSort(V, n);
	// shakerSort(V, n);
	// insertionSort(V, n);
	// selectionSort(V, n);
	// mergeSort(V, 0, n - 1);
	// quickSort(V, 0, n - 1);
	
	tempo = clock() - tempo;
	printf("\n");
	printf("\n");
	escreve(V, n);
	printf("Tempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);
	k = rand() % MAX + 1;
	printf("Procurando por %hd...\n", k);

	// descomente o algoritmo que deseja testar
	// p = seqSearch(k, V, n);
	// p = binSearch(k, V, n);
	
	if (p < 0) {
		printf(" Não encontrado!\n");
   } else {
		printf("%hd encontrado na posição %hd.\n", k, p); 
   }
	return 0;
}
