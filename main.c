#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "PQ.h"
#include "aresta.h"
#include "grafo.h"

FILE* utility_openFile(char *nameFile, char *action);

int main(int argc, char *argv[]){

    char* nameInputFile = argv[1];  //nome do arquivo Entrada
    char* nameOutputFile = argv[2]; //nome do arquivo de sáida
    FILE* inputFile = utility_openFile(nameInputFile,"r");   

    char linha[50];
    fgets(linha, 50,inputFile);
    int numbVertice = atoi(strtok(linha,";"));    //número de vertices
    int numbAresta  = atoi(strtok(NULL,";"));     //número de arestas
    
    fgets(linha, 50,inputFile);  
    int nodeOrigem   = atoi(strtok(linha,";"));    //nó de origem
    int nodeDestino  = atoi(strtok(NULL,";"));     //nó de destino
    
    fgets(linha, 10,inputFile);  
    int velocidadeInicial = atoi(linha);          //Velocidade média inicial

    Grafo* g = grafo_LeArquivo(inputFile, numbAresta, numbVertice, velocidadeInicial);

    int* verticesMenorTempo = calloc(numbVertice+1, sizeof(int));   // Vetor auxiliar para salvar os caminhos calculados por dijkstra
    int* caminhoPercorrido = calloc(numbVertice, sizeof(int));      // Vetor para salvar o caminho percorrido
    int* menorCaminhoAtual = calloc(numbVertice, sizeof(int));      // Vetor para salvar o caminho que deveria ser percorrido se nao houvesse mais atualizacoes
    double distanciaPercorrida = 0;                                 // Distancia percorrida (m)
    double tempoGasto = 0;                                          // Tempo gasto (s)
    
    double tempoProxAtualizacao = INFINITY;                         // Tempo da proxima atualizacao
    int flagHaAtualizacao = 1;
    int arestaOrigemAtualizacao = 0;
    int arestaDestinoAtualizacao = 0;
    double novaVelocidade = 0;

    int nodeAtual = nodeOrigem;         // Node atual, começando pela origem
    int numVerticesPercorridos = 0;     // Numero de vertices percorridos no total
    int count = 0;                      // Numero de vertices percorridos do caminho definido como atual

    if(fgets(linha, 50, inputFile) != NULL){
        /* FORMATO ATUALIZAÇÃO:
        Instante de tempo(s); Aresta(origem;destino); Nova velocidade media naquela aresta (em km/h)
        "tempo;origem;destino;velocidade"*/

        tempoProxAtualizacao     = atof(strtok(linha,";"));      //tempo
        arestaOrigemAtualizacao  = atoi(strtok(NULL,";"));       //nó de origem
        arestaDestinoAtualizacao = atoi(strtok(NULL,";"));       //nó de destino
        novaVelocidade           = atof(strtok(NULL,";"));       //nova Velocidade

    }else flagHaAtualizacao = 0;
  
    dijkstra(g, verticesMenorTempo, nodeOrigem, nodeDestino);
    grafo_geraMenorCaminho( menorCaminhoAtual, verticesMenorTempo, numbVertice, nodeDestino );

    //=======================ATUALIZAÇÕES==============================
    while (nodeAtual != nodeDestino){

        if(flagHaAtualizacao && tempoGasto >= tempoProxAtualizacao){
            // ATUALIZAR OS DADOS
            
            while(flagHaAtualizacao && tempoGasto >= tempoProxAtualizacao){
                Aresta* aresta = grafo_retornaAresta( g, arestaOrigemAtualizacao, arestaDestinoAtualizacao);
                aresta_atualizaVelocidade(aresta, novaVelocidade);

                if(fgets(linha, 50, inputFile) != NULL ){
                    /*
                    FORMATO ATUALIZAÇÃO:
                    Instante de tempo(s); Aresta(origem;destino); Nova velocidade media naquela aresta (em km/h)
                    "tempo;origem;destino;velocidade"
                    */
                    tempoProxAtualizacao    = atof(strtok(linha,";"));      //tempo
                    arestaOrigemAtualizacao = atoi(strtok(NULL,";"));       //nó de origem
                    arestaDestinoAtualizacao= atoi(strtok(NULL,";"));       //nó de destino
                    novaVelocidade          = atof(strtok(NULL,";"));       //nova Velocidade
                
                }else flagHaAtualizacao = 0;
            }

            // Recalcular rota a partir da localizacao atual apos as atualizacoes
            dijkstra(g, verticesMenorTempo, nodeAtual, nodeDestino);
            grafo_geraMenorCaminho(menorCaminhoAtual, verticesMenorTempo, numbVertice, nodeDestino);

            count = 0;
        }

        Aresta* arestaPercorrida = grafo_retornaAresta(g, nodeAtual, menorCaminhoAtual[count+1]);

        double tempoAresta = aresta_retornaTempoPercurso(arestaPercorrida);
        double distanciaAresta = aresta_retornaDistancia(arestaPercorrida);

        tempoGasto += tempoAresta;
        distanciaPercorrida += distanciaAresta;

        caminhoPercorrido[numVerticesPercorridos] = nodeAtual;
        nodeAtual = menorCaminhoAtual[count+1];
        numVerticesPercorridos++;
        count++;
    }

    caminhoPercorrido[numVerticesPercorridos] = nodeAtual;

    //=======================GERA SAÍDA==============================
    FILE* outputFile = utility_openFile(nameOutputFile,"w");
    grafo_geraOutput(outputFile, numVerticesPercorridos, caminhoPercorrido, distanciaPercorrida, tempoGasto);

    //=======================LIBERA MEMÓRIA===========================
    grafo_free(g);
    free(verticesMenorTempo);
    free(caminhoPercorrido);
    free(menorCaminhoAtual);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

FILE* utility_openFile(char *nameFile, char *action){
    //Abrir o arquivo
    FILE *file = fopen(nameFile, action);

    //Testar o arquivo
    if(file == NULL){
        printf("\n ERRo 001: Função Open_File: Erro Ao abrir arquivo\n");
        exit(0);
    }

    return file; 
}
