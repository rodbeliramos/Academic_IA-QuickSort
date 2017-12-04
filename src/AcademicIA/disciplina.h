#ifndef DISCIPLINA_H_INCLUDED
#define DISCIPLINA_H_INCLUDED
#include <stdint.h>
#include "matriz_curricular.h"
#include "node.h"

typedef struct disciplina discip_t;

// DISCIP FUNCTIONS
node_t*     discip_node_new(node_t* mc_node, uint8_t* codigo_disciplina, uint32_t turma, float conceito,
                          uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao);
void        discip_node_delete(node_t* discip_node);

void        discip_node_print(node_t* discip_node);

// GETTERS METHODS
node_t*     discip_node_get_uc_node(node_t* discip_node);
uint32_t    discip_node_get_turma(node_t* discip_node);
float       discip_node_get_conceito(node_t* discip_node);
uint8_t     discip_node_get_faltas(node_t* discip_node);
float       discip_node_get_frequencia(node_t* discip_node);
uint8_t     discip_node_get_origem(node_t* discip_node);
uint8_t     discip_node_get_situacao(node_t* discip_node);

#endif // DISCIPLINA_H_INCLUDED
