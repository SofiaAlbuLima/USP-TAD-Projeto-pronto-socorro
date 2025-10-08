#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"

#define TAM_NOME 101

struct paciente_ {
    char nome[TAM_NOME];
    int id;
    HISTORICO* procedimentos;
};

PACIENTE* paciente_criar(PACIENTE paciente) {
    PACIENTE *p;
    p = (PACIENTE *) malloc(sizeof(PACIENTE));

    if(p!=NULL) {
        strcpy(p->nome, paciente.nome);
        p->id = paciente.id;
        
        return p;
    }

    return NULL;
}