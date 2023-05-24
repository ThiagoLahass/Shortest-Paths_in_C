#include"aresta.h"

struct aresta
{
    int origem;
    int destino;
    double distancia;
    double velocidade;
};


int aresta_retornaOrigem(Aresta *aresta, int posicao){
    return aresta[posicao].origem;
}
int aresta_retornaDestino(Aresta *aresta, int posicao){
    return aresta[posicao].destino;
}
double aresta_retornaDistancia(Aresta *aresta, int posicao){
    return aresta[posicao].distancia;
}
double aresta_retornaVelocidade(Aresta *aresta, int posicao){
    return aresta[posicao].velocidade;
}


Aresta* aresta_LeArquivo(FILE *file, int quantidadeArestas, double velocidadeInicial){
    
    Aresta* lista_aresta = malloc(quantidadeArestas * sizeof(Aresta));    //lista struct aresta

    char *line = malloc(50*sizeof(char)); //recebe todos os dados de uma linha
    size_t len =50;                       //somente usado na função getline

    for(int i=0; i<quantidadeArestas && ((getline(&line, &len, file)) != -1); i++){
        lista_aresta[i].origem     = atoi(strtok(line, ";")); 
        lista_aresta[i].destino    = atoi(strtok(NULL, ";"));
        lista_aresta[i].distancia  = atof(strtok(NULL, ";"));
        lista_aresta[i].velocidade = velocidadeInicial;
    }

    return lista_aresta;
}


void aresta_exibe(Aresta *aresta, int quantidadeArestas){
    for(int i=0; i<quantidadeArestas; i++){
        printf("aresta[%d]:  origem:%d  dest:%d  ", i, aresta[i].origem, aresta[i].destino);
        printf("Dist:%.2lf  Veloc:%0.2lf\n", aresta[i].distancia, aresta[i].velocidade);
    }
    return;
}


void aresta_free(Aresta *arestas){
    free(arestas);
}

