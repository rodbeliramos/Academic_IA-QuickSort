#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

struct aluno {
    uint16_t    id_curso;
    uint8_t     id_grade;
    uint32_t    matricula;
    uint8_t*    nome;
    uint16_t    ano_entrada;
    uint8_t     semestre_entrada;
    uint8_t     situacao;
    uint16_t    total_horas_cursadas;
    float       porcentagem_cursada;
    float       ia;
    mc_t*       matriz_do_curso;
    dll_t*      discip_node_list;
};
/**
// ALUNO_T FUNCTIONS
aluno_t* aluno_new( uint16_t id_curso, uint8_t id_grade, uint32_t matricula, uint8_t* nome, uint16_t ano_entrada, uint8_t semestre_entrada, uint8_t situacao)
{

}

void aluno_delete(aluno_t* aluno)
{

}

// list functions
void aluno_discip_new(aluno_t* aluno, node_t* discip_node)
{

}

void aluno_discip_delete(aluno_t* aluno, uint8_t* codigo)
{

}

node_t* aluno_find_discip_node(aluno_t* aluno, uint8_t* codigo)
{

}

// print functions
void aluno_print(aluno_t* aluno)
{

}

//file functions
aluno_t* aluno_load_aluno(uint8_t* file)
{

}

void aluno_save_aluno(aluno_t* aluno, uint8_t* file)
{

}

// GETTERS METHODS
uint32_t aluno_get_matricula(aluno_t* aluno)
{

}

uint8_t* aluno_get_nome(aluno_t* aluno)
{

}

uint16_t aluno_get_ano_entrada(aluno_t* aluno)
{

}

uint8_t aluno_get_semestre_entrada(aluno_t* aluno)
{

}

uint8_t aluno_get_situacao(aluno_t* aluno)
{

}

uint16_t aluno_get_total_horas_cursadas(aluno_t* aluno)
{

}

float aluno_get_porcentagem_cursada(aluno_t* aluno)
{

}

float aluno_get_ia(aluno_t* aluno)
{

}

mc_t* aluno_get_matriz_do_curso(aluno_t* aluno)
{

}

dll_t* aluno_get_discip_node_list(aluno_t* aluno)
{

}
**/
