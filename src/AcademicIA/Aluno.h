#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED
#include <string.h>
#include <stdint.h>
#include "doubly_linked_list.h"
#include "matriz_curricular.h"
#include "disciplina.h"

typedef struct aluno aluno_t;

// ALUNO_T FUNCTIONS
aluno_t*    aluno_new( uint8_t* nome, uint32_t matricula, uint16_t id_curso, uint8_t id_grade,
                       uint16_t ano_entrada, uint8_t semestre_entrada, uint8_t situacao, dll_t* lista_de_mc);

void        aluno_delete(aluno_t* aluno);

// list functions
void        aluno_discip_new(aluno_t* aluno, uint8_t* codigo_diciplina, uint32_t turma, float conceito,
                             uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao);
//void        aluno_discip_delete(aluno_t* aluno, uint8_t* codigo);
node_t*     aluno_find_mc_node(dll_t* lista_de_mc, uint16_t id_curso, uint8_t id_grade);


// print functions
void        aluno_print(aluno_t* aluno);


//file functions
aluno_t*   aluno_load_from_txt(void);
/**
aluno_t*    aluno_load_from_csv(uint8_t* file);
void        aluno_save_to_csv(aluno_t* aluno, uint8_t* file);
**/
// GETTERS METHODS
uint16_t    aluno_get_id_curso(aluno_t* aluno);
uint8_t     aluno_get_id_grade(aluno_t* aluno);
uint32_t    aluno_get_matricula(aluno_t* aluno);
uint8_t*    aluno_get_nome(aluno_t* aluno);
uint16_t    aluno_get_ano_entrada(aluno_t* aluno);
uint8_t     aluno_get_semestre_entrada(aluno_t* aluno);
uint8_t     aluno_get_situacao(aluno_t* aluno);
uint16_t    aluno_get_horas_cursadas(aluno_t* aluno);
float       aluno_get_ia(aluno_t* aluno);
node_t*     aluno_get_mc_do_curso(aluno_t* aluno);
dll_t*      aluno_get_discip_node_list(aluno_t* aluno);
//EXTRA GETTER FUNCTIONS
uint16_t    aluno_get_discip_node_total(aluno_t* aluno);

#endif // ALUNO_H_INCLUDED
