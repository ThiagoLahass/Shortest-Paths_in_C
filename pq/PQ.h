#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

void PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Item);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin();       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min();          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty();        // Retorna True se a PQ não tem elementos
int  PQ_size();         // Número de elementos na PQ
void PQ_finish();       // Libera memória

#endif
