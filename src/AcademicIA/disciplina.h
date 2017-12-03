#ifndef DISCIPLINA_H_INCLUDED
#define DISCIPLINA_H_INCLUDED
#include <stdint.h>
#include "matriz_curricular.h"

typedef struct disciplina discip_t;

// LIST FUNCTIONS
discip_t*   discip_new(mc_t* mc, uint8_t* codigo_disciplina, uint16_t turma, float conceito,
                          uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao);
void        discip_delete(discip_t* discip);

void        discip_add_discip_tail(mc_t* mc, uc_t* uc);
void        discip_remove_discip_tail(mc_t* mc);

#endif // DISCIPLINA_H_INCLUDED
