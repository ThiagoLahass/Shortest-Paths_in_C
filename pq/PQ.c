#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pq{
    Item* v;
    int* map;
    int N;
};

static void swap(PQ* f, int i, int j) {
    exch(f->v[i], f->v[j]);
    f->map[id(f->v[i])] = i;
    f-> map[id(f->v[j])] = j;
}

void fix_up(PQ* f, int k) {
    // printf("In fix_up...\n");
    // printf(" f->v[k] = %d\n", f->v[k]);
    while (k > 1 && more(f->v[k/2], f->v[k])) {
        // printf("While...\n");
        swap(f, k, k/2);
        k = k/2;
    }
}

void fix_down(PQ* f, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(f->v[j], f->v[j+1])){
      j++;
    }
    if (!more(f->v[k], f->v[j])) {
      break;
    }
    swap(f,k, j);
    k = j;
  }
}

PQ* PQ_init(int maxN) {
    PQ* nova = malloc(sizeof(PQ));    
    nova->v = (Item *) malloc((maxN+1) * sizeof (Item));
    nova->map = (int *) malloc((maxN+1) * sizeof (int));
    nova->N = 0;
    return nova;
}

void PQ_insert(PQ* f, int id, double value) {

    printf("\n\nInserindo elemento %d, com peso %f, na fila...\n\n", id, value);
    f->N++;
    Item novo; novo.id = id; novo.value = value; 
    
    f->v[f->N] = novo;
    f->map[id(novo)] = f->N;
    fix_up(f, f->N);
}

int PQ_delmin(PQ* f) {
    Item min = f->v[1];
    swap(f, 1, f->N);
    f->N--;
    fix_down(f, f->N, 1);
    return min.id;
}

Item PQ_min(PQ* f) {
    return f->v[1];
}

void PQ_decrease_key(PQ* f, int id, double value) {
    // printf("Decreasing key...\n");
    int i = f->map[id];
    // printf("i = %d\n", i);
    // printf("Id = %d\n", id);
    // printf("Value = %f\n", value);
    value(f->v[i]) = value;
    // printf("value(f->v[i]) = %f\n", value(f->v[i]));
    // printf("Fix_up...\n");
    fix_up(f, i);
}

bool PQ_empty(PQ* f) {
    return f->N == 0;
}

int  PQ_size(PQ* f) {
    return f->N;
}

bool PQ_contains(PQ* f, int id){
    for(int i=1; i<=f->N; i++) if(id(f->v[i]) == id) return true;
    return false;
}

void PQ_finish(PQ* f) {
    free(f->v);
    free(f->map);
    free(f);
}

void PQ_imprime(PQ* f){
    printf("Fila atual:\n");
    printf("No:     ");
    for(int i=1; i<=f->N; i++){
        printf("%-10d ", f->v[i].id);
    }

    printf("\nValue:  ");

    for(int i=1; i<=f->N; i++){
        printf("%-10f ", f->v[i].value);
    }

    printf("\n\n");

}


