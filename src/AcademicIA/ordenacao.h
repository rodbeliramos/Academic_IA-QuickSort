#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED

void ordernar_quicksort(aluno_t **vetor_alunos, int qtd_alunos);
int mediana_de_tres(aluno_t **vetor_alunos, int indice_esq, int indice_dir);
void swap_alunos(aluno_t **vetor_alunos, int indice1, int indice2);
void quicksort(aluno_t **vetor_alunos, int indice_esq, int indice_dir);
int particionar(aluno_t **vetor_alunos,int  indice_esq,int  indice_dir);

#endif // ORDENACAO_H_INCLUDED
