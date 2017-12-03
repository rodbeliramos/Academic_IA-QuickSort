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
    dll_t*      uc_node_list;
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
    mc->uc_node_list = dll_new();

    return mc;
}

void mc_delete(mc_t* mc){
    if(mc == NULL){
        perror("Error at mc_delete - mc is null");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    node_t* uc_node;
    node_t* next_uc_node;
    uc_node = dll_get_head(mc_get_list(mc));
    for(i=0; i<dll_get_list_size(mc_get_list(mc)); i++){
        next_uc_node = node_get_next(uc_node);
        uc_node_delete(uc_node);
        uc_node = next_uc_node;
    }
    free(mc->nome_curso);
    free(mc);
}

void mc_uc_new(mc_t* mc, node_t* uc_node)
{
    if(mc == NULL || uc_node == NULL){
        perror("Error at mc_uc_new - mc or uc_node is null");
        exit(EXIT_FAILURE);
    }
    dll_add_tail(mc_get_list(mc),uc_node);
    mc->total_horas += uc_node_get_carga_horaria(uc_node);
    return;
}

void mc_uc_delete(mc_t* mc, uint8_t* codigo)
{
    node_t* uc_node;
    if(mc == NULL){
        perror("Error at mc_uc_delete - mc is null");
        exit(EXIT_FAILURE);
    }
    if(codigo == NULL){
        perror("Error at mc_uc_delete - codigo is null");
        exit(EXIT_FAILURE);
    }
    uc_node = mc_find_uc_node(mc, codigo);
    if(uc_node == dll_get_head(mc_get_list(mc))){            //se o nó está na cabeça da lista...
        dll_remove_head(mc_get_list(mc));
    } else if(uc_node == dll_get_tail(mc_get_list(mc))){    //se o nó está na cauda da lista...
        dll_remove_tail(mc_get_list(mc));
    } else{                                                 //se o nó está no meio da lista
        dll_remove_between(mc_get_list(mc), uc_node); //problema aqui
    }

    mc->total_horas -= uc_node_get_carga_horaria(uc_node);
    return;
}

node_t* mc_find_uc_node(mc_t* mc, uint8_t* codigo)
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
    node_t* uc_node = dll_get_head(mc_get_list(mc));

    for(i=0;i<dll_get_list_size(mc_get_list(mc));i++){
        if(strcmp((char*)uc_node_get_codigo(uc_node), (char*)codigo)==0)
        {
            return uc_node;
        }
        uc_node = node_get_next(uc_node);
    }
    return NULL;
}

void mc_print(mc_t* mc){
    if(mc == NULL){
        perror("Error at mc_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i = 0;
    uint8_t j = 0;
    node_t* uc_node = dll_get_head(mc_get_list(mc));

    printf("---\t Matriz Curricular de %s - %d \t---\n",(char*)mc_get_nome_curso(mc),(int)mc_get_id_curso(mc));
    printf("Criacao: %d/%d\t\t\tTotal de horas: %d\n",(int)mc_get_ano_criacao(mc),(int)mc_get_semestre_criacao(mc),
           (int)mc_get_total_horas(mc));
    printf("Unidades Curriculares: %d\n",(int)mc_get_uc_node_total(mc));

    for(i=0;i<dll_get_list_size(mc_get_list(mc));i++){
        if(uc_node_get_semestre(uc_node)!=j){
            j = uc_node_get_semestre(uc_node);
            puts("\n___________________________________________________________________\n");
            printf("- SEMESTRE %d -\n",j);
              puts("___________________________________________________________________\n");
              puts("Codigo\t\tNome\t\t\t\tCarga Horaria\n");
        }
        printf("%s\t%s\t\t%d\n",(char*)uc_node_get_codigo(uc_node),
                                (char*)uc_node_get_nome(uc_node),
                                (int)uc_node_get_carga_horaria(uc_node));
        uc_node = node_get_next(uc_node);
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

uint16_t mc_get_total_horas(mc_t* mc){
    if(mc == NULL){
        perror("ERROR at mc_get_total_horas");
        exit(EXIT_FAILURE);
    }
    return mc->total_horas;
}

dll_t* mc_get_list(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_lista");
        exit(EXIT_FAILURE);
    }
    return mc->uc_node_list;
}

uint16_t mc_get_uc_node_total(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_uc_node_total");
        exit(EXIT_FAILURE);
    }
    return dll_get_list_size(mc_get_list(mc));
}
