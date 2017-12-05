#include <stdio.h>
#include <stdlib.h>
#include "matriz_curricular.h"
//#define DEBUG

struct matriz_curricular {
    uint16_t    id_curso;
    uint8_t     id_grade;
    uint8_t*    nome_curso;
    uint16_t    ano_criacao;
    uint8_t     semestre_criacao;
    uint16_t    total_horas;
    dll_t*      uc_node_list;
};

//LIST FUNCTIONS
node_t* mc_node_new( uint8_t* nome_curso, uint16_t id_curso, uint8_t id_grade, uint16_t ano_criacao, uint8_t semestre_criacao)
{
    node_t* mc_node;
    mc_t* mc = (mc_t*)malloc(sizeof(mc_t));
    if(mc == NULL){
        perror("ERROR: at mc_node_new");
        exit(EXIT_FAILURE);
    }
    mc->nome_curso = (uint8_t*)malloc(strlen((char*)nome_curso)+1);
    if(mc->nome_curso == NULL){
        perror("ERROR: at mc_node_new");
        exit(EXIT_FAILURE);
    }

    strncpy((char*)mc->nome_curso, (char*)nome_curso,strlen((char*)nome_curso)+1);

    mc->id_curso = id_curso;
    mc->id_grade = id_grade;
    mc->ano_criacao = ano_criacao;
    mc->semestre_criacao = semestre_criacao;
    mc->total_horas = 0;
    mc->uc_node_list = dll_new();

    mc_node = node_new(mc);

    return mc_node;
}

void mc_node_delete(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("Error at mc_node_delete - mc_node is null");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);

    uint16_t i;
    node_t* uc_node;
    node_t* next_uc_node;
    uc_node = dll_get_head(mc_node_get_list(mc_node));
    for(i=0; i<dll_get_list_size(mc_node_get_list(mc_node)); i++){
        next_uc_node = node_get_next(uc_node);
        uc_node_delete(uc_node);
        uc_node = next_uc_node;
    }
    free(mc->nome_curso);
    dll_delete(mc->uc_node_list);
    mc->uc_node_list = NULL;
    free(mc);
    mc = NULL;
    node_delete(mc_node);
    return;
}

void mc_node_uc_new(node_t* mc_node, node_t* uc_node)
{
    if(mc_node == NULL || uc_node == NULL){
        perror("Error at mc_node_uc_new - mc_node or uc_node is null");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);

    dll_add_tail(mc_node_get_list(mc_node),uc_node);
    mc->total_horas += uc_node_get_carga_horaria(uc_node);
    return;
}

void mc_node_uc_delete(node_t* mc_node, uint8_t* codigo)
{
    if(mc_node == NULL){
        perror("Error at mc_node_uc_delete - mc_node is null");
        exit(EXIT_FAILURE);
    }
    if(codigo == NULL){
        perror("Error at mc_node_uc_delete - codigo is null");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    node_t* uc_node;

    uc_node = mc_node_find_uc_node(mc_node, codigo);
    if(uc_node == dll_get_head(mc_node_get_list(mc_node))){            //se o nó está na cabeça da lista...
        dll_remove_head(mc_node_get_list(mc_node));
    } else if(uc_node == dll_get_tail(mc_node_get_list(mc_node))){    //se o nó está na cauda da lista...
        dll_remove_tail(mc_node_get_list(mc_node));
    } else{                                                 //se o nó está no meio da lista
        dll_remove_between(mc_node_get_list(mc_node), uc_node); //problema aqui
    }

    mc->total_horas -= uc_node_get_carga_horaria(uc_node);
    return;
}

node_t* mc_node_find_uc_node(node_t* mc_node, uint8_t* codigo)
{
    if(mc_node == NULL){
        perror("Error at mc_find_uc_node - mc_node is null");
        exit(EXIT_FAILURE);
    }
    if(codigo == NULL){
        perror("Error at mc_find_uc_node - codigo is null");
        exit(EXIT_FAILURE);
    }

    uint16_t i;
    node_t* uc_node = dll_get_head(mc_node_get_list(mc_node));

    for(i=0;i<dll_get_list_size(mc_node_get_list(mc_node));i++){
        if(strcmp((char*)uc_node_get_codigo(uc_node), (char*)codigo)==0)
        {
            return uc_node;
        }
        uc_node = node_get_next(uc_node);
    }
    return NULL;
}

void mc_node_print(node_t* mc_node){
    if(mc_node == NULL){
        perror("Error at mc_node_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i = 0;
    uint8_t j = 0;
    node_t* uc_node = dll_get_head(mc_node_get_list(mc_node));

    fprintf(stdout,"\n-----------     Matriz Curricular de %s - %d     -----------\n\n",
                                                                    (char*)mc_node_get_nome_curso(mc_node),
                                                                    (int)mc_node_get_id_curso(mc_node));

    fprintf(stdout,"Grade:\t\t%d\nCriacao:\t%d/%d\nTotal de horas:\t%d\n\n",(int)mc_node_get_id_grade(mc_node),
                                                                     (int)mc_node_get_ano_criacao(mc_node),
                                                                     (int)mc_node_get_semestre_criacao(mc_node),
                                                                     (int)mc_node_get_total_horas(mc_node));
    fprintf(stdout,"Unidades Curriculares:\t%d\n",(int)mc_node_get_uc_node_total(mc_node));

    for(i=0;i<mc_node_get_uc_node_total(mc_node);i++){
        if(uc_node_get_semestre(uc_node)!=j){
            j = uc_node_get_semestre(uc_node);
            fprintf(stdout,"\n_______________________________________________________________________________\n");
            fprintf(stdout,"- SEMESTRE %d -\n",j);
            fprintf(stdout,"_______________________________________________________________________________\n");
            fprintf(stdout," Codigo\t\tNome\t\t\t\t\tCarga Horaria\n");
        }
        fprintf(stdout," %8s\t%-25s\t\t\t%3d\n",(char*)uc_node_get_codigo(uc_node),
                                        (char*)uc_node_get_nome(uc_node),
                                        (int)uc_node_get_carga_horaria(uc_node));
        uc_node = node_get_next(uc_node);
    }
    fprintf(stdout,"\n-------------------------------------------------------------------------------\n");

    return;
}

node_t* mc_node_load_mc(uint8_t* file)
{
    //Não consegui usar o uint... a funcao sscanf se perde.
    uint32_t         buffer_size = 100,
                id_curso = 0,
                qty_uc = 0,
                ano_criacao = 0,
                i = 0;

    uint8_t        buffer[buffer_size],
                codigo[9],
                nome[50],
                nome_curso[50];

    uint32_t     semestre = 0,
                uc_data_qty = 0,
                carga_horaria = 0,
                id_grade = 0,
                semestre_criacao = 0;


    FILE*       fp;
    node_t*     new_mc_node;
    node_t*     uc_node_atual;

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
                         (char*)nome_curso, (int*)&id_curso, (int*)&ano_criacao, (int*)&semestre_criacao, (int*)&id_grade);
    #ifdef DEBUG
        printf("\n%s, %d, %d, %d, %d",(char*)nome_curso, id_curso, ano_criacao, semestre_criacao, id_grade);
    #endif
    new_mc_node = mc_node_new((uint8_t*)nome_curso, (uint16_t)id_curso, (uint8_t)id_grade, (uint16_t)ano_criacao, (uint8_t)semestre_criacao);

    if(uc_data_qty != 5){
        perror("\nErro na acquisicao dos dados do arquivo!");
        exit(EXIT_FAILURE);
    }

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
        mc_node_uc_new(new_mc_node, uc_node_atual);

        i++;
    }

    fclose(fp);    /* Fecha arquivo*/
    return new_mc_node;
}

void mc_node_save_mc(node_t* mc_node, uint8_t* file)
{
    if(mc_node == NULL){
        perror("Error at mc_node_save_mc");
        exit(EXIT_FAILURE);
    }

    FILE*       fp;
    node_t*     uc_node;
    uint16_t    i;

    fp = fopen((char*)file,"w");
    if(fp == NULL){
        perror("ERROR: at mc_save_mc: fopen");
        exit(EXIT_FAILURE);
    }
   // for(i=0; i<)
    uc_node = dll_get_head(mc_node_get_list(mc_node));

    fprintf(fp,"Matriz Curricular:\n");
    fprintf(fp,"Curso: %s. ID: %d. Grade: %d-%d. ID: %d.\n", mc_node_get_nome_curso(mc_node),mc_node_get_id_curso(mc_node),
                mc_node_get_ano_criacao(mc_node),mc_node_get_semestre_criacao(mc_node), mc_node_get_id_grade(mc_node));

    for(i=0;i<mc_node_get_uc_node_total(mc_node);i++){
        fprintf(fp,"%d;%s;%s;%d\n", (int)uc_node_get_semestre(uc_node), (char*)uc_node_get_codigo(uc_node),
                                        (char*)uc_node_get_nome(uc_node),   (int)uc_node_get_carga_horaria(uc_node));
        uc_node = node_get_next(uc_node);
    }

    fclose(fp);    /* Fecha arquivo*/
    return;
}


// GETTERS METHODS
uint8_t mc_node_get_id_grade(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_id_grade");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->id_grade;
}

uint8_t* mc_node_get_nome_curso(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_nome_curso");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->nome_curso;
}

uint16_t mc_node_get_id_curso(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_id_curso");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->id_curso;
}

uint16_t mc_node_get_ano_criacao(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_ano_criacao");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->ano_criacao;
}

uint8_t mc_node_get_semestre_criacao(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_semestre_criacao");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->semestre_criacao;
}

uint16_t mc_node_get_total_horas(node_t* mc_node){
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_total_horas");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->total_horas;
}

dll_t* mc_node_get_list(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_lista");
        exit(EXIT_FAILURE);
    }
    mc_t* mc = node_get_data(mc_node);
    return mc->uc_node_list;
}

uint16_t mc_node_get_uc_node_total(node_t* mc_node)
{
    if(mc_node == NULL){
        perror("ERROR at mc_node_get_uc_node_total");
        exit(EXIT_FAILURE);
    }
    return dll_get_list_size(mc_node_get_list(mc_node));
}
