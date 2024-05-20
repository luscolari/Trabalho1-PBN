#include <stdio.h>
#include <stdlib.h>

//Struct para o pixel;
typedef struct
{
    //cada pixel tem tres atributos representando as cores que os compoem,
    //sendo estas R(red/ vermelho), G (green/ verde) e B (blue/ azul)
    int R, G, B;
} Pixel;

//função que torna uma imagem acinzentada
Pixel **cinza(Pixel **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; ++i)
    {
        for (int j = 0; j < colunas; ++j)
        {
            //cria o tom de cinza de cada pixel (a soma do RGB dividida por 3)
            int cinza = (matriz[i][j].R + matriz[i][j].G + matriz[i][j].B) / 3;

            //atribui o valor cinza ao RGB do pixel
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
    //chama a funcao cinza
    cinza(matrizN, linhas, colunas);

    //inverte as cores da imagem cinza atribuindo aos valores RGB de cada pixel seu complemento
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

//Função que aumenta o brilho na porcentagem dada pelo usuario na imagem cinza
Pixel **aumentaBrilho(Pixel **matrizA, int linhas, int colunas, int percentual)
{
    //chama a funcao cinza
    cinza(matrizA, linhas, colunas);

    //aumenta o brilho de cada pixel ao adicionar ao RGB o percentual de brilho
    //solicitado pelo usuario
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizA[i][j].R = matrizA[i][j].R + (matrizA[i][j].R * percentual/100);
            matrizA[i][j].G = matrizA[i][j].G + (matrizA[i][j].G * percentual/100);
            matrizA[i][j].B = matrizA[i][j].B + (matrizA[i][j].B * percentual/100);

            //verifica se os valores de cada cor de cada pixel nao estao passando do valor
            //maximo (255). Caso estejam, atribui o valor maximo a eles
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


//Função que diminui o brilho de uma imagem cinza em ate 100%
Pixel **diminuiBrilho(Pixel **matrizD, int linhas, int colunas, int percentual)
{
    //chama a funcao cinza
    cinza(matrizD, linhas, colunas);

    //diminui o brilho de cada pixel ao subtrair do RGB o percentual de brilho
    //solicitado pelo usuario
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizD[i][j].R = matrizD[i][j].R - (matrizD[i][j].R * percentual/100);
            matrizD[i][j].G = matrizD[i][j].G - (matrizD[i][j].G * percentual/100);
            matrizD[i][j].B = matrizD[i][j].B - (matrizD[i][j].R * percentual/100);

            //verifica se os valores de cada cor de cada pixel nao estao passando do valor
            //minimo (0). Caso estejam, atribui o valor minimo a eles
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
Pixel **girar(Pixel **matriz, int linhas, int colunas)
{
    //aloca espaco na memoria para a matrizGirada, porem com as proporcoes invertidas
    Pixel **matrizGirada = (Pixel **)malloc(colunas * sizeof(Pixel *));
    for (int i = 0; i < colunas; i++)
    {
        matrizGirada[i] = (Pixel *)malloc(linhas * sizeof(Pixel));
    }

    //inverte as coordenadas da matriz original e copia os pixels para a matrizGirada.
    for (int j = 0; j < colunas; j++)
    {
        for (int i = 0; i < linhas; i++)
        {
            matrizGirada[j][i] = matriz[linhas - i - 1][j];
        }
    }

    return matrizGirada;
}

//Função que envelhece uma imagem colorida
Pixel **envelhecer(Pixel **matriz, int linhas, int colunas)
{
    //deixa a imagem com aspecto de envelhecida diminuindo 20 do RGB de cada pixel
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
//e sugerindo ao usuario um jeito de ver o resultado
void mensagem()
{
    printf("--------------------------------------\n"
           "           Operação realizada         \n"
           "              com sucesso!            \n"
           "--------------------------------------\n"
           "  Para ver o resultado, abra o arquivo\n" 
        "   \033[1;30mImgNova.ppm\033[0m no Gimp.    \n"
           "--------------------------------------\n");
}

int main()
{
    //cria um ponteiro que aponta para um arquivo
    FILE *fp;

    //armazena o tipo de imagem P3
    char extensaoIMG[3];

    //cria as variaveis necessarias para manipular a matriz
    int linhas, colunas, valor, r, g, b, percentual;

    //variavel usada no switch onde o usuario escolhe a alteracao que quer na imagem
    int escolha = -1;

    //variavel que armazena o nome da imagem digitada pelo usuario
    char img[100];

    //exibe a mensagem inicial do programa e instrui o usuario sobre
    //o formato que a imagem deve ser digitada
    printf("--------------------------------------\n"
           "   Bem-vindo ao Mexendo em Imagens    \n"
           "           Programda criado por:      \n"
           "     Luísa Scolari e Marcela Zarichta \n" 
           "--------------------------------------\n");
    printf("Por favor, insira o nome da imagem com a extensao:\n "
            "(Exemplo: nome_imagem.ppm)\n");

    //recebe o nome da imagem digitada pelo usario
    scanf("%s", img);

    //tenta abrir o arquivo de nome armazenado em "img" no modo leitura
    //(indicado por "r"). Caso ache o arquivo, fp passara a apontar para ele
    fp = fopen(img, "r");

    //caso fp nao esteja apontando para nenhum arquivo, aparece uma mensagem de
    //erro em negrito e vermelho e encerra o programa com saida 1, indicando um erro
    if (fp == NULL)
    {
        fprintf(stderr, "\033[1;31mErro: arquivo %s não encontrado\033[0m\n", img); 
        return 1;
    }

    //usa a funcao fscanf para ler o arquivo fp do inicio
    fscanf(fp, "%s", extensaoIMG);          // lê o tipo de imagem P3
    fscanf(fp, "%d %d", &colunas, &linhas); // lê o tamanho da matriz
    fscanf(fp, "%d", &valor);               // lê o valor máximo que um numero pode atingir


    //alocando espaço na memória para a matriz
    Pixel **matriz = (Pixel **)malloc(linhas * sizeof(Pixel *));
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    //esta lendo os valores RGB de cada pixel da imagem e armazenando nesses atributos de matriz
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

    //fecha o arquivo apontado por fp
    fclose(fp);

    //exibe as opcoes de alteracoes de imagem para o usuario
    printf(""
                                            "--------------------------------------\n"
                                            "       Escolha o que deseja fazer     \n"
                                            "             com a imagem:            \n"
                                            "--------------------------------------\n"
                                            "  [1] - Tons de Cinza                 \n"
                                            "  [2] - Negativa                      \n"
                                            "  [3] - Aumentar o brilho             \n"
                                            "  [4] - Diminuir o brilho             \n"
                                            "  [5] - Girar 90 graus                \n"
                                            "  [6] - Envelhecer                    \n"
                                            "  [0] - Sair                          \n"
                                            "--------------------------------------\n");
    scanf("%d", &escolha);

    // Definição da matrizNova
    Pixel **matrizNova = (Pixel **)malloc(linhas * sizeof(Pixel *));
    for (int i = 0; i < linhas; i++)
    {
        matrizNova[i] = (Pixel *)malloc(colunas * sizeof(Pixel));
    }

    //opcoes de escolha feitas pelo usuario sobre o que quer fazer com a imagem
    switch (escolha)
    {
        case 1:
            // Caso 1: Torna a imagem cinza

            //matrizNova recebe o resultado da funcao cinza
            matrizNova = cinza(matriz, linhas, colunas);
            mensagem();
            break;

        case 2:
            // Caso 2: Torna a imagem negativa

            //matrizNova recebe o resultado da funcao negativa
            matrizNova = negativa(matriz, linhas, colunas);
            mensagem();
            break;

        case 3:
            // Caso 3: Aumenta o brilho da imagem cinzenta

            //pede para o usuario digitar a porcentagem de brilho que quer aumentar
            printf("Por favor, insira a porcentagem para aumentar o brilho: ");

            //le esse valor e guarda na variavel percentual
            scanf("%d", &percentual);

            //matrizNova recebe o resultado da funcao aumentarBrilho
            matrizNova = aumentaBrilho(matriz, linhas, colunas, percentual);
            mensagem();
            break;

        case 4:
            // Caso 4: Diminui o brilho da imagem cinzenta

            //pede para o usuario digitar a porcentagem de brilho que quer diminuir
            printf("Por favor, insira a porcentagem para diminuir o brilho: ");

            //le esse valor e guarda na variavel percentual
            scanf("%d", &percentual);

            //matrizNova recebe o resultado da funcao diminuirBrilho
            matrizNova = diminuiBrilho(matriz, linhas, colunas, percentual);
            mensagem();
            break;

        case 5:
            // Caso 5: Gira a imagem colorida em 90 graus

            //matrizNova recebe o resultado da funcao girar
            matrizNova = girar(matriz, linhas, colunas);

            //ao girar uma imagem em noventa graus, as proporcoes dela mudam, por isso
            //e necesario inverter os valores das linhas e colunas
            int temp = linhas;
            linhas = colunas;
            colunas = temp;
            mensagem();
            break;

        case 6:
            // Caso 6: Envelhece a imagem

            //matrizNova recebe o resultado da funcao envelhecer
            matrizNova = envelhecer(matriz, linhas, colunas);
            mensagem();
            break;

        case 0:
            // Caso 0: o usuario escolheu sair do programa, indo direto pro fim
            break;

        default:
            // Se nao seguir nenhum dos casos acima, aparece uma mensagem dizendo erro e volta para o menu.
            fprintf(stderr, "\033[1;31mErro: opção inválida!\033[0m\n");
            break;
    }

        // Abertura do arquivo para escrita
        FILE *fp_novo = fopen("ImgNova.ppm", "w");

        //verifica se conseguiu criar um novo arquivo. Caso fp_novo esteja apontando para nada,
        //houve uma falha nesse processo
        if (fp_novo == NULL)
        {
            //exibe uma mensagem de erro em vermelho e negrito, informando que nao conseguiu
            //criar uma imagem nova
            fprintf(stderr,"\033[1;31mErro! Nao foi possivel criar a imagem ImgNova.pmp\033[0m\n");

            //encerra o programa com saida 1, indicando um erro
            return 1;
        }

        // Gravação dos valores dos pixels RGB no arquivo novo
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
    

    //libera a memoria alocada para a matriz
    for (int i = 0; i < linhas; i++) 
    {
        free(matriz[i]);
    }
    free(matriz);

    //quando o programa chega ao fim sem erros, exibe esta mensagem
    printf(""
            "--------------------------------------\n"
            "                   FIM                \n"
            "--------------------------------------\n");

    //encerra o programa com saida 0, indicando que o programa terminou com sucesso
    return 0;
}