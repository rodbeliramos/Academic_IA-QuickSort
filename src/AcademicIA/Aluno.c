#include <stdio.h>
#include "aluno.h"

struct aluno
{
    int matricula;
	char nome[50];
	int entrada_ano;
	int entrada_semestre;
	char curso[20];
	int grade_ano;
	int grade_semestre;
	float indice_academico;
	int situacao;// (ativo, trancado, jubilado, cancelado)
	int qtd_disciplinas_cursadas;
};

aluno_t* cria_aluno(void)
{
    aluno_t estudante;
    aluno_t* p_estudante = &estudante;
    printf("Digite a matricula do novo aluno: ");
    scanf("%d", &estudante.matricula);
    fflush(stdin);

    printf("Digite nome do novo aluno: ");
    scanf("%s",estudante.nome);
    fflush(stdin);

    printf("Digite o ano de entrada do novo aluno: ");
    scanf("%d",&estudante.entrada_ano);
    fflush(stdin);

    printf("Digite semestre de entrada novo aluno: ");
    scanf("%d",&estudante.entrada_semestre);
    fflush(stdin);

    printf("Digite o curso do novo aluno: ");
    scanf("%s",estudante.curso);
    fflush(stdin);

    printf("Digite o ano da grade do novo aluno: ");
    scanf("%d", &estudante.grade_ano);
    fflush(stdin);

    printf("Digite o semestre da grade do novo aluno: ");
    scanf("%d", &estudante.grade_semestre);
    fflush(stdin);

    printf("Digite a situacao do novo aluno ( 1-ativo, 2-trancado, 3-jubilado, 4-cancelado): ");
    scanf("%d", &estudante.situacao);
    fflush(stdin);

    estudante.indice_academico = 0;
    estudante.qtd_disciplinas_cursadas = 0;

    print_aluno(estudante);

    return p_estudante;
}

void print_aluno(aluno_t estudante)
{
    printf("Matricula: %d \t\t Nome: %s\nSemestre de entrada: %d/%d\tCurso: %s\tGrade: %d/%d\nIndice academico: %f\tSituacao: %d", estudante.matricula, estudante.nome, estudante.entrada_ano,
            estudante.entrada_semestre, estudante.curso, estudante.grade_ano, estudante.grade_semestre, estudante.indice_academico, estudante.situacao);
    return;
}
