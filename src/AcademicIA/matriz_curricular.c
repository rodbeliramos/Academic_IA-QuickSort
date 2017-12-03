#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_curricular.h"
#define DEBUG

struct matriz_curricular {
    uint8_t*    nome_curso;
    uint8_t     id_curso;
    uint16_t    ano_criacao;
    uint8_t     semestre_criacao;
    uint16_t    total_horas;
    uint16_t    total_uc;
    uc_t*       head;
    uc_t*       tail;

};

//LIST FUNCTIONS
mc_t* mc_new( uint8_t* nome_curso, uint8_t id_curso, uint16_t ano_criacao, uint8_t semestre_criacao)
{
    mc_t* mc = (mc_t*)malloc(sizeof(mc_t));
    if(mc == NULL){
        perror("ERROR: at mc_new");
        exit(EXIT_FAILURE);
    }
    mc->nome_curso = (uint8_t*)malloc(strlen((char*)nome_curso)+1);
    if(mc->nome_curso == NULL){
        perror("ERROR: at mc_new");
        exit(EXIT_FAILURE);
    }

    strncpy((char*)mc->nome_curso, (char*)nome_curso,strlen((char*)nome_curso)+1);

    mc->id_curso = id_curso;
    mc->ano_criacao = ano_criacao;
    mc->semestre_criacao = semestre_criacao;
    mc->head = NULL;
    mc->tail = NULL;
    mc->total_uc = 0;
    return mc;
}

void mc_delete(mc_t* mc){
    uint16_t i;
    uc_t* uc;
    uc_t* next_uc;
    uc = mc_get_head(mc);
    for(i=0; i<mc_get_total_uc(mc); i++){
        next_uc = uc_get_next(uc);
        uc_delete(uc);
        uc = next_uc;
    }
    free(mc->nome_curso);
    free(mc);
}

void mc_add_uc_head(mc_t* mc, uc_t* uc)
{
    if(mc == NULL || uc == NULL){
        perror("ERROR: at mc_add_head");
        exit(EXIT_FAILURE);
    }
    if(mc_is_empty(mc)){
        mc->head = uc;
        mc->tail = uc;
        mc->total_uc++;
        uc_unlink(uc);
    } else {
        uc_unlink(uc);
        uc_link(uc,mc_get_head(mc));
        mc->head = uc;
        mc->total_uc++;
    }
    return;
}

void mc_remove_uc_head(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR: at mc_remove_head");
        exit(EXIT_FAILURE);
    }
    uc_t* uc = mc_get_head(mc);
    uc_t* next = uc_get_next(uc);
    uc_unlink(uc);
    mc->head = next;
    mc->total_uc--;

    return;
}

void mc_add_uc_tail(mc_t* mc, uc_t* uc)
{
    if(mc == NULL || uc == NULL){
        perror("ERROR at mc_add_tail");
        exit(EXIT_FAILURE);
    }
    if(mc_is_empty(mc)){
        mc->head = uc;
        mc->tail = uc;
        mc->total_uc++;
        uc_unlink(uc);
    } else {
        uc_unlink(uc);
        uc_link(mc_get_tail(mc), uc);
        mc->tail = uc;
        mc->total_uc++;
    }
    return;
}

void mc_remove_uc_tail(mc_t* mc)
{
    if(mc == NULL){
        perror("Error at mc_remove_head");
        exit(EXIT_FAILURE);
    }
    uc_t* uc = mc_get_tail(mc);
    uc_t* previous = uc_get_previous(uc);
    uc_unlink(uc);
    mc->tail = previous;
    mc->total_uc--;

    return;
}

uc_t* mc_find_uc(mc_t* mc, uint8_t* codigo)
{
    if(mc == NULL){
        perror("Error at mc_find_uc - mc is null");
        exit(EXIT_FAILURE);
    }
    if(codigo == NULL){
        perror("Error at mc_find_uc - codigo is null");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    uc_t* uc = mc_get_head(mc);

    for(i=0;i<mc_get_total_uc(mc);i++){
        if(strcmp((char*)uc_get_codigo(uc), (char*)codigo)){
            return uc;
        }
        uc = uc_get_next(uc);
    }
    return NULL;
}

uint8_t mc_is_empty(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_is_empty");
        exit(EXIT_FAILURE);
    }
    if(mc_get_total_uc(mc) == 0)
        return 1;
    else
        return 0;
}

void mc_print(mc_t* mc){
    if(mc == NULL){
        perror("Error at mc_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i = 0;
    uint8_t j = 0;
    uc_t* uc = mc_get_head(mc);

    printf("---\t Matriz Curricular de %s - %d \t---\n",(char*)mc_get_nome_curso(mc),(int)mc_get_id_curso(mc));
    printf("Criacao: %d/%d\t\t\tTotal de horas: %d\n",(int)mc_get_ano_criacao(mc),(int)mc_get_semestre_criacao(mc),
           (int)mc_get_total_horas(mc));

    for(i=0;i<mc_get_total_uc(mc);i++){
        if(uc_get_semestre(uc)!=j){
            j = uc_get_semestre(uc);
            puts("\n___________________________________________________________________\n");
            printf("- SEMESTRE %d -\n",j);
              puts("___________________________________________________________________\n");
              puts("Codigo\t\tNome\t\t\t\tCarga Horaria\n");
        }
        printf("%s\t%s\t\t%d\n",(char*)uc_get_codigo(uc),(char*)uc_get_nome(uc),(int)uc_get_carga_horaria(uc));
        uc = uc_get_next(uc);
    }
    return;
}

// GETTERS METHODS

uint8_t* mc_get_nome_curso(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_nome_curso");
        exit(EXIT_FAILURE);
    }
    return mc->nome_curso;
}

uint8_t mc_get_id_curso(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_id_curso");
        exit(EXIT_FAILURE);
    }
    return mc->id_curso;
}

uint16_t mc_get_ano_criacao(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_ano_criacao");
        exit(EXIT_FAILURE);
    }
    return mc->ano_criacao;
}

uint8_t mc_get_semestre_criacao(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_semestre_criacao");
        exit(EXIT_FAILURE);
    }
    return mc->semestre_criacao;
}

uc_t* mc_get_head(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR: at mc_get_head");
        exit(EXIT_FAILURE);
    }
    return mc->head;
}

uc_t* mc_get_tail(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_tail");
        exit(EXIT_FAILURE);
    }
    return mc->tail;
}

uint16_t mc_get_total_uc(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_total_uc");
        exit(EXIT_FAILURE);
    }
    return mc->total_uc;
}

uint16_t mc_get_total_horas(mc_t* mc){
    if(mc == NULL){
        perror("ERROR at mc_get_total_horas");
        exit(EXIT_FAILURE);
    }
    return mc->total_horas;
}
