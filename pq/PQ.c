#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

static Item *pq;
static int *map;
static int N;

static void swap(int i, int j) {
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j);
    k = j;
  }
}

void PQ_init(int maxN) {
    pq = (Item *) malloc((maxN+1) * sizeof (Item));
    map = (int *) malloc((maxN+1) * sizeof (int));
    N = 0;
}

void PQ_insert(Item v) {
    N++;
    pq[N] = v;
    map[id(v)] = N;
    fix_up(pq, N);
}

Item PQ_delmin() {
    Item min = pq[1];
    swap(1, N);
    N--;
    fix_down(pq, N, 1);
    return min;
}

Item PQ_min() {
    return pq[1];
}

void PQ_decrease_key(int id, double value) {
    int i = map[id];
    value(pq[i]) = value;
    fix_up(pq, i);
}

bool PQ_empty() {
    return N == 0;
}

int  PQ_size() {
    return N;
}

void PQ_finish() {
    free(pq);
    free(map);
}


