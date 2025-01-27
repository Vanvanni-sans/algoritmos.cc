
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
