// ordena.c
// Implementa algoritmos de ordenação

# include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef enum {false, true} bool;
typedef long Tdado;
typedef long Tnum;

void troca(Tdado *x, Tdado *y) {
	Tdado aux = *x;
	*x = *y;
	*y = aux;
}

void escreve(Tdado V[], Tnum n) {
	printf("[");
	for (Tnum i = 0; i < n; i++) {
		printf("%ld", V[i]);
		if (i < n - 1) {
			printf(", ");
      }
	}
	printf("]\n");
}

void bubbleSort(Tdado dados[], Tnum  n) {
  	for (int i = 0; i < n - 1; i++) {
  		for(int j = n - 1; j > i; j--) {
			if (dados[j] < dados[j - 1]) {
				troca(&dados[j], &dados[j - 1]);
         }
      }
   }
} 

void shakerSort(Tdado dados[], Tnum n) {
	bool trocou;
	do {
		trocou = false;
		for (Tnum i = (n - 1); i > 0; i--) {
			if(dados[i - 1] > dados[i]) {
				troca(&dados[i - 1], &dados[i]);
            trocou = true;
         }
		}
		for (Tnum i = 1; i < n; i++) {
			if (dados[i - 1] > dados[i]) {
            troca(&dados[i - 1], &dados[i]);
         	trocou = true;
         }
      }
   } while (trocou); 
}

void insertionSort(Tdado dados[], Tnum n) {
   for (Tnum i = 1; i < n; i++) {
		Tdado aux = dados[i];
		Tnum j = 0;
      for (j = i; (j > 0) && (aux < dados[j-1]); j--) {
         dados[j] = dados[j - 1];
      }
      dados[j] = aux;
   }
}

void selectionSort(Tdado dados[], Tnum n) {
	for (Tnum i = 0; i < (n - 1); i++) {
   	// encontra o menor elemento
		Tnum min = i;
		for (Tnum j = i + 1; j < n; j ++) {
			if (dados[j] < dados[min]) {
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
	left[n1] = LONG_MAX;
	right[n2] = LONG_MAX;
	
	for (Tnum k = low; k <= high; k++) {
		if (left[i] <= right[j]) {
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

//================================================

int partition(Tnum V[], Tnum low, Tnum high) {
   Tnum pivot = V[low];
   Tnum i = low - 1, j = high + 1;
  
   while (true) {
      do {
         i++;
		} while (V[i] < pivot);
        
      do {
         j--;
      } while (V[j] > pivot);

      if (i >= j) {
         return j;
      }
		troca(&V[i], &V[j]);
   }
}

void quickSort(Tnum V[], Tnum low, Tnum high) {
   if (low < high) {
      int pi = partition(V, low, high);  
      quickSort(V, low, pi);
      quickSort(V, pi + 1, high);
   }
}

//================================================

Tnum seqSearch(Tdado elem, Tdado dados[], Tnum n) {
	Tdado i;
   for (i = 0; (i < n) && (dados[i] != elem); i++);
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
   const short MAX = 200;
	Tdado V[20000];
	Tnum n, k, p; // quantidade de números a serem gerados e indice
	clock_t tempo;
	
	scanf("%ld", &n);
		
	srand(time(NULL));	// inicializa o gerador de números aleatórios
	
	printf("Vetor 1: ");
	for (int i = 0; i < n; i++) {
		V[i] = rand() % MAX + 1;
   }
	escreve(V, n);
	
	printf("Vetor 2: ");
	for (int i = 0; i < n; i++) {
		V[i] = rand() % MAX + 1;
   }
	escreve(V, n);
	tempo = clock();
	
	// descomente abaixo o algoritmo que deseja testar
	 bubbleSort(V, n);
	// shakerSort(V, n);
	// insertionSort(V, n);
	// selectionSort(V, n);
	// mergeSort(V, 0, n - 1);
	 //quickSort(V, 0, n - 1);
	
	tempo = clock() - tempo;
	printf("\n");
	printf("\n");
	escreve(V, n);
	printf("Tempo gasto = %f segundos\n", ((float)tempo) / CLOCKS_PER_SEC);
	k = rand() % MAX + 1;
	printf("Procurando por %ld...\n", k);

	// descomente o algoritmo de busca que deseja utilizar
	 p = seqSearch(k, V, n);
   	// p = binSearch(k, V, n);

	if (p < 0)
		printf(" Não encontrado!\n");
	else
		printf("%ld encontrado na posição %ld.\n", k, p); 
		
	return 0;
}
