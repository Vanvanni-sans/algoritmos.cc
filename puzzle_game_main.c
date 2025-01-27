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
