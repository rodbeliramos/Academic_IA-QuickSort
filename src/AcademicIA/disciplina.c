#include <stdio.h>
#include <stdlib.h>
#include "disciplina.h"

struct disciplina {
    //uint16_t semestre;      //int
    uint8_t codigo[9];      //char[]
    //uint8_t* nome;          //char[]
    uint16_t turma;         //int
    float conceito;
    uint8_t faltas;        //int
    float frequencia;       //float
    uint16_t origem;        //int talvez usar enum
    uint16_t situacao;      //int talvez usar enum
    //uint16_t carga_horaria; //int
};

discip_t* discip_new(uint8_t* codigo_disciplina, mc_t* mc){

}
