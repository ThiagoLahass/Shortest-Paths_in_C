#ifndef GRAFO_H
#define GRAFO_H

#include "aresta.h"
#include "PQ.h"

typedef struct grafo Grafo;

/** @brief Inicializa um grafo, composto pelo número de vértices e pela lista de adjacência
 * 
 *  @param int quantidadeVertices 
 *  @return Grafo* grafo inicializado
*/
Grafo* grafo_constroi(int quantidadeVertices);

/** @brief Adiciona uma nova aresta na lista de adjacência, a partir do vértice de origem
 * 
 *  @param Grafo* grafo utilizado
 *  @param Aresta* aresta a ser adicionada
 *  @param int vértice de origem da aresta
*/
void grafo_adicionaAresta(Grafo* g, Aresta* a, int origem);

/** @brief Lê o arquivo de entrada e constrói o grafo 
 * 
 *  @param File* arquivo de entrada
 *  @param int número de arestas do arquivo
 *  @param int número de vértices do arquivo
 *  @param double velocidade inicial de todos os caminhos
 *  @return Grafo* grafo construído
*/
Grafo* grafo_LeArquivo(FILE *file, int quantidadeArestas, int quantidadeVertices, double velocidadeInicial);

/** @brief Implementa o algoritmo de Dijkstra
 * 
 *  @param Grafo* grafo 
 *  @param int* verticesMenorTempo[v] indica que o menor caminho para v é vetor[v]
 *  @param int vértice de origem do caminho
 *  @param int vértice de destino do caminho
*/
void dijkstra(Grafo* g, int* verticesMenorTempo, int origem, int destino);

/** @brief Relaxa as arestas e atualiza a fila de prioridade
 * 
 *  @param Grafo* grafo 
 *  @param PQ* fila de prioridade mínima
 *  @param double* tempoDesdeOrigem[v] indica o tempo de v até a origem
 *  @param int* verticesMenorTempo[v] indica que o menor caminho para v é vetor[v]
 *  @param int vértice de origem do caminho
*/
void grafo_relaxaAresta(Aresta* a, PQ* fila, double* tempoDesdeOrigem, int* verticesMenorTempo, int vertice);

/** @brief Identifica o menor caminho da origem até o destino
 * 
 *  @param int* armazena o menor caminho a ser percorrido (do final ao início)
 *  @param int* verticesMenorTempo[v] indica que o menor caminho para v é vetor[v]
 *  @param int número de vértices do grafo
 *  @param int vértice de destino do caminho
*/
void grafo_geraMenorCaminho(int* verticesCaminhoAPercorrer, int* verticesMenorTempo, int numVertices, int destino);

/** @brief Encontra a aresta no grafo, dado os vértices de origem e destino
 * 
 *  @param Grafo* grafo
 *  @param int vértice de origem
 *  @param int vértice de destino
 *  @return Aresta* aresta que une os vértices de origem e destino
*/
Aresta* grafo_retornaAresta(Grafo* g, int origem, int destino);

/** @brief Coloca o resultado final do algoritmo no arquivo de saída
 * 
 *  @param FILE* arquivo de saída
 *  @param int número de vértices percorridos
 *  @param int* vetor que contém os vértices percorridos 
 *  @param double distância percorrida para realizar o caminho
 *  @param double tempo gasto para realizar o caminho
*/
void grafo_geraOutput(FILE* outputFile, int numVerticesPercorridos, int* caminhoPercorrido, double distanciaPercorrida, double tempoGasto);

/** @brief Libera a memória utilizada pelo grafo
 * 
 *  @param Grafo* grafo a ser liberado
*/
void grafo_free(Grafo* g);

#endif