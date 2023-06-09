#ifndef ARESTA_H
#define ARESTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aresta Aresta;

/**
 *  @brief Inicializa uma aresta, composta dos vértices de origem e destino, da velocidade média e da distância
 * 
 *  @param int vértice de origem
 *  @param int vértice de destino
 *  @param double distância entre os vértices da aresta
 *  @param double velocidade média do caminho 
 */
Aresta* aresta_constroi(int origem, int destino, double distancia, double velocidade);

/** 
 * @brief Retorna o vértice de origem da aresta
 * 
 * @param Aresta* aresta 
 * @return Número inteiro que simboliza o vértice
*/
int aresta_retornaOrigem(Aresta* a);

/** 
 * @brief Retorna o vértice de destino da aresta
 * 
 * @param Aresta* aresta 
 * @return Número inteiro que simboliza o vértice
*/
int aresta_retornaDestino(Aresta* a);

/** 
 * @brief Retorna a distância entre vértices da aresta
 * 
 * @param Aresta* aresta 
 * @return Número racional que simboliza a distância (em metros)
*/
double aresta_retornaDistancia(Aresta* a);


/** 
 * @brief Retorna a velocidade média do caminho entre os vértices
 * 
 * @param Aresta* aresta 
 * @return Número racional que simboliza a velocidade média (em metros/segundo)
*/
double aresta_retornaVelocidade(Aresta* a);


/** 
 * @brief Retorna o tempo de percurso entre os vértices
 * 
 * @param Aresta* aresta 
 * @return Número racional que simboliza o tempo de percurso (em segundos)
*/
double aresta_retornaTempoPercurso(Aresta* a);


/**
 *  @brief Atualiza o valor da velocidade média do caminho entre os vértices
 * 
 *  @param Aresta* aresta 
 *  @param double velocidade média
 */
void aresta_atualizaVelocidade(Aresta* a, double velocidade);


/**
 *  @brief Imprime os componentes da aresta (origem, destino, distância e velocidade média)
 * 
 *  @param Aresta* aresta 
 */
void aresta_imprime(Aresta* a);

#endif


