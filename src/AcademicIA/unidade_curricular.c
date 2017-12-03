#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidade_curricular.h"

struct unidade_curricular {
    uint8_t semestre;       //usar uint8_t -> Semestre < 255;
    uint8_t codigo[9];      //COM22101 (Padrão: 3 letras da UC, 3 digitos do codigo do curso 2 digitos do semestre da uc.)
    uint8_t* nome;
    uint8_t carga_horaria;  //usar uint8_t -> Carga horária < 255;
    void* previous;
    void* next;
};

// NODE FUNCTIONS
// Cria nova unidade curricular
uc_t* uc_new(uint8_t semestre, uint8_t* codigo, uint8_t* nome, uint16_t carga_horaria)
{
    uc_t* uc = malloc(sizeof(uc_t));

    if (uc == NULL){
        perror("ERROR: at uc_new() - malloc for uc");
        exit(EXIT_FAILURE);
    }
    uc->nome = (uint8_t*)malloc(strlen((char*)nome)+1);
    if(uc->nome == NULL){
        perror("ERROR: at uc_new() - malloc for name");
        exit(EXIT_FAILURE);
    }

    uc->semestre = semestre;
    strcpy((char*)uc->codigo, (char*)codigo);
    strncpy((char*)uc->nome, (char*)nome,strlen((char*)nome)+1);
    uc->carga_horaria = carga_horaria;
    uc->previous = NULL;
    uc->next = NULL;

    return uc;
}

// Deleta unidade curricular
void uc_delete(uc_t* uc)
{
    free(uc->nome);
    free(uc);
    return;
}

// list-linker
void uc_link(uc_t* source, uc_t* destine)
{
    if(source == NULL || destine == NULL){
        perror("ERROR: at uc_link: ponteiros invalidos\n");
        exit(EXIT_FAILURE);
    }
    source->next = destine;
    destine->previous = source;
}

// list-unlinker
void uc_unlink(uc_t* uc)
{
    if(uc == NULL){
        perror("ERROR: at uc_unlink: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    uc->previous = NULL;
    uc->next = NULL;
}

// get next
uc_t* uc_get_next(uc_t* uc)
{
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_next: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->next;
}

// get previous
uc_t* uc_get_previous(uc_t* uc)
{
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_previous: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->previous;
}

// GETTERS METHODS
// get semestre
uint8_t uc_get_semestre(uc_t* uc)
{
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_semestre: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->semestre;
}

// get codigo
uint8_t* uc_get_codigo(uc_t* uc)
{
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_codigo: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->codigo;
}

// get nome
uint8_t* uc_get_nome(uc_t* uc){
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_nome: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->nome;
}

// get carga-horaria
uint8_t uc_get_carga_horaria(uc_t* uc)
{
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_get_carga_horaria: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->carga_horaria;
}
