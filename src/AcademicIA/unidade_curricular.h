#ifndef UNIDADE_CURRICULAR_H_INCLUDED
#define UNIDADE_CURRICULAR_H_INCLUDED

#include <stdint.h>

typedef struct unidade_curricular uc_t;

//NODE FUNCTIONS
uc_t*       uc_new(uint8_t semestre, uint8_t* codigo, uint8_t* nome, uint16_t carga_horaria);
void        uc_delete(uc_t* uc);

void        uc_link(uc_t* source, uc_t* destine);
void        uc_unlink(uc_t* uc);
uc_t*       uc_get_next(uc_t* uc);
uc_t*       uc_get_previous(uc_t* uc);

//GETTERS METHODS
uint8_t     uc_get_semestre(uc_t* uc);
uint8_t*    uc_get_codigo(uc_t* uc);
uint8_t*    uc_get_nome(uc_t* uc);
uint8_t     uc_get_carga_horaria(uc_t* uc);

#endif // UNIDADE_CURRICULAR_H_INCLUDED
