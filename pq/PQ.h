#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct pq PQ;

PQ* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(PQ* f, int id, double value); // Insere Vertice na PQ. A maior prioridade é a do Vertice com menor campo 'value'
int PQ_delmin(PQ* f);     // Remove Vertice com menor campo 'value' da PQ
void PQ_decrease_key(PQ* f, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(PQ* f);      // Retorna Vertice com menor campo 'value' da PQ
bool PQ_empty(PQ* f);        // Retorna True se a PQ não tem elementos
int  PQ_size(PQ* f);         // Número de elementos na PQ
bool PQ_contains(PQ* f, int id);
void PQ_finish(PQ* f);       // Libera memória

void PQ_imprime(PQ* f);

#endif
