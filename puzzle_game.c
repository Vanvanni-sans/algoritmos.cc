//main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#define FG_RED "\033[91m"
#define FG_BRIGHT_GREEN  "\033[92m"
#define RESET "\033[0m"
#define KEY_ENTER 10

int main() {
    /////////////////////////////////////////////////////////////// Configuração do menu
    const char *titulo = "    Puzzle Game    ";
    const char *opcoes[] = {
        " começar",
        "    sair"
    };
    int n = sizeof(opcoes) / sizeof(opcoes[0]);

    // Mostra o menu e obtém a escolha
    int escolha = mostrar_menu_interativo(opcoes, n, titulo);
    printf("\033[H\033[J");  // Limpa a tela

    if (escolha == 1) {/////////////////////////////////////////////sair
        return 0;
    }

    if (escolha == 0) {////////////////////////////////////////////começar
        int largura, altura, distlado, distcima;
        printf(FG_BRIGHT_GREEN);
        printf("(usar cmd na lateral de preferencia, alguns podem bugar se não completamente abertos ou nem abrir como o replit)\n");
        printf(RESET);
        printf("\033[43;30;1m");
        printf("Insira a largura da janela! (máximo 20, minimo 3):\n");
        printf("\033[m");
        scanf("%d", &largura);
        printf("\033[43;30;1m");
        printf("Insira a altura da janela! (máximo 20, minimo 3):\n");
        printf("\033[m");
        scanf("%d", &altura);
        printf("\033[43;30;1m");
        printf("Insira a distancia do tabuleiro da borda lateral! (distancai>0):\n");
        printf("\033[m");
        scanf("%d", &distlado);
        printf("\033[43;30;1m");
        printf("Insira a distancia do tabuleiro da borda superior! (distancai>0):\n");
        printf("\033[m");
        scanf("%d", &distcima);
        printf("\033[;32;1m");
        clrscr();
        //algumas alterações feitas nas funções por praticidade e recursividade dos codigos
        //largura = x2, altura = y2, distlado=x1, distcima=y1(esse padrão se repete nas funções que alterei)
        //((y2 * 2) + y1) essa é a formula para descobrir a linha de baixo
        ////((x2 * 4) + x1) essa é a formula para descobrir a coluna da direita
        // Restringe a largura e altura a no máximo 20
        if (largura > 20) largura = 20;
        if (altura > 20) altura = 20;
        if (altura < 3) altura = 3;
        if (largura < 3) largura = 3;


        //cria a matriz de forma dinamica com o tipo joguinhgo definido na biblioteca
        joguinho** num = malloc(altura * sizeof(joguinho*));
        for (int i = 0; i < altura; i++) {
            num[i] = malloc(largura * sizeof(joguinho));
        }

        // Cria a janela com as dimensões fornecidas
        printf(FG_BRIGHT_GREEN);

        montar_grade( distlado, distcima, largura, altura);

        preencherMatriz(num, altura, largura, distcima, distlado);

        imprimirMatriz(num, altura, largura);

    aux vazio; // Variável para armazenar a posição do vazio
    vazio.i = altura - 1;
    vazio.j = largura - 1;
    sleep(3);
    //randomiza a matriz
    int aaa, vezes=altura*largura*50;
         srand(time(NULL)); //inicializa a semente aleatoria
    for(int i=0;i<vezes; i++){
          int r = rand()%4;
        switch(r){ 
            case 0:
            aaa = 'w';
            break;
            case 1:
            aaa = 'a';
            break;
            case 2:
            aaa = 's';
            break;
            case 3:
            aaa = 'd';
            break;
        }
        executar_jogo(num, altura, largura, distlado, distcima, aaa, &vazio);
        }

        //loop de execuçao do jogo
    int continuidade = 1; // Variável para controle do loop do jogo

    while (continuidade) {
    aaa = getch(); // Lê o input do usuário
    executar_jogo(num, altura, largura, distlado, distcima, aaa, &vazio);
        clrscr();
        printf(FG_BRIGHT_GREEN);
        montar_grade(distlado, distcima, largura, altura);
        imprimirMatriz(num, altura, largura);
        gotoxy(0, (distcima + (altura*2) + 1)); // Move o cursor para fora da janela
        printf("\n");
        printf(FG_BRIGHT_GREEN);
        printf("Use para mover:  W   \n");
        printf("               A S D\n");
        printf("\n");
        printf(RESET);
        printf(FG_RED);
        printf("Aperte 'Q' para sair do jogo\n");
        printf(RESET);
        printf("\n");
        printf(FG_BRIGHT_GREEN);
        printf("Decorado em tema natalino, feliz natal!\n");
    if (aaa == 'q') { // Sair do jogo
        continuidade = 0;
    }
    int ta_resolvido = verificar_resolucao(num, largura, altura);
        if(ta_resolvido == 1){
        clrscr();
        printf("VOCÊ RESOLVEU");
        continuidade++;
        break;
    }}

        gotoxy(0, (distcima + (altura*2) + 1)); // Move o cursor para fora da janela

        // Liberando a memória alocada
        for (int i = 0; i < altura; i++) {
            free(num[i]);
        }
        free(num);

    }


    return 0;
}


//utils.h**********************************************************************

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

// utils.c******************************************************************************************************

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define FG_BRIGHT_GREEN  "\033[92m"
#define BG_BLACK "\033[40m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define FG_WHITE "\033[37m"
#define BG_BLUE "\033[44m"
#define BG_YELLOW "\033[43m"
#define FG_BLACK "\033[90m"
#define FG_RED "\033[91m"

// Configuração para teclas
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_ENTER 10
#define KEY_ESC 27
#define KEY_RIGHT 67
#define KEY_LEFT 68

// Comprimento máximo de uma linha do menu
#define MENU_WIDTH 10


// limpa a tela
void clrscr() { printf(CLEAR); }

// posiciona o cursor na coluna x linha y
void gotoxy(int x, int y) {
  printf("\e[%d;%df", y, x);
  fflush(stdout);
}

// Quinas da janela
void montar_grade(int x1, int y1, int x2, int y2) {
  // o que era x2 virou ((x2*4)+x1) e o que era y2 virou (y1+(y2*2))

  gotoxy(x1, y1);
  printf("+");
  for (int i = x1 + 1; i < ((x2 * 4) + x1); i++) {
    gotoxy(i, y1);
    printf("-");
  }

  gotoxy(x1, (y1 + (y2 * 2))); // y2
  printf("+");                 // alterado, canto inferior esquerdo y2
  for (int j = y1 + 1; j < (y1 + (y2 * 2)); j++) {
    gotoxy(x1, j);
    printf("|"); // alterar, lateral
                 // esquerda//////////////////////////////////////////
  }

  gotoxy(((x2 * 4) + x1), y1); // x2
  printf("+");                 // alterado, canto superior direito
  for (int j = y1 + 1; j < (y1 + (y2 * 2)); j++) {
    gotoxy(((x2 * 4) + x1), j);
    printf("|"); // alterar, lateral
                 // direita/////////////////////////////////////////////
  }

  gotoxy(((x2 * 4) + x1), (y1 + (y2 * 2))); // x2/y2
  printf("+");                              // alterado, canto inferior direito
  for (int i = x1 + 1; i < ((x2 * 4) + x1); i++) {
    gotoxy(i, (y1 + (y2 * 2)));
    printf("-");
  }

  // cria parte interna da grade
  for (int i = y1 + 1; i < (y1 + (y2 * 2)); i += 2) {
    for (int j = x1 + 4; j < ((x2 * 4) + x1); j += 4) {
      gotoxy(j, i);
      printf("|");
    }
  }
  for (int i = y1 + 2; i < (y1 + (y2 * 2)); i += 2) {
    for (int j = x1 + 1; j < ((x2 * 4) + x1); j += 4) {
      gotoxy(j, i);
      if (j ==
          ((x2 * 4) + x1) - 3) { // testa se o print não sobrepõe barra direita
        printf("---");
      } else
        printf("---+");
    }
  }
}

char getch() {
  // le caracter de entrada padrao sem o bloqueio de entrada
  // nao precisa apertar enter

  int ch;
  struct termios oldt;
  struct termios newt;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

int keypress(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}
// menu///////////////////////////////////////////////
void configurar_terminal(struct termios *old) {
  struct termios new;
  tcgetattr(STDIN_FILENO, old);
  new = *old;
  new.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void restaurar_terminal(struct termios *old) {
  tcsetattr(STDIN_FILENO, TCSANOW, old);
}

// Função para exibir o cabeçalho
void exibir_cabecalho(const char *titulo) {
  printf("\033[H\033[J");          // Limpa a tela
  printf(BG_YELLOW FG_BLACK BOLD); // Estilo do cabeçalho
  printf(" %s ", titulo);
  printf(RESET "\n\n"); // Reseta estilos após o cabeçalho
}

// Função para formatar uma string com tamanho fixo
void formatar_opcao(const char *opcao, char *saida, int largura) {
  int len = strlen(opcao);
  int padding = largura - len; // Espaços para completar
  if (padding < 0)
    padding = 0; // Evita valores negativos
  snprintf(saida, largura + 1, "%s%*s", opcao, padding,
           ""); // Adiciona espaços ao final
}

// Função para exibir o menu interativo
int mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo) {
  int selecionado = 0;
  struct termios terminal_original;

  configurar_terminal(&terminal_original);

  while (1) {
    exibir_cabecalho(titulo); // Mostra o cabeçalho

    // Exibe as opções do menu
    for (int i = 0; i < n; i++) {
      char opcao_formatada[MENU_WIDTH + 1];
      formatar_opcao(opcoes[i], opcao_formatada, MENU_WIDTH);

      if (i == selecionado) {
        printf(BG_YELLOW FG_BLACK);
        printf(REVERSE " %s " RESET "\n",
               opcao_formatada); // Destaca a opção com vídeo reverso
      } else {
        printf(" %s\n", opcao_formatada);
      }
    }

    // Lê a tecla pressionada
    int ch = getchar();
    if (ch == '\033') { // Tecla especial (setas)
      getchar();        // Ignora '['
      switch (getchar()) {
      case KEY_UP:
        if (selecionado > 0)
          selecionado--;
        break;
      case KEY_DOWN:
        if (selecionado < n - 1)
          selecionado++;
        break;
      }
    } else if (ch == KEY_ENTER) {
      break; // Sai do loop ao pressionar Enter
    }
  }
  restaurar_terminal(&terminal_original);
  return selecionado;
}


void preencherMatriz(joguinho** matriz, int altura, int largura, int distcima, int distlado) {
int numtot = 1; // Contador de números

    // Pré-calcular limites
    int limite_altura = (altura * 2) + distcima;
    int limite_largura = (largura * 4) + distlado;
    for (int i = distcima + 1, i2 = 0; i < limite_altura; i += 2, i2++) {
        for (int j = distlado + 1, j2 = 0; j < limite_largura; j += 4, j2++) {
            if (i2 < altura && j2 < largura) {
                matriz[i2][j2].posx = j;
                matriz[i2][j2].posy = i;
                matriz[i2][j2].num = numtot++;
            } else {
                break;
            }
        }
    }
}

void imprimirMatriz(joguinho** num, int altura, int largura) {
    // Percorrer a matriz e imprimir os números nas posições especificadas
    printf(FG_RED);
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            gotoxy(num[i][j].posx, num[i][j].posy);
            if (num[i][j].num == altura * largura) {
                printf("   ");
            } else {
                printf("%d", num[i][j].num);
            }
        }
    }
            printf("\033[m");

}

void verificar_pos_borda(int i, int j, int largura, int altura, int distlado, int distcima){
    //i e j são posições atuais 
}



void executar_jogo(joguinho** num, int altura, int largura, int distlado, int distcima, int aaa, aux* vazio) {
        printf(FG_BRIGHT_GREEN);


    if(aaa=='q')return;
        switch (aaa) {
            case 'w': // Mover vazio para baixo
                if (vazio->i == altura - 1) {
                    break;
                }
                num[vazio->i][vazio->j].num = num[vazio->i + 1][vazio->j].num;
                num[vazio->i + 1][vazio->j].num = altura * largura;
                vazio->i += 1;
                break;
            case 's': // Mover vazio para cima
                if (vazio->i == 0) {
                    break;
                }
                num[vazio->i][vazio->j].num = num[vazio->i - 1][vazio->j].num;
                num[vazio->i - 1][vazio->j].num = altura * largura;
                vazio->i -= 1;
                break;
            case 'a': // Mover vazio para a direita
                if (vazio->j == largura - 1) {
                    break;
                }
                num[vazio->i][vazio->j].num = num[vazio->i][vazio->j + 1].num;
                num[vazio->i][vazio->j + 1].num = altura * largura;
                vazio->j += 1;
                break;
            case 'd': // Mover vazio para a esquerda
                if (vazio->j == 0) {
                    break;
                }
                num[vazio->i][vazio->j].num = num[vazio->i][vazio->j - 1].num;
                num[vazio->i][vazio->j - 1].num = altura * largura;
                vazio->j -= 1;
                break;
        }

        // Atualiza a tela


}

int verificar_resolucao(joguinho** num, int largura, int altura){
int num_esperado = 1; // Começamos com o número 1

    // Verifica cada célula da matriz
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (num[i][j].num != num_esperado) {
                // Se o número não for o esperado, o tabuleiro não está resolvido
                if (i == altura - 1 && j == largura - 1) {
                    // A última célula deve ser o número "altura * largura" (vazio)
                    if (num[i][j].num != altura * largura) {
                        return 0; // Tabuleiro não resolvido
                    }
                } else {
                    return 0; 
                }
            }
            num_esperado++; 
        }
    }
    return 1; 
}
