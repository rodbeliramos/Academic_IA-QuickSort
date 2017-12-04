#include <stdio.h>
#include <stdlib.h>
#include "disciplina.h"

struct disciplina {
    node_t*     uc_node;        //ponteiro para a unidade curricular na matriz curricular
    uint32_t    turma;          //int
    float       conceito;       //float
    uint8_t     faltas;         //int
    float       frequencia;     //float
    uint8_t     origem;         //int talvez usar enum
    uint8_t     situacao;       //int talvez usar enum
};

node_t* discip_node_new(node_t* mc_node, uint8_t* codigo_disciplina, uint32_t turma, float conceito,
                          uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao)
{
    if (mc_node == NULL || codigo_disciplina == NULL){
        perror("ERROR: at discip_new() - ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node_t* discip_node;

    discip_t* discip = (discip_t*)malloc(sizeof(discip_t));
    if (discip == NULL){
        perror("ERROR: at discip_node_new() - malloc for uc");
        exit(EXIT_FAILURE);
    }
    discip->uc_node = mc_node_find_uc_node(mc_node, codigo_disciplina);
    discip->turma = turma;
    discip->conceito = conceito;
    discip->faltas = faltas;
    discip->frequencia = frequencia;
    discip->origem = origem;
    discip->situacao = situacao;

    discip_node = node_new(discip);
    return discip_node;
}

void discip_node_delete(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_delete: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    discip_t* discip = node_get_data(discip_node);
    free(discip);
    discip = NULL;
    node_delete(discip_node);
    return;
}

void discip_node_print(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_print: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }

    printf("- discip_node:\n - Semestre: %d\n - Codigo: %s\n - Nome: %s\n - CH:%d\n - Turma: %d\n - Conceito: %f\n - Faltas: %d\n"
           " - Frequecia: %f\n - Origem: %d\n - Situacao: %d\n",
           uc_node_get_semestre(discip_node_get_uc_node(discip_node)), uc_node_get_codigo(discip_node_get_uc_node(discip_node)), uc_node_get_nome(discip_node_get_uc_node(discip_node)),
           uc_node_get_carga_horaria(discip_node_get_uc_node(discip_node)), discip_node_get_turma(discip_node), discip_node_get_conceito(discip_node),
           discip_node_get_faltas(discip_node), discip_node_get_frequencia(discip_node), discip_node_get_origem(discip_node),
           discip_node_get_situacao(discip_node));
    return;
}


// GETTERS METHODS
node_t* discip_node_get_uc_node(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_uc_node: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->uc_node;
}

uint32_t discip_node_get_turma(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_turma: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->turma;
}

float discip_node_get_conceito(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_conceito: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->conceito;
}

uint8_t discip_node_get_faltas(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_faltas: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->faltas;
}

float discip_node_get_frequencia(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_frequencia: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->frequencia;
}

uint8_t discip_node_get_origem(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_origem: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->origem;
}

uint8_t discip_node_get_situacao(node_t* discip_node)
{
    if(discip_node == NULL){
        perror("ERROR: at discip_node_get_origem: ponteiro invalido\n");
        exit(EXIT_FAILURE);
    }
    discip_t* discip = node_get_data(discip_node);
    return discip->situacao;
}
