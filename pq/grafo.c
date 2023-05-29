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

static void inverterVetor(int* vetor, int tamanho) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio < fim) {
        // Trocar os elementos de posição
        int temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;

        // Avançar com os índices
        inicio++;
        fim--;
    }
}

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

void dijkstra(Grafo* g, int* verticesMenorTempo, int origem, int destino){
    double* tempoDesdeOrigem = malloc(sizeof(double)*(g->quantidadeVertices+1));
    int* verticesJaComMenorTempo = malloc(sizeof(int)*(g->quantidadeVertices+1));

    for(int i=0; i<=g->quantidadeVertices; i++){
        tempoDesdeOrigem[i] = INFINITY;
        verticesMenorTempo[i] = -1;
        verticesJaComMenorTempo[i] = 0;
    }

    tempoDesdeOrigem[origem] = 0.0;

    PQ* fila = PQ_init(g->quantidadeVertices);
    PQ_insert(fila, origem, tempoDesdeOrigem[origem]);

    while(!PQ_empty(fila)){
        int vertice = PQ_delmin(fila);
        verticesJaComMenorTempo[vertice] = 1; //Define que esse vertice ja possui o menor caminho definido

        for(No* p = g->lista[vertice]; p!=NULL; p = p->prox){
            if( !verticesJaComMenorTempo[aresta_retornaDestino(p->a)] ){
                grafo_relaxaAresta(p->a, fila, tempoDesdeOrigem, verticesMenorTempo, vertice);
            }
        }
    }

    free(tempoDesdeOrigem);
    free(verticesJaComMenorTempo);
    PQ_finish(fila);
}

void grafo_relaxaAresta(Aresta* a, PQ* fila, double* tempoDesdeOrigem, int* verticesMenorTempo, int vertice){
    int destino = aresta_retornaDestino(a);
    double tempo = aresta_retornaTempoPercurso(a);

    if(tempoDesdeOrigem[destino] > (tempoDesdeOrigem[vertice] + tempo)){
        tempoDesdeOrigem[destino] = tempoDesdeOrigem[vertice] + tempo;
        verticesMenorTempo[destino] = vertice;

        if(PQ_contains(fila, destino)) PQ_decrease_key(fila, destino, tempoDesdeOrigem[destino]);
        else PQ_insert(fila, destino, tempoDesdeOrigem[destino]);
    }
}

void grafo_geraMenorCaminho( int* verticesCaminhoAPercorrer, int* verticesMenorTempo, int numVertices, int destino ){
    int numVerticesPercorridos = 0;
    while( destino != -1 ){
        verticesCaminhoAPercorrer[numVerticesPercorridos] = destino;
        destino = verticesMenorTempo[destino];
        numVerticesPercorridos++;
    }
    for(int i = numVerticesPercorridos; i < numVertices; i++ ){
        verticesCaminhoAPercorrer[i] = 0;
    }
    inverterVetor(verticesCaminhoAPercorrer, numVerticesPercorridos);
}


void grafo_exibeEdgeTo(int* verticesMenorTempo, int quantidadeVertices, int origem){
    printf("\nOrigem: %d", origem);
    printf("\nv =         ");
    for(int i=1; i<=quantidadeVertices; i++){
        printf("%-10d ", i );
    }
    printf("\nEdgeTo[] =  ");
    for(int i=1; i<=quantidadeVertices; i++){
        printf("%-10d ", verticesMenorTempo[i]);
    }
    printf("\n\n");
}

void grafo_exibeMenorCaminho(int* caminhoAPercorrer, int quantidadeVertices){
    for(int i=0; caminhoAPercorrer[i] != 0; i++){
        if( caminhoAPercorrer[i] != 0 ){
            printf("%d", caminhoAPercorrer[i]);
            if(caminhoAPercorrer[i+1] != 0) printf(";");
        }
    }
    printf("\n");
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

Aresta* grafo_retornaAresta( Grafo* g, int origem, int destino ){
    for(int i=1; i<=g->quantidadeVertices; i++){
        if( i == origem ){
            for(No* p = g->lista[i]; p!=NULL; p = p->prox){
                if( aresta_retornaDestino(p->a) == destino ){
                    return p->a;
                }
            }
        }
    }
    return NULL;
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
