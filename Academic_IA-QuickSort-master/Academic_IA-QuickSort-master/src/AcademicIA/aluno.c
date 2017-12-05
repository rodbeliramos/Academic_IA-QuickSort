#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

struct aluno {
    uint8_t*    nome;
    uint32_t    matricula;
    uint16_t    id_curso;
    uint8_t     id_grade;
    uint16_t    ano_entrada;
    uint8_t     semestre_entrada;
    uint8_t     situacao;
    uint16_t    horas_cursadas;
    float       pontuacao;
    float       ia;
    node_t*     mc_do_curso;
    dll_t*      discip_node_list;
};

// ALUNO_T FUNCTIONS
aluno_t* aluno_new( uint8_t* nome, uint32_t matricula, uint16_t id_curso, uint8_t id_grade,
                    uint16_t ano_entrada, uint8_t semestre_entrada, uint8_t situacao, dll_t* lista_de_mc)
{
    aluno_t* aluno = (aluno_t*)malloc(sizeof(aluno_t));
    if(aluno == NULL){
        perror("ERROR: at aluno_new");
        exit(EXIT_FAILURE);
    }

    aluno->nome = (uint8_t*)malloc(strlen((char*)nome)+1);
    if(aluno->nome == NULL){
        perror("ERROR: at aluno_new");
        exit(EXIT_FAILURE);
    }
    strncpy((char*)aluno->nome, (char*)nome,strlen((char*)nome)+1);

    aluno->matricula = matricula;
    aluno->id_curso = id_curso;
    aluno->id_grade = id_grade;
    aluno->ano_entrada = ano_entrada;
    aluno->semestre_entrada = semestre_entrada;
    aluno->situacao = situacao;
    aluno->horas_cursadas = 0;
    aluno->pontuacao = 0;
    aluno->ia = 0;
    aluno->mc_do_curso = aluno_find_mc_node(lista_de_mc, id_curso, id_grade);
    aluno->discip_node_list = dll_new();
    return aluno;
}

void aluno_delete(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("Error at aluno_delete - aluno is null");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    node_t* discip_node;
    node_t* next_discip_node;
    discip_node = dll_get_head(aluno_get_discip_node_list(aluno));
    for(i=0; i<dll_get_list_size(aluno_get_discip_node_list(aluno)); i++){
        next_discip_node = node_get_next(discip_node);
        discip_node_delete(discip_node);
        discip_node = next_discip_node;
    }
    free(aluno->nome);
    dll_delete(aluno->discip_node_list);
    aluno->mc_do_curso = NULL;
    free(aluno);
}

// list functions
void aluno_discip_new(aluno_t* aluno, uint8_t* codigo_diciplina, uint32_t turma, float conceito,
                      uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao)
{
    if(aluno == NULL || codigo_diciplina == NULL){
        perror("Error at aluno_discip_new - aluno or codigo_diciplina is null");
        exit(EXIT_FAILURE);
    }

    node_t* discip_node = discip_node_new(aluno_get_mc_do_curso(aluno), codigo_diciplina, turma,
                                     conceito, faltas, frequencia, origem, situacao);

    dll_add_tail(aluno_get_discip_node_list(aluno), discip_node);
    node_t* uc_node = discip_node_get_uc_node(discip_node);

    aluno->horas_cursadas += uc_node_get_carga_horaria(uc_node);
    aluno->pontuacao += uc_node_get_carga_horaria(uc_node) * conceito;
    aluno->ia = aluno_get_pontuacao(aluno)/aluno_get_horas_cursadas(aluno);

    return;
}
/**
void aluno_discip_delete(aluno_t* aluno, uint8_t* codigo)
{

}
*/
node_t* aluno_find_mc_node(dll_t* lista_de_mc, uint16_t id_curso, uint8_t id_grade)
{
    if(lista_de_mc == NULL){
        perror("Error at aluno_find_mc_node - lista_de_mc is null");
        exit(EXIT_FAILURE);
    }

    uint16_t i;
    node_t* mc_node = dll_get_head((lista_de_mc));

    for(i=0;i<dll_get_list_size(lista_de_mc);i++){
        if(mc_node_get_id_curso(mc_node)== id_curso && mc_node_get_id_grade(mc_node) == id_grade)
        {
            return mc_node;
        }
        mc_node = node_get_next(mc_node);
    }
    return NULL;
}

// print functions
void aluno_print(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("Error at aluno_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i = 0;
    uint8_t j = 0;
    float porcentagem = (float)aluno_get_horas_cursadas(aluno)/(float)mc_node_get_total_horas(aluno_get_mc_do_curso(aluno))*(float)100;

    node_t* discip_node = dll_get_head(aluno_get_discip_node_list(aluno));
    node_t* uc_node = discip_node_get_uc_node(discip_node);

    fprintf(stdout,"\n--------------------------- Boletim Escolar  ----------------------------------\n");
    fprintf(stdout,"\nCurso:\t\t%d - Curso de %s\n", (int)mc_node_get_id_curso(aluno_get_mc_do_curso(aluno)),
                                                    (char*)mc_node_get_nome_curso(aluno_get_mc_do_curso(aluno)));

    fprintf(stdout,"Grade:\t\t%d - Matriz Curricular - %d/%d\n\n",(int)mc_node_get_id_grade(aluno_get_mc_do_curso(aluno)),
                                                            (int)mc_node_get_ano_criacao(aluno_get_mc_do_curso(aluno)),
                                                            (int)mc_node_get_semestre_criacao(aluno_get_mc_do_curso(aluno)));
    fprintf(stdout,"Aluno(a):\t%d - %s\n\n",(int)aluno_get_matricula(aluno),(char*)aluno_get_nome(aluno));
    fprintf(stdout,"Perido:\t%d/%d\t\t\tSituacao do Aluno no Periodo:\t%d\n",(int)aluno_get_ano_entrada(aluno),
                                                                           (int)aluno_get_semestre_entrada(aluno),
                                                                           (int)aluno_get_situacao(aluno));
    fprintf(stdout,"Indice Academico:\t%2.1f\tHoras Cursadas:\t%d\tCursado:\t%2.f%%\n", (float)aluno_get_ia(aluno),
                                                                                      (int)aluno_get_horas_cursadas(aluno),
                                                                                      (float)porcentagem);
    fprintf(stdout,"Unidades Curriculares: %d\n",(int)mc_node_get_uc_node_total(aluno_get_mc_do_curso(aluno)));

    for(i=0;i<aluno_get_discip_node_total(aluno);i++){
        if(uc_node_get_semestre(uc_node)!=j){
            j = uc_node_get_semestre(uc_node);
            fprintf(stdout,"\n_______________________________________________________________________________\n");
            fprintf(stdout,"- SEMESTRE %d -\n",j);
            fprintf(stdout,"_______________________________________________________________________________\n");
            fprintf(stdout," CH Codigo   Nome\t\t\tTurma\tNota  Faltas Freq. Orig. Sit.\n");
        }
        fprintf(stdout,"%3d %s %-25s\t%d\t%4.1f\t%d     %3d    %d    %d\n",(int)uc_node_get_carga_horaria(uc_node),
                                                              (char*)uc_node_get_codigo(uc_node),
                                                              (char*)uc_node_get_nome(uc_node),
                                                              (int)discip_node_get_turma(discip_node),
                                                              (float)discip_node_get_conceito(discip_node),
                                                              (int)discip_node_get_faltas(discip_node),
                                                              (int)discip_node_get_frequencia(discip_node),
                                                              (int)discip_node_get_origem(discip_node),
                                                              (int)discip_node_get_situacao(discip_node) );
        if((discip_node = node_get_next(discip_node)))
        uc_node = discip_node_get_uc_node(discip_node);
    }
    fprintf(stdout,"\n-------------------------------------------------------------------------------\n");

    return;
}
/**
//file functions
aluno_t* aluno_load_aluno(uint8_t* file)
{

}

void aluno_save_aluno(aluno_t* aluno, uint8_t* file)
{

}
*/
// GETTERS METHODS

uint16_t aluno_get_id_curso(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_id_curso");
        exit(EXIT_FAILURE);
    }
    return aluno->id_curso;
}

uint8_t aluno_get_id_grade(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_id_grade");
        exit(EXIT_FAILURE);
    }
    return aluno->id_grade;
}

uint32_t aluno_get_matricula(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_matricula");
        exit(EXIT_FAILURE);
    }
    return aluno->matricula;
}

uint8_t* aluno_get_nome(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_nome");
        exit(EXIT_FAILURE);
    }
    return aluno->nome;
}

uint16_t aluno_get_ano_entrada(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_ano_entrada");
        exit(EXIT_FAILURE);
    }
    return aluno->ano_entrada;
}

uint8_t aluno_get_semestre_entrada(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_semestre_entrada");
        exit(EXIT_FAILURE);
    }
    return aluno->semestre_entrada;

}

uint8_t aluno_get_situacao(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_situacao");
        exit(EXIT_FAILURE);
    }
    return aluno->situacao;
}

uint16_t aluno_get_horas_cursadas(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_horas_cursadas");
        exit(EXIT_FAILURE);
    }
    return aluno->horas_cursadas;
}

float aluno_get_pontuacao(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_pontuacao");
        exit(EXIT_FAILURE);
    }
    return aluno->pontuacao;
}

float aluno_get_ia(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_ia");
        exit(EXIT_FAILURE);
    }
    return aluno->ia;
}

node_t* aluno_get_mc_do_curso(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_mc_do_curso");
        exit(EXIT_FAILURE);
    }
    return aluno->mc_do_curso;
}

dll_t* aluno_get_discip_node_list(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_discip_node_list");
        exit(EXIT_FAILURE);
    }
    return aluno->discip_node_list;
}


//EXTRA GETTER FUNCTIONS
uint16_t aluno_get_discip_node_total(aluno_t* aluno)
{
    if(aluno == NULL){
        perror("ERROR at aluno_get_discip_node_total");
        exit(EXIT_FAILURE);
    }
    return dll_get_list_size(aluno_get_discip_node_list(aluno));
}
