#include <stdio.h>
#include <stdlib.h>
#include "matriz_curricular.h"
#include "unidade_curricular.h"
#include "node.h"
#include "doubly_linked_list.h"
#include "aluno.h"
#include "ordenacao.h"

int main()
{
    aluno_t **vetor_alunos = NULL;
    int qtd_alunos = 0;

    int i, menu = 0;
    int valid_input;
    int busca_matricula;
    char nome_aluno[50];
    float ia_aluno;
    char busca_codigo_discip[8];
    char arquivo[10];
    node_t* uc_node;
    FILE *fp;

    dll_t* lista_de_mc;
    lista_de_mc = dll_new();
    node_t* mc_eng;
    mc_eng = mc_node_load_mc((uint8_t*)"matriz_teste_eng.csv");
    node_t* mc_sis_elet;

    mc_sis_elet = mc_node_new((uint8_t*)"Sistemas Eletronicos", 203, 2, 2001, 2);
    node_t* uc1 = uc_node_new(1,(uint8_t*)"GMT22101",(uint8_t*)"Geometria Analitica",54);
    node_t* uc2 = uc_node_new(1,(uint8_t*)"CAL22101",(uint8_t*)"Calcula A",108);
    node_t* uc3 = uc_node_new(1,(uint8_t*)"CAB22102",(uint8_t*)"Calcula B",72);

    mc_node_uc_new(mc_sis_elet, uc1);
    mc_node_uc_new(mc_sis_elet, uc2);
    mc_node_uc_new(mc_sis_elet, uc3);
    dll_add_tail(lista_de_mc,mc_eng);
    dll_add_tail(lista_de_mc,mc_sis_elet);

    vetor_alunos = aluno_load_from_csv((uint32_t*)&qtd_alunos,(uint8_t*)"lista_de_alunos.csv",lista_de_mc);

    printf("Bem Vindo ao programa de Calculo de Indice Academico.\n\n ");

    while(1)
    {
        valid_input = 0;
        printf("Selecione a Opcao desejada:\n1 - Buscar Aluno\n2 - Buscar Disciplina\n3 - Buscar Matriz Curricular\n");
        printf("4 - Adicionar Aluno via .txt\n5 - Ordenar alunos por IA\n6 - Salvar\n7 - Exit\n\nInput:");

        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            printf("\nDigite a matricula do aluno a ser buscado: ");
            scanf("%d", &busca_matricula);

            for (i=0; i<qtd_alunos; i++)
            {
                if (aluno_get_matricula(vetor_alunos[i]) == (uint32_t)busca_matricula)
                {
                    aluno_print(vetor_alunos[i]);
                    break;
                }
                if (i == qtd_alunos)
                    printf("Aluno Invalido -(Nao encontrado)\n\n");
            }

            break;


        case 2:
            printf("\nDigite o codigo da disciplina a ser buscada: ");
            scanf("%s", busca_codigo_discip);


            uc_node = mc_node_find_uc_node(mc_eng, (uint8_t*)busca_codigo_discip);
            if(uc_node == NULL)
                printf("Codigo de disciplina invalido\n");
            else
                uc_node_print(uc_node);

            printf("\n");
            break;

        case 3:
            //dll_t* lista_de_mc;
            //lista_de_mc = dll_new();
            //node_t* mc_eng;
            //mc_eng = mc_node_load_mc((uint8_t*)"matriz_teste_eng.csv");

            mc_node_print(mc_eng);
            break;

        case 4:
            while (!valid_input)
            {
                printf("Digite o nome do arquivo aluno: ");
                scanf("%s", arquivo);
                fflush(stdin);
                fp = fopen(arquivo, "r"); //lê arquivo



                if (fp == NULL) // Verificação de erro
                {
                    /* Imprime erro e aborta */
                    perror("Erro em ler_arquivo: fopen\n"); //mensagem de erro
                    valid_input = 0;

                }
                else
                    valid_input = 1;
            }

            if (qtd_alunos == 0)
                vetor_alunos = malloc(sizeof(aluno_t*));

            else
                vetor_alunos = (aluno_t**)realloc(vetor_alunos, (qtd_alunos+1)*sizeof(aluno_t*));


            vetor_alunos[qtd_alunos] = aluno_load_from_txt(arquivo, fp);
            aluno_print(vetor_alunos[qtd_alunos]);
            qtd_alunos++;

            break;

        case 5:

            printf("Alunos por ordem de maior IA:\n\nAluno\t\t\tIndice Academico\n");
            ordernar_quicksort(vetor_alunos, qtd_alunos);
            for(i=qtd_alunos; i>0; i--)
            {
                strcpy(nome_aluno, (char*)aluno_get_nome(vetor_alunos[i-1]));
                ia_aluno = aluno_get_ia(vetor_alunos[i-1]);
                printf("%s\t\t\t%f\tindice: %d\n", nome_aluno, ia_aluno,i);
            }


            break;

        case 6:
            aluno_save_to_csv(vetor_alunos,qtd_alunos,(uint8_t*)"lista_de_alunos_2.csv");


            break;

        case 7:
            goto fim_do_menu;

        case 8:
            for(i=0;i<qtd_alunos;i++){
                aluno_print(vetor_alunos[i]);
            }
        }

    }
    fim_do_menu:

           //deleta lista de matrizes curriculares.

    for(i=0; i<qtd_alunos;i++)
    {
    aluno_delete(vetor_alunos[i]);           //deleta aluno e cada disciplina cursada do aluno.
    mc_node_delete(mc_eng);         //deleta matriz curricular e cada unidade curricular dentro dela.
    mc_node_delete(mc_sis_elet);    //deleta matriz curricular e cada unidade curricular dentro dela.
    dll_delete(lista_de_mc);

    }
    return 0;
}
