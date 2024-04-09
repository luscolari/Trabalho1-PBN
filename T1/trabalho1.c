#include <stdio.h>
#include <stdlib.h>



void imagemCinza(FILE) {
    //matriz[j][i] = (r*0.30)+(g*0.59)+(b*0.11);


}

void imagemEnvelhecida(FILE) {
//Subtrair cada pixel de 20

}

void imagemNegativa(FILE) {
     //Subtrair cada pixel de 255
//Ex.: red = 130

}

void imagemBrilho(FILE) {
//Multiplicar cada pixel por 1.3, limitando a 255.

}

void imagemEscura(FILE) {
   


}

void imagemRotacionada(FILE) {

}

typedef struct  
{
    int R, G, B;
}Pixel;


int main(int){
    FILE *fp;
    int c;
    char extensaoIMG[3];
    int i, j, linhas, colunas, valor, r, g, b;
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
    matriz[i] = (int *)malloc(colunas * sizeof(int));
    }


    printf("---- BEM VINDO -----");
    printf("Por favor digite o nome da imagem: ");
   //scanf();

   FILE * fp;

   fp = fopen ("kyle.ppm", "r");

    fscanf(fp, "%s", extensaoIMG); 					// lê o tipo de imagem P3 
    fscanf(fp, "%d %d", &colunas, &linhas); 	// lê o tamanho da matriz  
    fscanf(fp, "%d", &valor); 					// lê o valor máximo. 
    

    for (i = 0; i < linhas; i++) 
    {
        for (j = 0; j < colunas; j++) 
        {
            fscanf(fp, "%d %d %d", &r, &g, &b);
            matriz[i][j].R = r;
            matriz[i][j].G = g;
            matriz[i][j].B = b;
        }
    }


    return 0;
}