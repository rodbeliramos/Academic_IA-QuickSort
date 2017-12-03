#include <stdio.h>
#include <stdlib.h>
#include "disciplina.h"

struct disciplina {
    uc_t*       uc;             //ponteiro para a unidade curricular na matriz curricular (possibilita retornar os valores abaixo
                                //sem ocupar mais memória.
    //uint8_t   codigo[9];      //char[]
    //uint16_t  semestre;       //int
    //uint8_t*  nome;           //char[]
    //uint16_t  carga_horaria;  //int
    uint16_t    turma;          //int
    float       conceito;       //float
    uint8_t     faltas;         //int
    float       frequencia;     //float
    uint8_t     origem;         //int talvez usar enum
    uint8_t     situacao;       //int talvez usar enum
    discip_t*   previous;
    discip_t*   next;
};
/*
discip_t* discip_new(mc_t* mc, uint8_t* codigo_disciplina, uint16_t turma, float conceito,
                          uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao)
{
    if (mc == NULL || codigo_disciplina == NULL){
        perror("ERROR: at discip_new() - ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    discip_t* discip = (discip_t*)malloc(sizeof(discip_t));
    if(discip == NULL){
        perror("ERROR: at discip_new");
        exit(EXIT_FAILURE);
    }
    discip->uc = mc_find_uc(mc, codigo_disciplina);
    discip->turma = turma;
    discip->conceito = conceito;
    discip->faltas = faltas;
    discip->frequencia = frequencia;
    discip->origem = origem;
    discip->situacao = situacao;

    return discip;
}
*/
