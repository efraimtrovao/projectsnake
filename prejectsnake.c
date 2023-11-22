#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

#define COR_COBRA 2   
#define COR_COMIDA 4  

int G[26][76], X[1771], Y[1771], l = 5, s = 0, x, y, f = 0, d = 1;
int recorde = 0;

void imprimir() {
    int i, j;
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
            if ((i == 1 || i == 25) && (j < 35 || j > 39))
                printf("|");
            else if ((j == 1 || j == 75) && (i < 10 || i > 14))
                printf("-");
            else if (G[i][j] == 1)
                printf("\033[1;%dm*\033[0m", COR_COBRA); 
            else if (G[i][j] == 2)
                printf("\033[1;%dm*\033[0m", COR_COMIDA); 
            else if (G[i][j] == 3)
                printf(">");
            else if (G[i][j] == 4)
                printf("^");
            else if (G[i][j] == 5)
                printf("<");
            else if (G[i][j] == 6)
                printf("v");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\nPontuação: %d", s);
}

void configurar() {
    int i, j;
    for (i = 1; i <= 25; i++) {
        for (j = 1; j <= 75; j++) {
            if (i == 1 || i == 25 || j == 1 || j == 75)
                G[i][j] = 1;
            else
                G[i][j] = 0;
        }
    }

    for (i = 10; i <= 14; i++) {
        G[i][1] = 0;
        G[i][75] = 0;
    }

    for (i = 35; i <= 39; i++) {
        G[1][i] = 0;
        G[25][i] = 0;
    }

    G[X[0]][Y[0]] = 1;
    if (d == 1)
        G[X[1]][Y[1]] = 3;
    else if (d == 2)
        G[X[1]][Y[1]] = 4;
    else if (d == 3)
        G[X[1]][Y[1]] = 5;
    else if (d == 4)
        G[X[1]][Y[1]] = 6;

    for (i = 2; i <= l; i++) {
        G[X[i]][Y[i]] = 1;
    }

    if (f > 0) {
        G[x][y] = 2;
        f = f - 1;
    }
}

void imprimirMenu() {
    system("CLS");
    printf("=== Jogo da Cobra ===\n");
    printf("      Bem vindo!\n\n");

    printf("1. Iniciar Jogo\n");
    printf("2. Sair\n\n");
}

int obterEscolhaMenu() {
    int escolha;
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

void mostrarInstrucoes() {
    system("CLS");
    printf("=== Instruções ===\n\n");
    printf("Use as setas para controlar a cobra.\n");
    printf("Coma a comida (*) para crescer a cobra e ganhar pontos.\n");
    printf("Evite colisões com as paredes e o corpo da cobra.\n\n");
    printf("Pressione qualquer tecla para continuar...\n\n");
    getch();
}

void menuGameOver() {
    system("CLS");
    printf("=== Fim de Jogo ===\n\n");
    printf("Pontuação: %d\n", s);
    printf("Recorde: %d\n\n", recorde);
    printf("1. Jogar Novamente\n");
    printf("2. Sair do Jogo\n\n");
}

int obterEscolhaMenuGameOver() {
    int escolha;
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);
    return escolha;
}

void fimDeJogo() {
    if (s > recorde) {
        recorde = s;
    }

    menuGameOver();
    int escolha = obterEscolhaMenuGameOver();

    switch (escolha) {
        case 1:
            l = 5;
            s = 0;
            x = 0;
            y = 0;
            f = 0;
            d = 1;

            X[1] = 12;
            Y[1] = 12;
            X[2] = 12;
            Y[2] = 11;
            X[3] = 12;
            Y[3] = 10;
            X[4] = 12;
            Y[4] = 9;
            X[5] = 12;
            Y[5] = 8;

            while (G[X[0]][Y[0]] >= 1) {
                X[0] = rand() % 23 + 2;
                Y[0] = rand() % 73 + 2;
            }
            break;
        case 2:
            exit(0);
        default:
            printf("Escolha inválida. Saindo...\n");
            exit(1);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int escolha;

    imprimirMenu();
    escolha = obterEscolhaMenu();

    switch (escolha) {
        case 1:
            mostrarInstrucoes();
            break;
        case 2:
            return 0;
        default:
            printf("Escolha inválida. Saindo...\n");
            return 1;
    }

    srand(time(NULL));
    X[0] = 0;
    Y[0] = 0;
    X[1] = 12;
    Y[1] = 12;
    X[2] = 12;
    Y[2] = 11;
    X[3] = 12;
    Y[3] = 10;
    X[4] = 12;
    Y[4] = 9;
    X[5] = 12;
    Y[5] = 8;
    int i = 12, j = 12;

    configurar();

    while (G[X[0]][Y[0]] >= 1) {
        X[0] = rand() % 23 + 2;
        Y[0] = rand() % 73 + 2;
    }

    configurar();
    imprimir();
    getch();
    system("CLS");

    while (1) {
        configurar();
        imprimir();

        if (d == 1) {
            if (Y[1] == 75)
                Y[1] = 0;
            if (G[X[1]][Y[1] + 1] == 0) {
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] == X[0]) && (Y[1] + 1 == Y[0])) {
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] + 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();
        } else if (d == 2) {
            if (X[1] == 1)
                X[1] = 26;
            if (G[X[1] - 1][Y[1]] == 0) {
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] - 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] - 1 == X[0]) && (Y[1] == Y[0])) {
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] - 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();
        } else if (d == 3) {
            if (Y[1] == 1)
                Y[1] = 76;
            if (G[X[1]][Y[1] - 1] == 0) {
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] - 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] == X[0]) && (Y[1] - 1 == Y[0])) {
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                Y[1] = Y[1] - 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();
        } else if (d == 4) {
            if (X[1] == 25)
                X[1] = 0;
            if (G[X[1] + 1][Y[1]] == 0) {
                for (int k = l; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] + 1;
                i = X[1];
                j = Y[1];
            } else if ((X[1] + 1 == X[0]) && (Y[1] == Y[0])) {
                for (int k = l + 1; k > 1; k--) {
                    X[k] = X[k - 1];
                    Y[k] = Y[k - 1];
                }
                X[1] = X[1] + 1;
                i = X[1];
                j = Y[1];
                x = X[0];
                y = Y[0];
                f = l;
                while (G[X[0]][Y[0]] >= 1) {
                    X[0] = rand() % 23 + 2;
                    Y[0] = rand() % 73 + 2;
                }
                l = l + 1;
                s = s + 1;
            } else
                fimDeJogo();
        }

        if ((GetAsyncKeyState(VK_RIGHT)) && (d != 3))
            d = 1;
        else if ((GetAsyncKeyState(VK_UP)) && (d != 4))
            d = 2;
        else if ((GetAsyncKeyState(VK_LEFT)) && (d != 1))
            d = 3;
        else if ((GetAsyncKeyState(VK_DOWN)) && (d != 2))
            d = 4;

        Sleep(18);
        system("CLS");
    }

    return 0;
}

