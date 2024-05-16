#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int R, G, B;
} Pixel;

 Pixel **cinza(Pixel **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int cinza = (matriz[i][j].R + matriz[i][j].G + matriz[i][j].B) / 3;

            matriz[i][j].R = cinza;
            matriz[i][j].G = cinza;
            matriz[i][j].B = cinza;
        }
    }

    return matriz;
}

 Pixel **negativa(Pixel **matrizN, int linhas, int colunas) {
    matrizN = cinza(matrizN, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matrizN[i][j].R = 255 - matrizN[i][j].R;
            matrizN[i][j].G = 255 - matrizN[i][j].G;
            matrizN[i][j].B = 255 - matrizN[i][j].B;
        }
    }
    return matrizN;
}


 Pixel **aumentaBrilho(Pixel **matrizA, int linhas, int colunas) {
    matrizA = cinza(matrizA, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
           //codigo para aumentar o brilho
        }
    }
    return matrizA;
}


 Pixel **diminuiBrilho(Pixel **matrizD, int linhas, int colunas) {
    matrizD = cinza(matrizD, linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
           //codigo para diminuir o brilho
        }
    }
    return matrizD;
}

 Pixel **girar(Pixel **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
           //codigo para girar
        }
    }
    return matriz;
}

 Pixel **envelhecer(Pixel **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
           //codigo para envelhecer
        }
    }
    return matriz;
 }

int main(void){
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
        if(fp == NULL){
            fprintf(stderr, "Erro ao abrir o arquivo %s.\n", img);
            exit(EXIT_FAILURE);
        }


    fscanf(fp, "%s", extensaoIMG); 					// lê o tipo de imagem P3 
    fscanf(fp, "%d %d", &colunas, &linhas); 	// lê o tamanho da matriz  
    fscanf(fp, "%d", &valor); 					// lê o valor máximo. 
    
    
    Pixel **matriz = (Pixel **)malloc(linhas * sizeof(Pixel *));


    for (int i = 0; i < linhas; i++) {
        matriz[i] = (Pixel *)malloc(colunas * sizeof(Pixel));

    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
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


    for (int i = 0; i < linhas; i++) {
        matrizNova[i] = (Pixel *)malloc(colunas * sizeof(Pixel));

    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++){
            fscanf(fp, "%d %d %d", &r, &g, &b); 
            matrizNova[i][j].R = r;
            matrizNova[i][j].G = g;
            matrizNova[i][j].B = b;
        }

switch (escolha) {
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
        //se nao seguir nenhum dos casos acima, aparece uma mensagem dizendo erro.
        printf("Erro!");
        break;
}

// Abertura do arquivo para escrita
FILE *fp_novo = fopen("ImgNova.ppm", "w");
if (fp_novo == NULL) {
    fprintf(stderr, "Erro! Nao foi possivel criar a imagem ImgNova.pmp\n");
    exit(EXIT_FAILURE);
}

// Gravação dos valores dos pixels RGB
fprintf(fp_novo, "P3\n%d %d\n255\n", colunas, linhas);
for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        fprintf(fp_novo, "%d %d %d ", matrizNova[i][j].R, matrizNova[i][j].G, matrizNova[i][j].B);
    }
    fprintf(fp_novo, "\n"); // Adiciona uma nova linha após cada linha de pixels
}

// Fechamento do arquivo
fclose(fp_novo);
    }

}

