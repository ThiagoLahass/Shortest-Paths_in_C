#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "grafo.h"

typedef struct no No;

struct no{
    Aresta* a; 
    No* prox;
};

struct grafo{
    int quantidadeVertices;
    No** lista;
};

Grafo* grafo_constroi(int quantidadeVertices){
    Grafo* novo = malloc(sizeof(Grafo));   
    novo->lista = malloc(sizeof(No*)*(quantidadeVertices+1));
    for(int i=0; i<=quantidadeVertices; i++) novo->lista[i] = NULL;
    novo->quantidadeVertices = quantidadeVertices;
    
    return novo;
}

void grafo_adicionaAresta(Grafo* g, Aresta* a, int origem){
    No** p = &(g->lista[origem]);
   
    if (*p == NULL){
        *p = malloc(sizeof(No));
        (*p)->a = a;
        (*p)->prox = NULL;
        return;
    }

    while (*p != NULL){
        p = &((*p)->prox);
    }
    
    No* novo = malloc(sizeof(No));
    novo->a = a;
    novo->prox = NULL;  
    *p = novo;
}

Grafo* grafo_LeArquivo(FILE *file, int quantidadeArestas, int quantidadeVertices, double velocidadeInicial){
    Grafo* g = grafo_constroi(quantidadeVertices);
    char *line = malloc(50*sizeof(char));  //recebe todos os dados de uma linha
    size_t len = 50;                       //somente usado na função getline

    for(int i=0; i<quantidadeArestas && ((getline(&line, &len, file)) != -1); i++){
        int origem        = atoi(strtok(line, ";")); 
        int destino       = atoi(strtok(NULL, ";"));
        double distancia  = atof(strtok(NULL, ";"));
        
        Aresta* a = aresta_constroi(origem, destino, distancia, velocidadeInicial); 
        grafo_adicionaAresta(g, a, origem);
    }
    free(line);
    return g;
}

void dijkstra(Grafo* g,  int origem, int destino){
    double* distanciaOrigem = malloc(sizeof(double)*(g->quantidadeVertices+1));
    int* verticesMenorCaminho = malloc(sizeof(int)*(g->quantidadeVertices+1));
    int* verticesJaComMenorCaminho = malloc(sizeof(int)*(g->quantidadeVertices+1)); 

    for(int i=0; i<=g->quantidadeVertices; i++){
        distanciaOrigem[i] = INFINITY;
        verticesMenorCaminho[i] = -1;
        verticesJaComMenorCaminho[i] = 0;
    }

    distanciaOrigem[origem] = 0.0;

    PQ* fila = PQ_init(g->quantidadeVertices);
    PQ_insert(fila, origem, distanciaOrigem[origem]);


    while(!PQ_empty(fila)){
        int vertice = PQ_delmin(fila);
        verticesJaComMenorCaminho[vertice] = 1; //Define que esse vertice ja possui o menor caminho definido

        for(No* p = g->lista[vertice]; p!=NULL; p = p->prox){
            if( !verticesJaComMenorCaminho[aresta_retornaDestino(p->a)] ){
                grafo_relaxaAresta(p->a, fila, distanciaOrigem, verticesMenorCaminho, vertice);
            }
        }
    }

    grafo_exibeMenorCaminho(verticesMenorCaminho, g->quantidadeVertices, origem);
    free(distanciaOrigem);
    free(verticesMenorCaminho);
    free(verticesJaComMenorCaminho);
    PQ_finish(fila);
}

void grafo_relaxaAresta(Aresta* a, PQ* fila, double* distanciaOrigem, int* verticesMenorCaminho, int vertice){
    int destino = aresta_retornaDestino(a);
    double distancia = aresta_retornaDistancia(a), velocidade = aresta_retornaVelocidade(a); 

    if(distanciaOrigem[destino] > (distanciaOrigem[vertice] + distancia)){
        distanciaOrigem[destino] = distanciaOrigem[vertice] + distancia;
        verticesMenorCaminho[destino] = vertice;

        if(PQ_contains(fila, destino)) PQ_decrease_key(fila, destino, distanciaOrigem[destino]);
        else PQ_insert(fila, destino, distanciaOrigem[destino]);
    }
}


void grafo_exibeMenorCaminho(int* verticesMenorCaminho, int quantidadeVertices, int origem){
    printf("\nOrigem: %d", origem);
    printf("\nv =         ");
    for(int i=1; i<=quantidadeVertices; i++){
        printf("%-10d ", i );
    }
    printf("\nEdgeTo[] =  ");
    for(int i=1; i<=quantidadeVertices; i++){
        printf("%-10d ", verticesMenorCaminho[i]);
    }
    printf("\n\n");
}

void grafo_exibe(Grafo* g){
    printf("%d\n", g->quantidadeVertices);
    for(int i=1; i<=g->quantidadeVertices; i++){
        printf("Vertice %d: ", i);
        
        for(No* p = g->lista[i]; p!=NULL; p = p->prox){
            aresta_imprime(p->a);
        }
        printf("\n");
    }
}

void grafo_free(Grafo* g){
    for(int i=0; i<=g->quantidadeVertices; i++){
        No* p = g->lista[i];
        No* temp = NULL;

        while(p!=NULL){
            temp = p->prox;
            free(p->a);
            free(p);
            p = temp;
        }
    }

    free(g->lista);
    free(g);
}
