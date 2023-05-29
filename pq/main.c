#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    grafo_exibe(g);


    int* verticesMenoresCaminhos = calloc(numbVertice+1, sizeof(int));  // Vetor auxiliar para salvar os caminhos calculados por dijkstra
    int* caminhoPercorrido = calloc(numbVertice+1, sizeof(int));        // Vetor para salvar o caminho percorrido
    double distanciaPercorrida = 0;                                     // Distancia percorrida (m)
    double tempoGasto = 0;                                              // Tempo gasto (s)

    dijkstra(g, verticesMenoresCaminhos, nodeOrigem, nodeDestino);

    // grafo_exibeMenorCaminho(verticesMenoresCaminhos, numbVertice, nodeOrigem);

    /*
    FORMATO ATUALIZAÇÃO:
    Instante de tempo(s); Aresta(origem;destino); Nova velocidade media naquela aresta (em km/h)
    "tempo;origem;destino;velocidade"
    */

    fgets(linha, 50, inputFile);  
    int tempo = atoi(strtok(linha,";"));            //tempo
    nodeOrigem  = atoi(strtok(NULL,";"));           //nó de origem
    nodeDestino = atoi(strtok(NULL,";"));           //nó de destino
    int novaVelocidade = atoi(strtok(NULL,";"));    //nova Velocidade

    printf("tempo : %d\n", tempo);
    printf("nodeOrigem : %d\n", nodeOrigem);
    printf("nodeDestino : %d\n", nodeDestino);
    printf("novaVelocidade : %d\n", novaVelocidade);
    
    grafo_free(g);
    free(verticesMenoresCaminhos);
    free(caminhoPercorrido);
    fclose(inputFile);
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