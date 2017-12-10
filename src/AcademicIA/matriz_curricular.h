#ifndef MATRIZ_CURRICULAR_H_INCLUDED
#define MATRIZ_CURRICULAR_H_INCLUDED

#include <string.h>
#include <stdint.h>
#include "unidade_curricular.h"
#include "doubly_linked_list.h"
#include "node.h"

typedef struct matriz_curricular mc_t;

// MC_T FUNCTIONS
node_t*     mc_node_new( uint8_t* nome_curso, uint16_t id_curso, uint8_t id_grade, uint16_t ano_criacao, uint8_t semestre_criacao);
void        mc_node_delete(node_t* mc_node);

// list functions
void        mc_node_uc_new(node_t* mc_node, node_t* uc_node);
void        mc_node_uc_delete(node_t* mc_node, uint8_t* codigo);
node_t*     mc_node_find_uc_node(node_t* mc_node, uint8_t* codigo);

// print functions
void        mc_node_print(node_t* mc_node);

//file functions
node_t*     mc_node_load_mc(uint8_t* file);
void        mc_node_save_mc(node_t* mc_node, uint8_t* file);
// GETTERS METHODS
uint8_t     mc_node_get_id_grade(node_t* mc_node);
uint8_t*    mc_node_get_nome_curso(node_t* mc_node);
uint16_t    mc_node_get_id_curso(node_t* mc_node);
uint16_t    mc_node_get_ano_criacao(node_t* mc_node);
uint8_t     mc_node_get_semestre_criacao(node_t* mc_node);
uint16_t    mc_node_get_total_horas(node_t* mc_node);
dll_t*      mc_node_get_uc_node_list(node_t* mc_node);
uint16_t    mc_node_get_uc_node_total(node_t* mc_node);

#endif // MATRIZ_CURRICULAR_H_INCLUDED
