#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "PQ.h"
#include "aresta.h"
#include "grafo.h"

FILE* utility_openFile(char *nameFile, char *action);

void conversor_SEGUNDOS_para_HH_M_SSfff( double segundos, int* HH, int* MM, double* SSfff );

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

    // grafo_exibe(g);


    int* verticesMenoresCaminhos = calloc(numbVertice+1, sizeof(int));      // Vetor auxiliar para salvar os caminhos calculados por dijkstra
    int* caminhoPercorrido = calloc(numbVertice, sizeof(int));              // Vetor para salvar o caminho percorrido
    int* vetorAuxCaminhoAPercorrer = calloc(numbVertice, sizeof(int));      // Vetor para salvar o caminho que deveria ser percorrido se nao houvesse mais atualizacoes
    double distanciaPercorrida = 0;                                         // Distancia percorrida (m)
    double tempoGasto = 0;                                                  // Tempo gasto (s)
    
    double tempoProxAtualizacao = INFINITY;                                 // Tempo da proxima atualizacao
    int flagHaAtualizacao = 1;
    int arestaOrigemAtualizacao = 0;
    int arestaDestinoAtualizacao = 0;
    double novaVelocidade = 0;

    int nodeAtual = nodeOrigem;         // Node atual, começando pela origem
    int numVerticesPercorridos = 0;     // Numero de vertices percorridos no total
    int count = 0;                      // Numero de vertices percorridos do caminho definido como atual


    if( fgets(linha, 50, inputFile) != NULL ){
        /*
        FORMATO ATUALIZAÇÃO:
        Instante de tempo(s); Aresta(origem;destino); Nova velocidade media naquela aresta (em km/h)
        "tempo;origem;destino;velocidade"
        */

        tempoProxAtualizacao    = atof(strtok(linha,";"));      //tempo
        arestaOrigemAtualizacao = atoi(strtok(NULL,";"));       //nó de origem
        arestaDestinoAtualizacao= atoi(strtok(NULL,";"));       //nó de destino
        novaVelocidade          = atof(strtok(NULL,";"));       //nova Velocidade

        printf("\ntempo : %f\n", tempoProxAtualizacao);
        printf("arestaOrigemAtualizacao : %d\n", arestaOrigemAtualizacao);
        printf("arestaDestinoAtualizacao : %d\n", arestaDestinoAtualizacao);
        printf("novaVelocidade : %f\n\n", novaVelocidade);
    }
    else{
        flagHaAtualizacao = 0;
    }

    dijkstra(g, verticesMenoresCaminhos, nodeOrigem, nodeDestino);
    grafo_geraMenorCaminho( vetorAuxCaminhoAPercorrer, verticesMenoresCaminhos, numbVertice, nodeDestino );
    grafo_exibeMenorCaminho( vetorAuxCaminhoAPercorrer, numbVertice);

    while ( nodeAtual != nodeDestino ){

        if( flagHaAtualizacao && tempoGasto >= tempoProxAtualizacao ){
            count = 0;

            // ATUALIZAR OS DADOS
            printf("\nATUALIZANDO DADOS...\n");
            Aresta* aresta = grafo_retornaAresta( g, arestaOrigemAtualizacao, arestaDestinoAtualizacao);
            aresta_atualizaVelocidade(aresta, novaVelocidade);

            grafo_exibe(g);

            // Recaucular rota a partir da localizacao
            dijkstra(g, verticesMenoresCaminhos, nodeAtual, nodeDestino);
            grafo_geraMenorCaminho( vetorAuxCaminhoAPercorrer, verticesMenoresCaminhos, numbVertice, nodeDestino );
            grafo_exibeMenorCaminho( vetorAuxCaminhoAPercorrer, numbVertice);

            if( fgets(linha, 50, inputFile) != NULL ){
                /*
                FORMATO ATUALIZAÇÃO:
                Instante de tempo(s); Aresta(origem;destino); Nova velocidade media naquela aresta (em km/h)
                "tempo;origem;destino;velocidade"
                */

                tempoProxAtualizacao    = atof(strtok(linha,";"));      //tempo
                arestaOrigemAtualizacao = atoi(strtok(NULL,";"));       //nó de origem
                arestaDestinoAtualizacao= atoi(strtok(NULL,";"));       //nó de destino
                novaVelocidade          = atof(strtok(NULL,";"));       //nova Velocidade

                printf("\ntempo : %f\n", tempoProxAtualizacao);
                printf("arestaOrigemAtualizacao : %d\n", arestaOrigemAtualizacao);
                printf("arestaDestinoAtualizacao : %d\n", arestaDestinoAtualizacao);
                printf("novaVelocidade : %f\n\n", novaVelocidade);
            }
            else{
                flagHaAtualizacao = 0;
            }
        }

        printf("numVerticesPercorridos: %d\n", numVerticesPercorridos);
        printf("count: %d\n", count);

        Aresta* arestaPercorrida = grafo_retornaAresta( g, nodeAtual, vetorAuxCaminhoAPercorrer[count+1]);
        aresta_imprime(arestaPercorrida);

        double tempoAresta = aresta_retornaTempoPercurso(arestaPercorrida);
        double distanciaAresta = aresta_retornaDistancia(arestaPercorrida);
        printf("\nTempo de percurso: %f\n", tempoAresta);
        printf("Distancia de percurso: %f\n\n", distanciaAresta);

        tempoGasto += tempoAresta;
        distanciaPercorrida += distanciaAresta;

        printf("\nTempo de percurso total atual: %f\n", tempoGasto);
        printf("Distancia de percurso total atual: %f\n\n", distanciaPercorrida);

        caminhoPercorrido[numVerticesPercorridos] = nodeAtual;
        nodeAtual = vetorAuxCaminhoAPercorrer[count+1];
        numVerticesPercorridos++;
        count++;
    }

    caminhoPercorrido[numVerticesPercorridos] = nodeAtual;


    //=======================SAIDA===========================

    FILE* outputFile = utility_openFile(nameOutputFile,"w");

    //Caminho Percorrido
    for(int i = 0; i <= numVerticesPercorridos; i++){
        fprintf(outputFile, "%d", caminhoPercorrido[i]);
        if( i < numVerticesPercorridos ){
            fprintf(outputFile,";");
        }
    }
    fprintf(outputFile, "\n");

    //Distancia em km
    fprintf(outputFile, "%f\n", distanciaPercorrida/1000);

    //Tempo no formato HH:MM:SS.fff, onde “.fff” representam os milisseegundos.
    int horas, minutos;
    double segundos;
    conversor_SEGUNDOS_para_HH_M_SSfff(tempoGasto, &horas, &minutos, &segundos);
    fprintf(outputFile, "%d:%d:%f\n", horas, minutos, segundos);

    //=========================FIM SAIDA========================


    grafo_free(g);
    free(verticesMenoresCaminhos);
    free(caminhoPercorrido);
    free(vetorAuxCaminhoAPercorrer);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}


FILE* utility_openFile(char *nameFile, char *action){
    //Abrir o arquivo/
    FILE *file;
    file = fopen(nameFile, action);

    //Testar Arquivo/
    if(file == NULL){
        printf("\n ERRo 001: Função Open_File: Erro Ao abrir arquivo\n");
        exit(0);
    }
    return file; 
}

void conversor_SEGUNDOS_para_HH_M_SSfff( double segundos, int* HH, int* MM, double* SSfff ){
    *HH = segundos/3600;
    segundos -= (*HH)*3600;
    *MM = segundos/60;
    segundos -= (*MM)*60;
    *SSfff = segundos;
}