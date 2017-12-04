#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_curricular.h"
#define DEBUG

struct matriz_curricular {
    uint8_t     id_grade;
    uint8_t*    nome_curso;
    uint16_t    id_curso;
    uint16_t    ano_criacao;
    uint8_t     semestre_criacao;
    uint16_t    total_horas;
    dll_t*      uc_node_list;
};

//LIST FUNCTIONS
mc_t* mc_new( uint8_t* nome_curso, uint16_t id_curso, uint8_t id_grade, uint16_t ano_criacao, uint8_t semestre_criacao)
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
    mc->id_grade = id_grade;
    mc->ano_criacao = ano_criacao;
    mc->semestre_criacao = semestre_criacao;
    mc->total_horas = 0;
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

    fprintf(stdout,"\n---\t Matriz Curricular de %s - %d \t---\n",(char*)mc_get_nome_curso(mc),(int)mc_get_id_curso(mc));
    fprintf(stdout,"Grade: %d\tCriacao: %d/%d\tTotal de horas: %d\n",(int)mc_get_id_grade(mc), (int)mc_get_ano_criacao(mc),(int)mc_get_semestre_criacao(mc),
           (int)mc_get_total_horas(mc));
    fprintf(stdout,"Unidades Curriculares: %d\n",(int)mc_get_uc_node_total(mc));

    for(i=0;i<dll_get_list_size(mc_get_list(mc));i++){
        if(uc_node_get_semestre(uc_node)!=j){
            j = uc_node_get_semestre(uc_node);
            fprintf(stdout,"\n___________________________________________________________________\n");
            fprintf(stdout,"- SEMESTRE %d -\n",j);
            fprintf(stdout,"___________________________________________________________________\n");
            fprintf(stdout,"Codigo\t\tNome\t\t\t\tCarga Horaria\n");
        }
        fprintf(stdout,"%s\t%s\t\t%d\n",(char*)uc_node_get_codigo(uc_node),
                                (char*)uc_node_get_nome(uc_node),
                                (int)uc_node_get_carga_horaria(uc_node));
        uc_node = node_get_next(uc_node);
    }
    return;
}

mc_t* mc_load_mc(uint8_t* file)
{
    int         buffer_size = 100,
                id_curso = 0,
                qty_uc = 0,
                ano_criacao = 0,
                i = 0;

    char        buffer[buffer_size],
                codigo[9],
                nome[50],
                nome_curso[50];

    int         semestre = 0,
                uc_data_qty = 0,
                carga_horaria = 0,
                id_grade = 0,
                semestre_criacao = 0;


    FILE*       fp;
    mc_t*       new_mc;

    fp = fopen((char*)file,"r");
    if(fp == NULL){
        perror("ERROR: at mc_load_mc: fopen");
        exit(EXIT_FAILURE);
    }

    while(fgets((char*)buffer,(int)buffer_size,fp)!=NULL)    /* Conta o numero de temporadas*/
        qty_uc++;
    qty_uc-=2;  //ignora o cabecario
    node_t* uc_node[qty_uc];
    rewind(fp);

    fgets((char*)buffer,(int)buffer_size,fp); // pula o cabecario
    fgets((char*)buffer,(int)buffer_size,fp); // Dados da MC!

    uc_data_qty = 0;
    uc_data_qty = sscanf((char*)buffer,"Curso: %50[^.]. ID: %d. Grade: %d-%d. ID: %d.\n",
                          nome_curso, &id_curso, &ano_criacao, &semestre_criacao, &id_grade); //Erro Aqui! ??? Don't know why!
    #ifdef DEBUG
        printf("\n%s, %d, %d, %d, %d",(char*)nome_curso, id_curso, ano_criacao, semestre_criacao, id_grade);
    #endif
    new_mc = mc_new((uint8_t*)nome_curso, (uint16_t)id_curso, (uint8_t)id_grade, (uint16_t)ano_criacao, (uint8_t)semestre_criacao);

    if(uc_data_qty != 5){
        perror("\nErro na acquisicao dos dados do arquivo!");
        exit(EXIT_FAILURE);
    }
    node_t* uc_node_atual;
    while(fgets((char*)buffer,(int)buffer_size,fp)!=NULL){
        uc_data_qty = 0;

        uc_data_qty = sscanf((char*)buffer,"%d;%9[^;];%50[^;];%d\n",
                             (int*)&semestre, (char*)codigo, (char*)nome, (int*)&carga_horaria);
        #ifdef DEBUG
            printf("\n%d, %s, %s,%i",semestre, codigo, nome, carga_horaria);
        #endif
        if(uc_data_qty != 4){
            perror("\nErro na acquisicao dos dados do arquivo!");
            exit(EXIT_FAILURE);
        }
        uc_node[i] = uc_node_new(semestre, (uint8_t*)codigo, (uint8_t*)nome, carga_horaria);
        uc_node_atual = uc_node[i];
        mc_uc_new(new_mc, uc_node_atual);

        i++;
    }

    fclose(fp);    /* Fecha arquivo*/
    return new_mc;
}

void mc_save_mc(mc_t* mc, uint8_t* file)
{
    FILE*       fp;
    node_t*     uc_node;
    uint16_t    i;

    fp = fopen((char*)file,"w");
    if(fp == NULL){
        perror("ERROR: at mc_save_mc: fopen");
        exit(EXIT_FAILURE);
    }
   // for(i=0; i<)
    uc_node = dll_get_head(mc_get_list(mc));

    fprintf(fp,"Matriz Curricular:\n");
    fprintf(fp,"Curso: %s. ID: %d. Grade: %d-%d. ID: %d.\n", mc_get_nome_curso(mc),mc_get_id_curso(mc),
                mc_get_ano_criacao(mc),mc_get_semestre_criacao(mc), mc_get_id_grade(mc));
    for(i=0;i<dll_get_list_size(mc_get_list(mc));i++){
        fprintf(fp,"%d;%s;%s;%d\n", (int)uc_node_get_semestre(uc_node), (char*)uc_node_get_codigo(uc_node),
                                        (char*)uc_node_get_nome(uc_node),   (int)uc_node_get_carga_horaria(uc_node));
        uc_node = node_get_next(uc_node);
    }

    fclose(fp);    /* Fecha arquivo*/
    return;
}


// GETTERS METHODS
uint8_t mc_get_id_grade(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_id_grade");
        exit(EXIT_FAILURE);
    }
    return mc->id_grade;
}

uint8_t* mc_get_nome_curso(mc_t* mc)
{
    if(mc == NULL){
        perror("ERROR at mc_get_nome_curso");
        exit(EXIT_FAILURE);
    }
    return mc->nome_curso;
}

uint16_t mc_get_id_curso(mc_t* mc)
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
