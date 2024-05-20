#include <stdio.h>
#include <stdlib.h>

// Struct para o pixel
typedef struct {
    int R, G, B;
} Pixel;

Pixel **cinza(Pixel **matriz, int linhas, int colunas) {
    Pixel **novaMatriz = (Pixel **)malloc(linhas * sizeof(Pixel *));
    for (int i = 0; i < linhas; i++) {
        novaMatriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int cinza = (matriz[i][j].R + matriz[i][j].G + matriz[i][j].B) / 3;
            novaMatriz[i][j].R = cinza;
            novaMatriz[i][j].G = cinza;
            novaMatriz[i][j].B = cinza;
        }
    }

    return novaMatriz;
}

Pixel **negativa(Pixel **matriz, int linhas, int colunas) {
    Pixel **novaMatriz = cinza(matriz, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j].R = 255 - novaMatriz[i][j].R;
            novaMatriz[i][j].G = 255 - novaMatriz[i][j].G;
            novaMatriz[i][j].B = 255 - novaMatriz[i][j].B;
        }
    }
    return novaMatriz;
}

Pixel **aumentaBrilho(Pixel **matriz, int linhas, int colunas) {
    Pixel **novaMatriz = cinza(matriz, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j].R = matriz[i][j].R + matriz[i][j].R / 2;
            novaMatriz[i][j].G = matriz[i][j].G + matriz[i][j].G / 2;
            novaMatriz[i][j].B = matriz[i][j].B + matriz[i][j].B / 2;
        }
    }
    return novaMatriz;
}

Pixel **diminuiBrilho(Pixel **matriz, int linhas, int colunas) {
    Pixel **novaMatriz = cinza(matriz, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j].R = matriz[i][j].R / 2;
            novaMatriz[i][j].G = matriz[i][j].G / 2;
            novaMatriz[i][j].B = matriz[i][j].B / 2;
        }
    }
    return novaMatriz;
}

Pixel **girar(Pixel **matriz, int linhas, int colunas) {
    Pixel **matrizGirada = (Pixel **)malloc(colunas * sizeof(Pixel *));
    for (int i = 0; i < colunas; i++) {
        matrizGirada[i] = (Pixel *)malloc(linhas * sizeof(Pixel));
    }

    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas; i++) {
            matrizGirada[j][i] = matriz[linhas - i - 1][j];
        }
    }

    return matrizGirada;
}

Pixel **envelhecer(Pixel **matriz, int linhas, int colunas) {
    Pixel **novaMatriz = (Pixel **)malloc(linhas * sizeof(Pixel *));
    for (int i = 0; i < linhas; i++) {
        novaMatriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j].R = matriz[i][j].R - 20;
            novaMatriz[i][j].G = matriz[i][j].G - 20;
            novaMatriz[i][j].B = matriz[i][j].B - 20;
        }
    }
    return novaMatriz;
}


// Função para tornar as letras em negrito
void bold(int status) {
    static const char *seq[] = {"\x1b[0m", "\x1b[1m"};
    printf("%s", seq[!!status]);
}

// Função que printa mensagem na tela dizendo que foi possível realizar a operação
void mensagem() {
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "           Operação realizada         \n"
           "              com sucesso!            \n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "  Para ver o resultado, abra o arquivo\n");
    bold(1); printf(" ImgNova.ppm "); bold(0); printf("no Gimp.    \n"
                                                     "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

#include <stdio.h>
#include <stdlib.h>

// Declaração das funções de processamento
Pixel **cinza(Pixel **matriz, int linhas, int colunas);
Pixel **negativa(Pixel **matriz, int linhas, int colunas);
Pixel **aumentaBrilho(Pixel **matriz, int linhas, int colunas);
Pixel **diminuiBrilho(Pixel **matriz, int linhas, int colunas);
Pixel **girar(Pixel **matriz, int linhas, int colunas);
Pixel **envelhecer(Pixel **matriz, int linhas, int colunas);



int main() {
    FILE *fp;
    char extensaoIMG[3];
    int linhas, colunas, valor, r, g, b;
    int escolha = -1;
    char img[100];

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "   Bem-vindo ao Mexendo em Imagens    \n"
           "           Programda criado por:      \n"
           "     Luísa Scolari e Marcela Zarichta \n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Por favor digite o nome da imagem:\n ");
    scanf("%s", img);

    fp = fopen(img, "r");
    if (fp == NULL) {
        fprintf(stderr, "\033[1;31mErro: arquivo %s não encontrado\033[0m\n", img);
        return 1;
    }

    fscanf(fp, "%s", extensaoIMG);          // lê o tipo de imagem P3
    fscanf(fp, "%d %d", &colunas, &linhas); // lê o tamanho da matriz
    fscanf(fp, "%d", &valor);               // lê o valor máximo.

    // alocando espaço na memória para a matriz
    Pixel **matriz = (Pixel **)malloc(linhas * sizeof(Pixel *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            matriz[i][j].R = r;
            matriz[i][j].G = g;
            matriz[i][j].B = b;
        }
    }

    fclose(fp);

    while (escolha != 0) {
        printf(""
               "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
               "       Escolha o que deseja fazer     \n"
               "             com a imagem:            \n"
               "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
               "  [1] - Tons de Cinza                 \n"
               "  [2] - Negativa                      \n"
               "  [3] - Aumentar o brilho             \n"
               "  [4] - Diminuir o brilho             \n"
               "  [5] - Girar 90 graus                \n"
               "  [6] - Envelhecer                    \n"
               "  [0] - Sair                          \n"
               "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        scanf("%d", &escolha);

        Pixel **matrizNova = NULL;

        switch (escolha) {
            case 1:
                matrizNova = cinza(matriz, linhas, colunas);
                mensagem();
                break;



            case 2:
                matrizNova = negativa(matriz, linhas, colunas);
                mensagem();
                break;

            case 3:
                matrizNova = aumentaBrilho(matriz, linhas, colunas);
                mensagem();
                break;

            case 4:
                matrizNova = diminuiBrilho(matriz, linhas, colunas);
                mensagem();
                break;

            case 5:
                matrizNova = girar(matriz, linhas, colunas);
                // Trocar linhas e colunas após girar
                int temp = linhas;
                linhas = colunas;
                colunas = temp;
                mensagem();
                break;

            case 6:
                matrizNova = envelhecer(matriz, linhas, colunas);
                mensagem();
                break;

            case 0:
                break;
            default:
                fprintf(stderr, "\033[1;31mErro: opção inválida!\033[0m\n");
                break;
        }

        if (matrizNova != NULL) {
            FILE *fp_novo = fopen("ImgNova.ppm", "w");
            if (fp_novo == NULL) {
                fprintf(stderr, "\033[1;31mErro! Nao foi possivel criar a imagem ImgNova.pmp\033[0m\n");
                return 1;
            }

            fprintf(fp_novo, "P3\n%d %d\n255\n", colunas, linhas); // Ajuste para colunas e linhas
            for (int i = 0; i < linhas; i++) {
                for (int j = 0; j < colunas; j++) {
                    fprintf(fp_novo, "%d %d %d\n", matrizNova[i][j].R, matrizNova[i][j].G, matrizNova[i][j].B);
                }
            }

            fclose(fp_novo);

            // Liberar matrizNova
            for (int i = 0; i < linhas; i++) {
                free(matrizNova[i]);
            }
            free(matrizNova);
        }
    

    // Liberar matriz original
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    printf(""
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "                   FIM                \n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    return 0;
}
}
