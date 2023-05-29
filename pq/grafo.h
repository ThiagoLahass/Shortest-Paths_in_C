#ifndef GRAFO_H
#define GRAFO_H

#include "aresta.h"
#include "PQ.h"

typedef struct grafo Grafo;

Grafo* grafo_constroi(int quantidadeVertices);

void grafo_adicionaAresta(Grafo* g, Aresta* a, int origem);

Grafo* grafo_LeArquivo(FILE *file, int quantidadeArestas, int quantidadeVertices, double velocidadeInicial);

void grafo_exibe(Grafo* g);

void dijkstra(Grafo* g, int* verticesMenorCaminho, int origem, int destino);

void grafo_relaxaAresta(Aresta* a, PQ* fila, double* distanciaOrigem, int* verticesMenorCaminho, int vertice);

void grafo_exibeMenorCaminho(int* verticesMenorCaminho, int quantidadeVertices, int origem);

void grafo_free(Grafo* g);

#endif