#include"aresta.h"

struct aresta{
    int origem;
    int destino;
    double distancia;
    double velocidade;
};

Aresta* aresta_constroi(int origem, int destino, double distancia, double velocidade){
    Aresta* nova = malloc(sizeof(Aresta));

    nova->origem = origem;
    nova->destino = destino;
    nova->distancia = distancia;
    nova->velocidade = velocidade;

    return nova;
}

int aresta_retornaOrigem(Aresta* a){
    return a->origem;
}

int aresta_retornaDestino(Aresta* a){
    return a->destino;
}

double aresta_retornaDistancia(Aresta* a){
    return a->distancia;
}

double aresta_retornaVelocidade(Aresta* a){
    return a->velocidade;
}

double aresta_retornaTempoPercurso(Aresta* a){
    double velocidade_m_s = a->velocidade/3.6;
    return a->distancia/velocidade_m_s;
}

void aresta_atualizaVelocidade(Aresta*a, double velocidade){
    a->velocidade = velocidade;
}

void aresta_imprime(Aresta* a){
    printf("<(%d,%d) d = %f, v = %f > ", a->origem, a->destino, a->distancia, a->velocidade);
}
