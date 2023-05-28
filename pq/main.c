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

    //aresta_exibe(lista_arestas, numbAresta);
    
    Grafo* g = grafo_LeArquivo(inputFile, numbAresta, numbVertice, velocidadeInicial);
    grafo_exibe(g);

    dijkstra(g, nodeOrigem, nodeDestino);    
    
   // aresta_free(lista_arestas);
    grafo_free(g);
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