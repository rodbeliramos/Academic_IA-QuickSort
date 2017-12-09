#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "matriz_curricular.h"
#include "unidade_curricular.h"
#include "node.h"
#include "doubly_linked_list.h"


struct aluno
{
    uint8_t*    nome;
    uint32_t    matricula;
    uint16_t    id_curso;
    uint8_t     id_grade;
    uint16_t    ano_entrada;
    uint8_t     semestre_entrada;
    uint8_t     situacao;
    uint16_t    horas_cursadas;
    float       ia;
    node_t*     mc_do_curso;
    dll_t*      discip_node_list;
};

// ALUNO_T FUNCTIONS
aluno_t* aluno_new( uint8_t* nome, uint32_t matricula, uint16_t id_curso, uint8_t id_grade,
                    uint16_t ano_entrada, uint8_t semestre_entrada, uint8_t situacao, dll_t* lista_de_mc)
{
    aluno_t* aluno = (aluno_t*)malloc(sizeof(aluno_t));
    if(aluno == NULL)
    {
        perror("ERROR: at aluno_new");
        exit(EXIT_FAILURE);
    }

    aluno->nome = (uint8_t*)malloc(strlen((char*)nome)+1);
    if(aluno->nome == NULL)
    {
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
    aluno->ia = 0;
    aluno->mc_do_curso = aluno_find_mc_node(lista_de_mc, id_curso, id_grade);
    aluno->discip_node_list = dll_new();
    return aluno;
}

void aluno_delete(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("Error at aluno_delete - aluno is null");
        exit(EXIT_FAILURE);
    }
    uint16_t i;
    node_t* discip_node;
    node_t* next_discip_node;
    discip_node = dll_get_head(aluno_get_discip_node_list(aluno));
    for(i=0; i<dll_get_list_size(aluno_get_discip_node_list(aluno)); i++)
    {
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
    if(aluno == NULL || codigo_diciplina == NULL)
    {
        perror("Error at aluno_discip_new - aluno or codigo_diciplina is null");
        exit(EXIT_FAILURE);
    }
    float pontuacao;
    node_t* discip_node = discip_node_new(aluno_get_mc_do_curso(aluno), codigo_diciplina, turma,
                                          conceito, faltas, frequencia, origem, situacao);

    dll_add_tail(aluno_get_discip_node_list(aluno), discip_node);
    node_t* uc_node = discip_node_get_uc_node(discip_node);

    pontuacao = aluno_get_ia(aluno) * (float)aluno_get_horas_cursadas(aluno)
                + (float)uc_node_get_carga_horaria(uc_node) * conceito;

    aluno->horas_cursadas += uc_node_get_carga_horaria(uc_node);
    aluno->ia = pontuacao/aluno_get_horas_cursadas(aluno);

    return;
}
/**
void aluno_discip_delete(aluno_t* aluno, uint8_t* codigo)
{

}
*/
node_t* aluno_find_mc_node(dll_t* lista_de_mc, uint16_t id_curso, uint8_t id_grade)
{
    if(lista_de_mc == NULL)
    {
        perror("Error at aluno_find_mc_node - lista_de_mc is null");
        exit(EXIT_FAILURE);
    }

    uint16_t i;
    node_t* mc_node = dll_get_head((lista_de_mc));

    for(i=0; i<dll_get_list_size(lista_de_mc); i++)
    {
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
    if(aluno == NULL)
    {
        perror("Error at aluno_print");
        exit(EXIT_FAILURE);
    }
    uint16_t i = 0;
    uint8_t j = 0;

    node_t* discip_node = dll_get_head(aluno_get_discip_node_list(aluno));
    node_t* uc_node = discip_node_get_uc_node(discip_node);

    fprintf(stdout,"\n--------------------------- Boletim Escolar  ----------------------------------\n");
    fprintf(stdout,"\nCurso:\t\t%d - Curso de %s\n", (int)mc_node_get_id_curso(aluno_get_mc_do_curso(aluno)),
            (char*)mc_node_get_nome_curso(aluno_get_mc_do_curso(aluno)));

    fprintf(stdout,"Grade:\t\t%d - Matriz Curricular - %d/%d\n\n",(int)mc_node_get_id_grade(aluno_get_mc_do_curso(aluno)),
            (int)mc_node_get_ano_criacao(aluno_get_mc_do_curso(aluno)),
            (int)mc_node_get_semestre_criacao(aluno_get_mc_do_curso(aluno)));
    fprintf(stdout,"Aluno(a):\t%d - %s\n\n",(int)aluno_get_matricula(aluno),(char*)aluno_get_nome(aluno));
    fprintf(stdout,"Perido:\t%d/%d\t\t\t\tSituacao do Aluno no Periodo:\t%d\n",(int)aluno_get_ano_entrada(aluno),
            (int)aluno_get_semestre_entrada(aluno),
            (int)aluno_get_situacao(aluno));
    fprintf(stdout,"Indice Academico:\t%2.1f\t\tHoras Cursadas:\t%d\n", (float)aluno_get_ia(aluno),
            (int)aluno_get_horas_cursadas(aluno));
    fprintf(stdout,"Unidades Curriculares:\t%d\n",(int)mc_node_get_uc_node_total(aluno_get_mc_do_curso(aluno)));

    for(i=0; i<aluno_get_discip_node_total(aluno); i++)
    {
        if(uc_node_get_semestre(uc_node)!=j)
        {
            j = uc_node_get_semestre(uc_node);
            fprintf(stdout,"\n_______________________________________________________________________________\n");
            fprintf(stdout,"- SEMESTRE %d -\n",j);
            fprintf(stdout,"_______________________________________________________________________________\n");
            fprintf(stdout," CH Codigo   Nome\t\t\tTurma\tNota  Faltas  Freq.  Orig. Sit.\n");
        }
        fprintf(stdout,"%3d %s %-25s\t%d\t%4.1f\t%3d   %5.1f%%   %2d   %2d\n",(int)uc_node_get_carga_horaria(uc_node),
                (char*)uc_node_get_codigo(uc_node),
                (char*)uc_node_get_nome(uc_node),
                (int)discip_node_get_turma(discip_node),
                (float)discip_node_get_conceito(discip_node),
                (int)discip_node_get_faltas(discip_node),
                (float)discip_node_get_frequencia(discip_node),
                (int)discip_node_get_origem(discip_node),
                (int)discip_node_get_situacao(discip_node) );
        if((discip_node = node_get_next(discip_node)))
            uc_node = discip_node_get_uc_node(discip_node);
    }
    fprintf(stdout,"\n-------------------------------------------------------------------------------\n");

    return;
}

//file functions
aluno_t* aluno_load_aluno(void)
{
    aluno_t* novo_aluno = NULL;
    uint8_t nome[50];
    uint32_t matricula = NULL;
    char c_matricula[10];
    uint16_t id_curso = NULL;
    char c_id_curso[10];
    uint8_t id_grade = NULL;
    uint16_t ano_entrada = NULL;
    char c_ano_entrada[5];
    char c_entrada[7];
    uint8_t semestre_entrada = NULL;
    char c_periodo[100];
    uint8_t situacao = NULL;
    char c_situacao[6];
    int line_index = 1;
    char buffer[100];
    dll_t* lista_de_mc;
    lista_de_mc = dll_new();

    int i = 0;

    int disp_turma;
    char c_disp_turma[7];
    float disp_conceito;
    int disp_falta;
    char c_disp_falta[3];
    float disp_frequencia;
    char c_disp_frequencia[2];
    int disp_origem;
    char c_origem[7];
    int disp_situacao;
    char c_disp_situacao[5];

    node_t* mc_eng;
    mc_eng = mc_node_load_mc((uint8_t*)"matriz_teste_eng.csv");
    dll_add_tail(lista_de_mc,mc_eng);

    dll_t* lista_de_uc = mc_node_get_uc_node_list(mc_eng);
    //node_t* searching_node = dll_get_head(lista_de_uc);

    char* uc_codigo;
    char codigobuffer[9];

    char arquivo[20];
    printf("Digite o nome do arquivo aluno: ");
    scanf("%s", arquivo);
    fflush(stdin);

    //char nome_arquivo = 'boletim_test.txt';




    // printf("Digite o nome do arquivo do aluno a ser adicionado: ");
    //scanf("%s", (char*)nome_arquivo);

//(uint8_t*)"Rodrigo Belisario"

    FILE *fp = fopen(arquivo, "r"); //lê arquivo

    if (fp == NULL) // Verificação de erro
    {
        /* Imprime erro e aborta */
        perror("Erro em ler_arquivo: fopen"); //mensagem de erro
        exit(EXIT_FAILURE); // Exit
    }

    while (fgets(buffer,100,fp)!= NULL)
    {
        if (!strcmp(c_periodo,buffer))
        {
            fgets(buffer,100,fp);
            fgets(buffer,100,fp);
            strncpy(c_entrada, buffer, 7);
            c_entrada[6] = '\0';

            line_index = line_index +2;
        }
        if (line_index == 8)
        {

            strncpy(c_id_curso, buffer, 3);
            id_curso = atoi(c_id_curso);
        }
        if (line_index == 12)
        {

            id_grade = atoi(&buffer[0]);
        }
        if (line_index == 16)
        {
            strncpy(c_matricula, buffer, 10);
            matricula = atoi(c_matricula);
            memcpy((char*)nome, &buffer[13], 50);
        }
        if (line_index == 18)
        {
            strncpy(c_periodo, buffer, 100);
            fgets(buffer,100,fp);
            fgets(buffer,100,fp);
            strncpy(c_entrada, buffer, 7);
            c_entrada[6] = '\0';

            line_index = line_index +2;
        }
        if (line_index == 24)
        {
            strncpy(c_situacao, buffer, 6);
            c_situacao[5] = '\0';
            situacao = !strcmp(c_situacao,"Ativa");

            //printf("em line 24 c_entrada = %s", c_entrada);

            strncpy(c_ano_entrada, c_entrada, 5);
            c_ano_entrada[4] = '\0';

            ano_entrada = atoi(c_ano_entrada);
            semestre_entrada = atoi(&c_entrada[5]);

            novo_aluno = aluno_new(nome, matricula, id_curso, id_grade, ano_entrada, semestre_entrada, situacao, lista_de_mc);
        }

        node_t* searching_node = dll_get_head(lista_de_uc);

        for(i = 0; i<(mc_node_get_uc_node_total(mc_eng))-1; i++)
        {

            uc_codigo = (char*)uc_node_get_codigo(searching_node);


            strncpy(codigobuffer, buffer,9);
            codigobuffer[8] = '\0';
          //  printf("codigobuffer: %s\n", codigobuffer);



            if (!(strcmp(codigobuffer, uc_codigo)))
            {

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);
                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                strncpy(c_disp_turma, buffer, 7);
                disp_turma = atoi(c_disp_turma);

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                disp_conceito = atoi(&buffer[0]);
                if(buffer[0]=='E')
                    disp_conceito = 10;
                if(buffer[0]=='P')
                    disp_conceito = 8;
                if(buffer[0]=='S')
                    disp_conceito = 6;
                if(buffer[0]=='I')
                    disp_conceito = 4;

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                strncpy(c_disp_falta, buffer, 3);
                disp_falta = atoi(c_disp_falta);

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                strncpy(c_disp_frequencia, buffer, 3);
                disp_frequencia = atoi(c_disp_frequencia);

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                strncpy(c_origem, buffer,7);
                c_origem[6] = '\0';
                disp_origem = !strcmp(c_origem,"Normal");
               // if (disp_origem!= 1)
                   // disp_origem = 0;

                fgets(buffer,100,fp);
                fgets(buffer,100,fp);

                strncpy(c_disp_situacao, buffer,5);
                c_disp_situacao[4] = '\0';
                disp_situacao = !strcmp(c_disp_situacao,"Apto");

                //printf("ENTROUUUU");

                aluno_discip_new(novo_aluno, (uint8_t*)uc_codigo, (uint16_t)disp_turma, (float)disp_conceito, (uint8_t)disp_falta, (float)disp_frequencia, (uint8_t)disp_origem, (uint8_t)disp_situacao);
            }


        searching_node = node_get_next(searching_node);
        }

        //printf ("%s \n fim do get \n ",buffer);
        line_index++;

    }
    strncpy(c_ano_entrada, c_entrada, 5);
    c_ano_entrada[4] = '\0';

    ano_entrada = atoi(c_ano_entrada);
    semestre_entrada = atoi(&c_entrada[5]);

    novo_aluno->ano_entrada = ano_entrada;
    novo_aluno->semestre_entrada = semestre_entrada;


    /*
    printf("line index: %i\n",line_index);
    printf("Id do curso: %i\n", id_curso);
    printf("matricula: %i\n", matricula);
    printf("Nome: %s\n", (char*)nome);
    printf("Id da grade: %i\n", id_grade);
    printf("situacao: %i\n", situacao);
    printf("Entrada: %s\n", c_entrada);
    printf("Ano entrada: %i\n", ano_entrada);
    printf("Semestre entrada: %i\n", semestre_entrada);
    */

    fclose(fp);


    //aluno_discip_new(novo_aluno, uint8_t* codigo_diciplina, uint32_t turma, float conceito,uint8_t faltas, float frequencia, uint8_t origem, uint8_t situacao);

    //novo_aluno = aluno_new(nome, matricula, id_curso, id_grade, ano_entrada, semestre_entrada, situacao, lista_de_mc);




    fclose(fp);

    return novo_aluno;
}

/**
void aluno_save_aluno(aluno_t* aluno, uint8_t* file)
{

}
*/
// GETTERS METHODS

uint16_t aluno_get_id_curso(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_id_curso");
        exit(EXIT_FAILURE);
    }
    return aluno->id_curso;
}

uint8_t aluno_get_id_grade(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_id_grade");
        exit(EXIT_FAILURE);
    }
    return aluno->id_grade;
}

uint32_t aluno_get_matricula(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_matricula");
        exit(EXIT_FAILURE);
    }
    return aluno->matricula;
}

uint8_t* aluno_get_nome(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_nome");
        exit(EXIT_FAILURE);
    }
    return aluno->nome;
}

uint16_t aluno_get_ano_entrada(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_ano_entrada");
        exit(EXIT_FAILURE);
    }
    return aluno->ano_entrada;
}

uint8_t aluno_get_semestre_entrada(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_semestre_entrada");
        exit(EXIT_FAILURE);
    }
    return aluno->semestre_entrada;

}

uint8_t aluno_get_situacao(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_situacao");
        exit(EXIT_FAILURE);
    }
    return aluno->situacao;
}

uint16_t aluno_get_horas_cursadas(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_horas_cursadas");
        exit(EXIT_FAILURE);
    }
    return aluno->horas_cursadas;
}

float aluno_get_ia(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_ia");
        exit(EXIT_FAILURE);
    }
    return aluno->ia;
}

node_t* aluno_get_mc_do_curso(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_mc_do_curso");
        exit(EXIT_FAILURE);
    }
    return aluno->mc_do_curso;
}

dll_t* aluno_get_discip_node_list(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_discip_node_list");
        exit(EXIT_FAILURE);
    }
    return aluno->discip_node_list;
}


//EXTRA GETTER FUNCTIONS
uint16_t aluno_get_discip_node_total(aluno_t* aluno)
{
    if(aluno == NULL)
    {
        perror("ERROR at aluno_get_discip_node_total");
        exit(EXIT_FAILURE);
    }
    return dll_get_list_size(aluno_get_discip_node_list(aluno));
}



