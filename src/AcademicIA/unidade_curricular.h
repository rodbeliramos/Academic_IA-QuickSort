#ifndef UNIDADE_CURRICULAR_H_INCLUDED
#define UNIDADE_CURRICULAR_H_INCLUDED

#include <stdint.h>
#include "node.h"


typedef struct unidade_curricular uc_t;

//UC_T FUNCTIONS
node_t*     uc_node_new(uint8_t semestre, uint8_t* codigo, uint8_t* nome, uint16_t carga_horaria);
void        uc_node_delete(node_t* uc_node);

void        uc_node_print(node_t* uc_node);

//GETTERS METHODS
uint8_t     uc_node_get_semestre(node_t* uc_node);
uint8_t*    uc_node_get_codigo(node_t* uc_node);
uint8_t*    uc_node_get_nome(node_t* uc_node);
uint8_t     uc_node_get_carga_horaria(node_t* uc_node);

#endif // UNIDADE_CURRICULAR_H_INCLUDED
