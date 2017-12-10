#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "ordenacao.h"

void ordernar_quicksort(aluno_t **vetor_alunos, int qtd_alunos)
{

    int indice_dir = qtd_alunos-1;
    int indice_esq=0;

    quicksort(vetor_alunos, indice_esq, indice_dir);

    return;
}
void quicksort(aluno_t **vetor_alunos, int indice_esq, int indice_dir)
{
    int p;

    if(indice_esq<indice_dir)
    {
    p = particionar(vetor_alunos, indice_esq, indice_dir);
    quicksort(vetor_alunos, indice_esq, p);
    quicksort(vetor_alunos, p+1, indice_dir);
    }

}

int mediana_de_tres(aluno_t **vetor_alunos, int indice_esq, int indice_dir)
{
    int indice_med = (indice_esq+indice_dir)/2;

    if (aluno_get_ia(vetor_alunos[indice_dir])<aluno_get_ia(vetor_alunos[indice_esq]))
    {
        swap_alunos(vetor_alunos, indice_esq, indice_dir);
    }

    if (aluno_get_ia(vetor_alunos[indice_med])<aluno_get_ia(vetor_alunos[indice_esq]))
    {
        swap_alunos(vetor_alunos, indice_med, indice_esq);
    }

    if (aluno_get_ia(vetor_alunos[indice_dir])<aluno_get_ia(vetor_alunos[indice_med]))
    {
        swap_alunos(vetor_alunos, indice_dir, indice_med);
    }

    return indice_med;
}

void swap_alunos(aluno_t **vetor_alunos, int indice1, int indice2)
{
    aluno_t* aluno;
    /*
    puts("SWAP - Happening!!!**************\n");
    aluno_t *aluno1;
    aluno_t* aluno2;
    aluno_t* aluno_temp;

    aluno1 = vetor_alunos[indice1];
    aluno2 = vetor_alunos[indice2];
    aluno_print(aluno1);
    aluno_print(aluno2);
    */

    aluno = vetor_alunos[indice1];
    vetor_alunos[indice1] = vetor_alunos[indice2];
    vetor_alunos[indice2]=aluno;
}

int particionar(aluno_t **vetor_alunos,int  indice_esq,int  indice_dir)
{

    int indice_med = mediana_de_tres(vetor_alunos, indice_esq, indice_dir);
    float pivot = aluno_get_ia (vetor_alunos[indice_med]);
    int i = indice_esq - 1;
    int j = indice_dir + 1;


    for(;;)
    {
        do
        {
            i++;
        }
        while(aluno_get_ia(vetor_alunos[i])<pivot);

        do
        {
            j--;
        }
        while(aluno_get_ia(vetor_alunos[j])>pivot);  //while(array[j]<pivot);

        if (i>=j)
            return j;

        swap_alunos(vetor_alunos, i, j);
    }
}

