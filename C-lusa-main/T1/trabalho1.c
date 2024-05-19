#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int R, G, B;
} Pixel;

Pixel **cinza(Pixel **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            int cinza = (matriz[i][j].R + matriz[i][j].G + matriz[i][j].B) / 3;

            matriz[i][j].R = cinza;
            matriz[i][j].G = cinza;
            matriz[i][j].B = cinza;
        }
    }

    return matriz;
}

Pixel **negativa(Pixel **matrizN, int linhas, int colunas)
{

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizN[i][j].R = 255 - matrizN[i][j].R;
            matrizN[i][j].G = 255 - matrizN[i][j].G;
            matrizN[i][j].B = 255 - matrizN[i][j].B;
        }
    }
    return matrizN;
}

Pixel **aumentaBrilho(Pixel **matrizA, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizA[i][j].R = matrizA[i][j].R + matrizA[i][j].R / 2;
            matrizA[i][j].G = matrizA[i][j].G + matrizA[i][j].G / 2;
            matrizA[i][j].B = matrizA[i][j].B + matrizA[i][j].B / 2;
        }
    }
    return matrizA;
}

Pixel **diminuiBrilho(Pixel **matrizD, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizD[i][j].R = matrizD[i][j].R / 2;
            matrizD[i][j].G = matrizD[i][j].G / 2;
            matrizD[i][j].B = matrizD[i][j].B / 2;
        }
    }
    return matrizD;
}

Pixel **girar(Pixel **matriz, int linhas, int colunas)
{
    // Allocate memory for the new matrix
    Pixel **matrizNova = (Pixel **)malloc(colunas * sizeof(Pixel *));
    for (int i = 0; i < colunas; i++)
    {
        matrizNova[i] = (Pixel *)malloc(linhas * sizeof(Pixel));
    }

    // Transpose the matrix
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizNova[j][i] = matriz[i][j];
        }
    }

    // Reverse each row
    // Reverse each column
    for (int j = 0; j < colunas; j++)
    {
        for (int i = 0; i < linhas / 2; i++)
        {
            Pixel temp = matrizNova[i][j];
            matrizNova[i][j] = matrizNova[linhas - i - 1][j];
            matrizNova[linhas - i - 1][j] = temp;
        }
    }

    return matrizNova;
}

Pixel **envelhecer(Pixel **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j].R -= 20;
            matriz[i][j].G -= 20;
            matriz[i][j].B -= 20;
        }
    }
    return matriz;
}

int main()
{
    FILE *fp;
    int c;
    char extensaoIMG[3];
    int i, j, linhas, colunas, valor, r, g, b;
    int escolha = -1;
    char img[100];

    printf("---- BEM VINDO -----");
    printf("Por favor digite o nome da imagem: ");
    scanf("%s", img);

    fp = fopen(img, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", img);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%s", extensaoIMG);          // lê o tipo de imagem P3
    fscanf(fp, "%d %d", &colunas, &linhas); // lê o tamanho da matriz
    fscanf(fp, "%d", &valor);               // lê o valor máximo.

    Pixel **matriz = (Pixel **)malloc(linhas * sizeof(Pixel *));

    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            matriz[i][j].R = r;
            matriz[i][j].G = g;
            matriz[i][j].B = b;
        }
    }

    fclose(fp);

    printf("Escolha o que deseja fazer com a imagem"
           "[1] - Tons de Cinza\n"
           "[2] - Negativa\n"
           "[3] - Aumentar o brilho\n"
           "[4] - Diminuir o brilho\n"
           "[5] - Girar 90 graus\n"
           "[6] - Envelhecer\n"
           "[0] - Sair");
    scanf("%d", &escolha);

    // Definição da matrizNova
    Pixel **matrizNova = (Pixel **)malloc(linhas * sizeof(Pixel *));

    for (int i = 0; i < linhas; i++)
    {
        matrizNova[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    // Remove the loop that reads pixel values into matrizNova
    // since you've already read them into matriz.

    switch (escolha)
    {
    case 1:
        // Caso 1: Torna a imagem cinza
        matrizNova = cinza(matriz, linhas, colunas);
        break;

    case 2:
        // Caso 2: Torna a imagem negativa
        matrizNova = negativa(matriz, linhas, colunas);
        break;

    case 3:
        // Caso 3: Aumenta a imagem cinzenta
        matrizNova = aumentaBrilho(matriz, linhas, colunas);
        break;

    case 4:
        // Caso 4: Diminui a imagem cinzenta
        matrizNova = diminuiBrilho(matriz, linhas, colunas);
        break;

    case 5:
        // Caso 5: Gira a imagem colorida em 90 graus
        matrizNova = girar(matriz, linhas, colunas);
        break;

    case 6:
        // Caso 6: Envelhece a imagem
        matrizNova = envelhecer(matriz, linhas, colunas);
        break;

    default:
        // se nao seguir nenhum dos casos acima, aparece uma mensagem dizendo erro.
        printf("Erro!");
        break;
    }

    // Abertura do arquivo para escrita
    FILE *fp_novo = fopen("ImgNova.ppm", "w");
    if (fp_novo == NULL)
    {
        fprintf(stderr, "Erro! Nao foi possivel criar a imagem ImgNova.pmp\n");
        exit(EXIT_FAILURE);
    }

    // Gravação dos valores dos pixels RGB
    fprintf(fp_novo, "P3\n%d %d\n255\n", colunas, linhas);
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fprintf(fp_novo, "%d\n%d\n%d\n", matrizNova[i][j].R, matrizNova[i][j].G, matrizNova[i][j].B);
        }
    }

    // Fechamento do arquivo
    fclose(fp_novo);
}
