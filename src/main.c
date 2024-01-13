#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include <stdbool.h>
#include "Pair.h"
#include "List.h"

#define Matriz int**
#define scan_int(x) scanf("%d", &x); 
#define alloc(X,T,R) (R) malloc(X * sizeof (T*));


void init();
void fillMatrix();
void freeVariables();
void perform();
void initCoordinates();
int calculate_new_value_for_position(int i,int j);
int getMatriz(int x, int y);
void printMatriz();
bool valid_Coordiante(Pair* p, int x, int y);

typedef struct matriz_settings{
    int largura;
    int altura;
} Matriz_settings;

//COISAS DA MATRIZ PRINCIPAL
Matriz_settings m_settings;
Matriz matriz;
Matriz matriz_mirror;

List* coordinates;

int main(){
    puts("Before:");
    init();

    perform();
    
    puts("After:");
    printMatriz();

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
    matriz_mirror = alloc(m_settings.altura, int, Matriz);

    for(int i=0;i<m_settings.altura;i++){
         matriz[i] = alloc(m_settings.largura, int, int*);
         matriz_mirror[i] = alloc(m_settings.largura, int, int*);
    }


    fillMatrix();
    
    initCoordinates();
}

void fillMatrix(){
    srand(time(NULL));

    for(int i=0;i<m_settings.altura;i++){
        for(int j=0;j<m_settings.largura;j++){
             matriz[i][j] = rand()%10;
             matriz_mirror[i][j] = 0;
             printf("%d ",matriz[i][j]);
        }
        puts("");
    }
}

void freeVariables(){
    list_forEach(coordinate, coordinates){
        pair_free(getValue(coordinate, Pair*));
    }

    list_free(coordinates);
    
    for(int i=0;i<m_settings.altura;i++){
        free(matriz[i]);
        free(matriz_mirror[i]);
    }

    free(matriz);
    free(matriz_mirror);
}

void initCoordinates(){
    int x[] = {0,1,1,0,-1,-1,-1,-1,-1};
    int y[] = {0,0,1,1,1,0,-1,0,1};

    coordinates = list_create();

    for(int i=0;i<9;i++){
        Pair* p = create_pair(x[i], y[i]);
        list_add(coordinates, p);
    }
}
void perform(){
    for(int i=0;i<m_settings.altura;i++){
        for(int j=0;j<m_settings.largura;j++){
             matriz[i][j] = calculate_new_value_for_position(j,i);
        }
    }

}

int calculate_new_value_for_position(int x,int y){
    int cont = 0;
    int sum = 0;

    list_forEach(coordinate, coordinates){
        Pair* p = getValue(coordinate, Pair*);

        int px = pair_get_x(p)+x;
        int py = pair_get_y(p)+y;

        if(valid_Coordiante(p, px, py)){
            printf("(%d %d) %d %d => %dok\n",x,y,px,py, getMatriz(py, px));
            cont++;
            sum += getMatriz(py ,px);
        }
    }

    return sum/cont;
}

int getMatriz(int x, int y){
    return matriz[x][y];
}


bool valid_Coordiante(Pair* p, int x, int y){
    if(x<0||y<0){
        return false;
    }

    if(x>=m_settings.largura || y>=m_settings.altura ){
        return false;
    }

    return true;
}

void printMatriz(){
     for(int i=0;i<m_settings.altura;i++){
        for(int j=0;j<m_settings.largura;j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}