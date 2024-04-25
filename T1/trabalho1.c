#include <stdio.h>
#include <stdlib.h>



typedef struct  
{
    int R, G, B;
}Pixel;


int main(void){
    FILE *fp;
    int c;
    char extensaoIMG[3];
    int i, j, linhas, colunas, valor, r, g, b;


    printf("---- BEM VINDO -----");
    printf("Por favor digite o nome da imagem: ");
   //scanf();

   fp = fopen ("kyle.ppm", "r");

    fscanf(fp, "%s", extensaoIMG); 					// lê o tipo de imagem P3 
    fscanf(fp, "%d %d", &colunas, &linhas); 	// lê o tamanho da matriz  
    fscanf(fp, "%d", &valor); 					// lê o valor máximo. 
    
    
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

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d", matriz[i][j]);
        }
    }

     for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    fclose(fp);

}
