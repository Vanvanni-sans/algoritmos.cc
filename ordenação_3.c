// Ordena3.c
//  Ordenação de estruturas complexas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Declaração do tipo de dado booleano 
typedef enum {false, true} bool;

// Declaração do tipo TNum
typedef short Tnum;

// Tipo de dado a ser ordenado
typedef struct
{
	short key; // chave de ordenação
	short seq; // sequência de aparição 
} Tdado;

// Função de troca
void troca(Tdado *x, Tdado *y)
{
	Tdado aux = *x;
	*x = *y;
	*y = aux;
}

// Função de comparação
int compara2(const void *a, const void *b)
{
	Tdado x = *(Tdado*)a;
	Tdado y = *(Tdado*)b;
	
	if (x.key < y.key) 				// chave principal de a é menor que de b
		return -1;
	else if (x.key > y.key)	// chave principal de a é maior que de b 
		return 1;
	else if (x.seq < y.seq)	// chave secundária de a é menor que de b
		return-1;
	else if (x.seq > y.seq)	// chave secundária de a é maior que de b
		return 1;
	else 																									// são iguais
		return 0;
}

// Função para escrever um vetor
void escreve(Tdado V[], Tnum n)
{
	printf("[");
	for (Tnum i = 0; i < n; i++)
	{
		printf("(%hd, %hd)", V[i].key, V[i].seq);
		if (i < n - 1)
			printf(", ");
	}
	printf("]\n");
}

// Função bubbleSort
void bubbleSort(Tdado dados[], Tnum  n, int compara())
{
  	for (int i = 0; i < n - 1; i++)
  		for(int j = n - 1; j > i; j--)
			if (compara(&dados[j], &dados[j - 1]) < 0)
				troca(&dados[j], &dados[j - 1]);
} 

// Função shakerSort
void shakerSort(Tdado dados[], Tnum n, int compara())
{
	bool trocou;
	do
	{
		trocou = false;
		for (Tnum i = (n - 1); i > 0; i--)
		{
			if(compara(&dados[i - 1], &dados[i]) > 0)
         {
				troca(&dados[i - 1], &dados[i]);
            trocou = true;
         }
		}
		for (Tnum i = 1; i < n; i++)
		{
			if (compara(&dados[i - 1], &dados[i]) > 0)
			{
            troca(&dados[i - 1], &dados[i]);
         	trocou = true;
         }
      }
   } while (trocou); 
}

// Função insertionSort
void insertionSort(Tdado dados[], Tnum n, int compara())
{
   for (Tnum i = 1; i < n; i++)
   {
		Tdado aux = dados[i];
		Tnum j = 0;
      for (j = i; (j > 0) && (compara(&aux, &dados[j-1]) < 0); j--)
         dados[j] = dados[j - 1];
      dados[j] = aux;
   }
}

// Função selectionSort
void selectionSort(Tdado dados[], Tnum n, int compara())
{
	for (Tnum i = 0; i < (n - 1); i++)
	{
   	// encontra o menor elemento
		Tnum min = i;
		for (Tnum j = i + 1; j < n; j ++)
			if (compara(&dados[j], &dados[min]) < 0)
				min = j;
      // Troca a posição atual com o menor elemento do vetor
      troca(&dados[min], &dados[i]);
   }
}

// Algoritmo de particao merge
void merge(Tdado V[], Tnum low, Tnum mid, Tnum high, int compara())
{
	Tnum n1 = mid - low + 1; 
	Tnum n2 = high - mid;          
	Tdado left[n1 + 1], right[n2 + 1];
	Tnum i = 0, j = 0;
	
	for (Tnum i = 0; i < n1; i++)
		left[i] = V[low + i];
		
	for (Tnum j = 0; j < n2; j++)
		right[j] = V[mid + 1 + j];
	
	left[n1].key = SHRT_MAX;
	right[n2].key = SHRT_MAX;
	
	for (Tnum k = low; k <= high; k++)
		if (compara(&left[i], &right[j]) <= 0)
			V[k] = left[i++];
		else
		{
			V[k] = right[j++];
		}
}

// algoritmo de ordencão mergesort
void mergeSort(Tdado V[], Tnum low, Tnum high, int compara())
{
	if (low < high)
	{
		Tnum mid = (low + high) / 2;
		mergeSort(V, low, mid, compara);
		mergeSort(V, mid + 1, high, compara);
		merge(V, low, mid, high, compara);
	}
}

// algoritmo de partição quickSort
int partition(Tdado V[], Tnum low, Tnum high, int compara())
{
   Tdado pivot = V[low];
   Tnum i = low - 1, j = high + 1;
  
   while (true)
   {
      do
		{
         i++;
		} while (compara(&V[i], &pivot) < 0);
  
       do
      {
          j--;
      } while (compara(&V[j], &pivot) > 0);

      if (i >= j)
         return j;
		troca(&V[i], &V[j]);
   }
}

// algoritmo de ordenação quickSort
void quickSort(Tdado V[], Tnum low, Tnum high, int compara())
{
   if (low < high)
   {
      int pi = partition(V, low, high, compara);  
        quickSort(V, low, pi, compara);
        quickSort(V, pi + 1, high, compara);
    }
}

// Principal
int main()
{
    const short MAX = 200;
	Tdado V[SHRT_MAX];
	Tnum n, p; // quantidade de números a serem gerados e indice
	clock_t tempo;
	Tdado k;
	scanf("%hd", &n);
		
	srand(time(NULL));	// inicializa o gerador de números aleatórios
	
	for (int i = 0; i < n; i++)
	{
		V[i].key = rand() % MAX + 1;
		V[i].seq = i + 1;
	}
	escreve(V, n);
	tempo = clock();
	
	// Use aqui os algoritmos de ordenação
	// bubbleSort(V, n, compara2);
	// shakerSort(V, n, compara2);
	// insertionSort(V, n, compara2);
	// selectionSort(V, n, compara2);
  	// mergeSort(V, 0, n - 1, compara2);
	// quickSort(V, 0, n - 1, compara2);
	// qsort(V, n, sizeof(Tdado), compara2); // algoritmo fornecido pela biblioteca do C

	tempo = clock() - tempo;
	printf("\n");
	printf("\n");
	escreve(V, n);
	printf("Tempo gasto = %lf segundos\n", ((double)tempo) / CLOCKS_PER_SEC);
	// k = rand() % MAX + 1;
  	printf("buscando por >> ");
  	scanf("%hd %hd", &k.key, &k.seq);
  
   	// usa a busca binária do C para encontrar o elemento k
  	Tdado *res = bsearch(&k, V, n, sizeof(Tdado), compara2);
  	
	if (res)
    		printf("Encontrado!\n");
  	else
    		printf("Não encontrado!\n");
	return 0;
}
