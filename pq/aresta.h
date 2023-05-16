#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct aresta Aresta;

/* 
 * Função que retorna atributo origem da struct 
 * Pré-condição: ponteiro para lista de structs aresta, válida
 * Pós-condição: nenhuma
 * Input:  ponteiro para lista de structs Aresta, posição da struct
 * Output: atributo origem da struct
 */
int aresta_retornaOrigem(Aresta *aresta, int posicao);
/* 
 * Função que retorna atributo destino da struct 
 * Pré-condição: ponteiro para lista de structs aresta, válida
 * Pós-condição: nenhuma
 * Input:  ponteiro para lista de structs Aresta, posição da struct
 * Output: atributo destino da struct
 */
int aresta_retornaDestino(Aresta *aresta, int posicao);

/* 
 * Função que retorna atributo Distância da struct 
 * Pré-condição: ponteiro para lista de structs aresta, válida
 * Pós-condição: nenhuma
 * Input:  ponteiro para lista de structs Aresta, posição da struct
 * Output: atributo Distância da struct
 */
double aresta_retornaDistancia(Aresta *aresta, int posicao);

/* 
 * Função que retorna atributo Velocidade da struct 
 * Pré-condição: ponteiro para lista de structs aresta, válida
 * Pós-condição: nenhuma
 * Input:  ponteiro para lista de structs Aresta, posição da struct
 * Output: atributo Velocidade da struct
 */
double aresta_retornaVelocidade(Aresta *aresta, int posicao);



/* 
 * Função que lê arquivo e retorna lista de structs Aresta preenchida 
 * Pré-condição: ponteiro para arquivo válido
 * Pós-condição: lista de structs criada e preenchida
 * Input: ponteiro para arquivo, quantidade de Aresta, velocidade inicial da aresta
 * Output: lista de structs Aresta preenchida
 */
Aresta* aresta_LeArquivo(FILE *file, int quantidadeArestas, double velocidadeInicial);

/* 
 * Função que exibe lista de structs Aresta 
 * Pré-condição: lista de structs Aresta, válida
 * Pós-condição: nenhuma
 * Input: lista de structs Aresta preenchida, quantidade de Arestas
 * Output: nenhum
 */
void aresta_exibe(Aresta *aresta, int quantidadeArestas);

/* 
 * Função que libera lista de structs Aresta 
 * Pré-condição: lista de structs Aresta válida
 * Pós-condição: lista de structs Aresta liberada da memória
 * Input: lista de structs Aresta preenchida
 * Output: nenhum
 */
void aresta_free(Aresta *arestas);



