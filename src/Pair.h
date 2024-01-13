#include<stdlib.h>

#define alloc(X,T,R) (R) malloc(X * sizeof (T*));

typedef struct pair{
    int first;
    int second;
} Pair;


Pair* create_pair(int x, int y){
    Pair* p = alloc(1, Pair, Pair*);

    p->first = x;
    p->second = y;

    return p;
}


int pair_get_first(Pair* p){
    return p->first;
}

int pair_get_second(Pair* p){
    return p->second;
}


int pair_get_x(Pair* p){
    return pair_get_first(p);
}

int pair_get_y (Pair* p){
    return pair_get_second(p);
}

void pair_free(Pair* p){
    free(p);
}