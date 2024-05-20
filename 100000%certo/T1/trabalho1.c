#include <stdio.h>
#include <stdlib.h>

//Struct para o pixel;
typedef struct
{
    int R, G, B;
} Pixel;

//função que torna uma imagem acinzentada
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

//função que torna uma imagem acinzentada em tons negativos
Pixel **negativa(Pixel **matrizN, int linhas, int colunas)
{
    cinza(matrizN, linhas, colunas);
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

//Função que aumenta o brilho na pporcentagem dada pelo usuario na imagem cinza 
Pixel **aumentaBrilho(Pixel **matrizA, int linhas, int colunas, int percentual)
{
    cinza(matrizA, linhas, colunas);
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizA[i][j].R = matrizA[i][j].R + (matrizA[i][j].R * percentual/100);
            matrizA[i][j].G = matrizA[i][j].G + (matrizA[i][j].G * percentual/100);
            matrizA[i][j].B = matrizA[i][j].B + (matrizA[i][j].B * percentual/100);

            if (matrizA[i][j].R > 255) 
            {
                matrizA[i][j].R = 255;
            }
            if (matrizA[i][j].G > 255)
            {
                matrizA[i][j].G = 255;
            }
            if (matrizA[i][j].B > 255) 
            {
                matrizA[i][j].B = 255;
            }
        }
        
    }
    return matrizA;
}


//Função que diminui o brilho de uma imagem cinza em 100%
Pixel **diminuiBrilho(Pixel **matrizD, int linhas, int colunas, int percentual)
{
    cinza(matrizD, linhas, colunas);
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizD[i][j].R = matrizD[i][j].R - (matrizD[i][j].R * percentual/100);
            matrizD[i][j].G = matrizD[i][j].G - (matrizD[i][j].G * percentual/100);
            matrizD[i][j].B = matrizD[i][j].B - (matrizD[i][j].R * percentual/100);

            if (matrizD[i][j].R < 0) 
            {
                matrizD[i][j].R = 0;
            }
            if (matrizD[i][j].G < 0)
            {
                matrizD[i][j].G = 0;
            }
            if (matrizD[i][j].B < 0) 
            {
                matrizD[i][j].B = 0;
            }
        }
    }
    return matrizD;
}


//Função que gira em 90 graus uma imagem colorida
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

//Função que envelhece uma imagem colorida
Pixel **envelhecer(Pixel **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j].R = matriz[i][j].R - 20;
            matriz[i][j].G = matriz[i][j].G - 20;
            matriz[i][j].B = matriz[i][j].B - 20;
        }
    }
    return matriz;
}

//Função que printa mensagem na tela dizendo que foi possível realizar a operação
void mensagem()
{
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "           Operação realizada         \n"
           "              com sucesso!            \n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "  Para ver o resultado, abra o arquivo\n" 
        "   \033[1;30mImgNova.ppm\033[0m no Gimp.    \n"
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

int main()
{
    FILE *fp;
    char extensaoIMG[3];
    int linhas, colunas, valor, r, g, b, percentual;
    int escolha = -1;
    char img[100];

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
           "   Bem-vindo ao Mexendo em Imagens    \n"
           "           Programda criado por:      \n"
           "     Luísa Scolari e Marcela Zarichta \n" 
           "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Por favor, insira o nome da imagem com a extensao:\n "
            "(Exemplo: nome_imagem.ppm)\n");
    scanf("%s", img);

    fp = fopen(img, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\033[1;31mErro: arquivo %s não encontrado\033[0m\n", img); 
        return 1;
    }

    fscanf(fp, "%s", extensaoIMG);          // lê o tipo de imagem P3
    fscanf(fp, "%d %d", &colunas, &linhas); // lê o tamanho da matriz
    fscanf(fp, "%d", &valor);               // lê o valor máximo.


    //alocando espaço na memória para a matriz
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
            mensagem();
            break;

        case 2:
            // Caso 2: Torna a imagem negativa
            matrizNova = negativa(matriz, linhas, colunas);
            mensagem();
            break;

        case 3:
            // Caso 3: Aumenta o brilho da imagem cinzenta
            printf("Por favor, insira a porcentagem para aumentar o brilho: ");
            scanf("%d", &percentual);
            matrizNova = aumentaBrilho(matriz, linhas, colunas, percentual);
            mensagem();
            break;

        case 4:
            // Caso 4: Diminui o brilho da imagem cinzenta
            printf("Por favor, insira a porcentagem para diminuir o brilho: ");
            scanf("%d", &percentual);
            matrizNova = diminuiBrilho(matriz, linhas, colunas, percentual);
            mensagem();
            break;

        case 5:
            // Caso 5: Gira a imagem colorida em 90 graus
            matrizNova = girar(matriz, linhas, colunas);
            int temp = linhas;
            linhas = colunas;
            colunas = temp;
            mensagem();
            break;

        case 6:
            // Caso 6: Envelhece a imagem
            matrizNova = envelhecer(matriz, linhas, colunas);
            mensagem();
            break;

        case 0:
            break;
        default:
            // Se nao seguir nenhum dos casos acima, aparece uma mensagem dizendo erro e volta para o menu.
            fprintf(stderr, "\033[1;31mErro: opção inválida!\033[0m\n");
            break;
    }

        // Abertura do arquivo para escrita
        FILE *fp_novo = fopen("ImgNova.ppm", "w");
        if (fp_novo == NULL)
        {
            fprintf(stderr,"\033[1;31mErro! Nao foi possivel criar a imagem ImgNova.pmp\033[0m\n");
            return 1;
        }

        // Gravação dos valores dos pixels RGB
        fprintf(fp_novo, "P3\n\n%d %d\n255\n", colunas, linhas);
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                fprintf(fp_novo, "%d\n%d\n%d\n", matrizNova[i][j].R, matrizNova[i][j].G, matrizNova[i][j].B);
            }
        }
        // Fechamento do arquivo
        fclose(fp_novo);
    

    for (int i = 0; i < linhas; i++) 
    {
        free(matriz[i]);
    }
    free(matriz);

    printf(""
            "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
            "                   FIM                \n"
            "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    return 0;
}