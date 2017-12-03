#include <stdio.h>
#include <stdlib.h>
#include "matriz_curricular.h"
#include "unidade_curricular.h"
#include "node.h"
#include "doubly_linked_list.h"

int main()
{
    mc_t* mc_eng;
    mc_eng = mc_new((uint8_t*)"Engenharia Eletronica", 221, 2013,1);

    node_t* uc1 = uc_node_new(1,(uint8_t*)"GMT22101",(uint8_t*)"Geometria Analitica",54);
    node_t* uc2 = uc_node_new(1,(uint8_t*)"CAA22101",(uint8_t*)"Calcula A",108);
    node_t* uc3 = uc_node_new(1,(uint8_t*)"CAB22102",(uint8_t*)"Calcula B",72);
    //printf("%d,",(int)uc_node_get_carga_horaria(uc1));
    mc_uc_new(mc_eng,uc1);
    mc_uc_new(mc_eng,uc2);
    mc_uc_new(mc_eng,uc3);
    //mc_uc_delete(mc_eng, (uint8_t*)"GMT22101");
    mc_uc_delete(mc_eng, (uint8_t*)"CAA22101");
    //mc_uc_delete(mc_eng, (uint8_t*)"CAB22102");



    node_t* node1 = node_new(uc1);
    mc_print(mc_eng);

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
