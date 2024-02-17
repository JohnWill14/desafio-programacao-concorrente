#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include "Pair.h"
#include "List.h"


#define Matriz int**
#define scan_int(x) scanf("%d", &x); 
#define alloc(X,T,R) (R) malloc(X * sizeof (T*));


void init();
void fillMatrix();
void freeVariables();
void *perform(void *ptr);
void initCoordinates();
int calculate_new_value_for_position(int i,int j);
int getMatriz(int x, int y);
void printMatriz();
bool valid_Coordiante(Pair* p, int x, int y);
int getMirror(int x, int y);
void calculate_all();
int get_mirror_column(int x);

typedef struct matriz_settings{
    int largura;
    int altura;
} Matriz_settings;

//COISAS DA MATRIZ PRINCIPAL
Matriz_settings m_settings;
Matriz matriz;
Matriz matriz_mirror;

List* coordinates;

pthread_mutex_t mutex;

int main(){

    init();
    calculate_all();
    
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
    matriz_mirror = alloc(m_settings.altura , int, Matriz);

    for(int i=0;i<m_settings.altura;i++){
         matriz[i] = alloc(m_settings.largura, int, int*);
         matriz_mirror[i] = alloc(get_mirror_column(m_settings.largura), int, int*);
    }

    puts("Before:");
    fillMatrix();
    
    initCoordinates();

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

    for(int i=0;i<m_settings.altura;i++){
        for(int j=0;j<get_mirror_column(m_settings.largura) / 8;j++){
             matriz_mirror[i][j] = 0;
        }
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
    int x[] = { 1, 1, 0, -1, -1, -1, 0, 1};
    int y[] = { 0, 1, 1,  1,  0, -1,  -1,  -1};

    coordinates = list_create();

    for(int i=0;i<8;i++){
        Pair* p = create_pair(x[i], y[i]);
        list_add(coordinates, p);
    }
}

void calculate_all() {
    pthread_t* threadsList = alloc(m_settings.altura, pthread_t, pthread_t*);

    int args[m_settings.altura];

    for(int i = 0; i < m_settings.altura; i++) {
        args[i] = i;
        pthread_create(&threadsList[i], NULL, perform, (void*)(&args[i]));
    }

    for(int i = 0; i < m_settings.altura; i++) {
        pthread_join(threadsList[i], NULL);
    }

    free(threadsList);
}

void *perform(void *ptr){
    int *ponteiro_int;
    ponteiro_int = (int*) ptr;
    int row = *ponteiro_int; 
    
    for(int j=0;j<m_settings.largura;j++){
        int value = calculate_new_value_for_position(j,row);

        pthread_mutex_lock(&mutex);
        matriz[row][j] = value;
        matriz_mirror[row][get_mirror_column(j)] |= 1 << (j % 8);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int calculate_new_value_for_position(int x,int y){
    int cont = 0;
    int sum = 0;

    list_forEach(coordinate, coordinates){
        Pair* p = getValue(coordinate, Pair*);

        int px = pair_get_x(p)+x;
        int py = pair_get_y(p)+y;

        if(valid_Coordiante(p, px, py)){
            cont++;
            sum += getMatriz(py ,px);
        }
    }

    return sum/cont;
}

int getMatriz(int x, int y){
    return matriz[x][y];
}

int getMirror(int x, int y){
    int bit = y % 8;
    int pos = get_mirror_column(y);
    return matriz_mirror[x][pos] & (1 << bit);
}


bool valid_Coordiante(Pair* p, int x, int y){
    if(x<0||y<0){
        return false;
    }

    if(x>=m_settings.largura || y>=m_settings.altura ){
        return false;
    }


    if(pair_get_y(p)<0){
        while(getMirror(y, x) == 0){
            //wait..
        }
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

int get_mirror_column(int x)
{
    return (x + 8 - 1) / 8;
}