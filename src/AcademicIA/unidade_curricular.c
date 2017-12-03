#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unidade_curricular.h"

struct unidade_curricular {
    uint8_t     semestre;       //usar uint8_t -> Semestre < 255;
    uint8_t     codigo[9];      //COM22101 (Padrão: 3 letras da UC, 3 digitos do codigo do curso 2 digitos do semestre da uc.)
    uint8_t*    nome;
    uint8_t     carga_horaria;  //usar uint8_t -> Carga horária < 255;
};

// Cria nova unidade curricular
node_t* uc_node_new(uint8_t semestre, uint8_t* codigo, uint8_t* nome, uint16_t carga_horaria)
{
    node_t* uc_node;
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

    uc_node = node_new(uc);

    return uc_node;
}

// Deleta unidade curricular
void uc_node_delete(node_t* uc_node)
{
    uc_t* uc = node_get_data(uc_node);

    if(uc == NULL){
        perror("ERROR: at uc_delete: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    free(uc->nome);
    free(uc);
    node_delete(uc_node);
    return;
}

//print
void uc_node_print(node_t* uc_node)
{
    uc_t* uc = node_get_data(uc_node);

    if(uc == NULL){
        perror("ERROR: at node_print: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    printf("- uc_node:\n - semestre: %d\n - codigo: %s\n - nome: %s\n - CH:%d\n",
           uc_node_get_semestre(uc_node), uc_node_get_codigo(uc_node),
           uc_node_get_nome(uc_node), uc_node_get_carga_horaria(uc_node));
    return;
}

// GETTERS METHODS
// get semestre
uint8_t uc_node_get_semestre(node_t* uc_node)
{
    uc_t* uc = node_get_data(uc_node);

    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_node_get_semestre: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->semestre;
}

// get codigo
uint8_t* uc_node_get_codigo(node_t* uc_node)
{
    uc_t* uc = node_get_data(uc_node);
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_node_get_codigo: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->codigo;
}

// get nome
uint8_t* uc_node_get_nome(node_t* uc_node){
    uc_t* uc = node_get_data(uc_node);
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_node_get_nome: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->nome;
}

// get carga-horaria
uint8_t uc_node_get_carga_horaria(node_t* uc_node)
{
    uc_t* uc = node_get_data(uc_node);
    if (uc == NULL) {
        fprintf(stderr,"ERROR: at uc_node_get_carga_horaria: ponteiro invalido");
        exit(EXIT_FAILURE);
    }
    return uc->carga_horaria;
}
