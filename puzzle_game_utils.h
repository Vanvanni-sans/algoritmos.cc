#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <string.h>

#define CLEAR "\033[H\033[2J"

typedef struct{
 int posx;
 int posy;
 int num;
}joguinho;

typedef struct{
    int i;
    int j;
}aux;

//Funções

//limpa a tela
void clrscr();

//posiciona o cursor nas coordenadas x, y
void gotoxy(int x, int y);

//Borda da matriz
void montar_grade(int x1, int y1, int x2, int y2);
//recebe uma tecla sem precisar digitar [enter]
char getch();
//verifica se uma tecla foi precionada
int keypress();
// Configuração de terminal
void configurar_terminal(struct termios *old);

void restaurar_terminal(struct termios *old);
// Função para exibir o cabeçalho
void exibir_cabecalho(const char *titulo);
// Função para formatar uma string com tamanho fixo
void formatar_opcao(const char *opcao, char *saida, int largura);
// Função para exibir o menu interativo
int mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo);
//vetor tipo armazenar posição

void preencherMatriz(joguinho** matriz, int altura, int largura, int distcima, int distlado);

void imprimirMatriz(joguinho** num, int altura, int largura);

void executar_jogo(joguinho** num, int altura, int largura, int distlado, int distcima, int aaa, aux* vazio);

int verificar_resolucao(joguinho** num, int largura, int altura);
