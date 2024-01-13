#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define Matriz int**
#define scan_int(x) scanf("%d", &x); 
#define alloc(X,T,R) (R) malloc(X * sizeof (T*));

void init();
void fillMatrix();
void freeVariables();

typedef struct matriz_settings{
    int largura;
    int altura;
} Matriz_settings;

//COISAS DA MATRIZ PRINCIPAL
Matriz_settings m_settings;
Matriz matriz;

int main(){

    init();
    freeVariables();

    return 0;
}

void init(){
    printf("Insira a altura da matriz: ");
    scan_int(m_settings.altura);

    printf("Insira a largura da matriz: ");
    scan_int(m_settings.largura);

    printf("\nMATRIZ %02dX%02d\n",m_settings.altura, m_settings.largura );

    matriz = alloc(m_settings.altura, int, Matriz);

    for(int i=0;i<m_settings.altura;i++){
         matriz[i] = alloc(m_settings.largura, int, int*);
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