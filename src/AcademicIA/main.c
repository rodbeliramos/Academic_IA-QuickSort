#include <stdio.h>
#include <stdlib.h>
#include "matriz_curricular.h"
#include "unidade_curricular.h"
#include "node.h"
#include "doubly_linked_list.h"
#include "aluno.h"
int main()
{
    dll_t* lista_de_mc;
    lista_de_mc = dll_new();

    node_t* mc_eng;
    mc_eng = mc_node_load_mc((uint8_t*)"matriz_teste_eng.csv");
    mc_node_print(mc_eng);

    node_t* mc_sis_elet;
    mc_sis_elet = mc_node_new((uint8_t*)"Sistemas Eletronicos", 203, 2, 2001, 2);


    node_t* uc1 = uc_node_new(1,(uint8_t*)"GMT22101",(uint8_t*)"Geometria Analitica",54);
    node_t* uc2 = uc_node_new(1,(uint8_t*)"CAL22101",(uint8_t*)"Calcula A",108);
    node_t* uc3 = uc_node_new(1,(uint8_t*)"CAB22102",(uint8_t*)"Calcula B",72);
    mc_node_uc_new(mc_sis_elet, uc1);
    mc_node_uc_new(mc_sis_elet, uc2);
    mc_node_uc_new(mc_sis_elet, uc3);
    //mc_node_uc_delete(mc_sis_elet, "CAA22101");
    mc_node_print(mc_sis_elet);

    dll_add_tail(lista_de_mc,mc_eng);
    dll_add_tail(lista_de_mc,mc_sis_elet);

    aluno_t* aluno1;
    aluno1 = aluno_new((uint8_t*)"Rodrigo Belisario", 1710067462, 221, 1, 2017, 1, 1, lista_de_mc);
    aluno_discip_new(aluno1, (uint8_t*)"COM22101", 221019, 8.0, 0, 100.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"EGS22101", 221012, 9.0, 8, 76.5, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"GMT22101", 221012, 6.0, 6, 90.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"PIN22101", 221012, 10.0, 6, 85.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"ELD22101", 221019, 8.0, 0, 100.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"QMG22101", 221012, 6.0, 1, 98.3, 1, 1);

    aluno_discip_new(aluno1, (uint8_t*)"CAL22101", 221012, 0.0, 34, 71.7, 1, 1);    //influencia no percentual cursado

    aluno_discip_new(aluno1, (uint8_t*)"CAL22101", 221019, 7.0, 0, 100.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"ELD22102", 221019, 8.0, 0, 100.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"MEP22103", 221019, 8.0, 0, 100.0, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"PRG22104", 221042, 7.0, 7,  88.3, 1, 1);
    aluno_discip_new(aluno1, (uint8_t*)"ARQ22104", 221041, 9.0, 6,  85.0, 1, 1);



    aluno_print(aluno1);

    aluno_delete(aluno1);           //deleta aluno e cada disciplina cursada do aluno.
    mc_node_delete(mc_eng);         //deleta matriz curricular e cada unidade curricular dentro dela.
    mc_node_delete(mc_sis_elet);    //deleta matriz curricular e cada unidade curricular dentro dela.
    dll_delete(lista_de_mc);        //deleta lista de matrizes curriculares.

    //mc_eng = mc_new((uint8_t*)"Engenharia Eletronica", 221, 2013,1);

    //printf("%d,",(int)uc_node_get_carga_horaria(uc1));
    //mc_uc_new(mc_eng,uc1);
    //mc_uc_new(mc_eng,uc2);
    //mc_uc_new(mc_eng,uc3);
    //mc_uc_delete(mc_eng, (uint8_t*)"GMT22101");
    //mc_uc_delete(mc_eng, (uint8_t*)"CAA22101");
    //mc_uc_delete(mc_eng, (uint8_t*)"CAB22102");

    //mc_save_mc(mc_eng, (uint8_t*)"matriz_teste_eng.csv");
    //node_t* node1 = node_new(uc1);
//mc_delete(mc_eng);
    //node_t* uc_ca = mc_find_uc_node(mc_eng,(uint8_t*)"CAA22101");
  //  uc_node_print(uc_ca);

  /*uc_t* uc2 = uc_new(1,(uint8_t*)"GMT22101",(uint8_t*)"Geometria Analitica",54);
    uc_t* uc3 = uc_new(1,(uint8_t*)"QMG22101",(uint8_t*)"Quimica Geral",54);
    uc_t* uc4 = uc_new(1,(uint8_t*)"COM22101",(uint8_t*)"Comunicação e Expressão",36);
    uc_t* uc5 = uc_new(1,(uint8_t*)"EGS22101",(uint8_t*)"Eng. E Sustentabilidade",36);
    uc_t* uc6 = uc_new(1,(uint8_t*)"ELD22101",(uint8_t*)"Eletrônica Digital I",72);
    uc_t* uc7 = uc_new(1,(uint8_t*)"PIN22101",(uint8_t*)"Projeto Integrador I",36);

    uc_t* uc8 = uc_new(2,(uint8_t*)"CAB22102",(uint8_t*)"Cálculo B",72);
    uc_t* uc9 = uc_new(2,(uint8_t*)"FFM22102",(uint8_t*)"Fund. De FSC em Mecânica",108);
    uc_t* uc20 = uc_new(3,(uint8_t*)"SEG22103",(uint8_t*)"Asp. De Seg. Em Eletricid.",36);
    uc_t* uc21 = uc_new(4,(uint8_t*)"PRG22104",(uint8_t*)"Programação de Comp. I",54);

    // Inserir Optativas aqui

    mc_add_uc_tail(mc_eng, uc1);
    mc_add_uc_tail(mc_eng, uc2);
    mc_add_uc_tail(mc_eng, uc3);
    mc_add_uc_tail(mc_eng, uc4);
    mc_add_uc_tail(mc_eng, uc5);
    mc_add_uc_tail(mc_eng, uc6);
    mc_add_uc_tail(mc_eng, uc7);
    mc_add_uc_tail(mc_eng, uc8);
    mc_add_uc_tail(mc_eng, uc9);
    mc_add_uc_tail(mc_eng, uc20);
    mc_add_uc_tail(mc_eng, uc21);


    mc_print(mc_eng);*/
    return 0;
}
