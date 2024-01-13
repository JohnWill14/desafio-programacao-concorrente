#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void init();
void fillMatrix();
void freeVariables();

typedef struct matriz_settings{
    int largura;
    int altura;
} matriz_settings;

//COISAS DA MATRIZ PRINCIPAL
matriz_settings m_settings;
int** matriz;

int main(){

    init();
    freeVariables();

    return 0;
}

void init(){
    printf("Insira a altura da matriz: ");
    scanf("%d", &m_settings.altura);

    printf("Insira a largura da matriz: ");
    scanf("%d", &m_settings.largura);

    printf("\nMATRIZ %02dX%02d\n",m_settings.altura, m_settings.largura );

    matriz = (int**) malloc(m_settings.altura * sizeof (int*));

    for(int i=0;i<m_settings.altura;i++){
         matriz[i] = (int*) malloc(m_settings.largura * sizeof (int*));
    }

    fillMatrix();
}

void fillMatrix(){
    srand(time(NULL));

    for(int i=0;i<m_settings.altura;i++){
        for(int j=0;j<m_settings.largura;j++){
             matriz[i][j] = rand()%10;
             printf("%d ",matriz[i][j]);
        }
        puts("");
    }
}

void freeVariables(){
    for(int i=0;i<m_settings.altura;i++){
        free(matriz[i]);
    }

    free(matriz);
}