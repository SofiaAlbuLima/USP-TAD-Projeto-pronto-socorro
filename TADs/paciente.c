#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "historico.h"

struct paciente_ {
    char nome[TAM_NOME];
    int id;
    HISTORICO* procedimentos;
};

PACIENTE* paciente_criar(char string[], int i) {
    PACIENTE *p;
    p = (PACIENTE *) malloc(sizeof(PACIENTE));

    if(p!=NULL) {
        strcpy(p->nome, string);
        p->id = i;
        p->procedimentos = historico_criar();
        return p;
    }

    return NULL;
}

bool paciente_apagar(PACIENTE** aux) {
    if (aux!=NULL) {
        if(*aux!=NULL) {
            if(historico_apagar(&((*aux)->procedimentos)) == true){
                free(*aux);
                *aux = NULL;
                return true;
            }
        }
    }
    return false;
}

void paciente_imprimir(PACIENTE* aux) {
    if(aux != NULL) {
        printf("Nome: %s\n", aux->nome);
        printf("ID: %d\n", aux->id);
        historico_consultar(aux->procedimentos);
    }
    else {
        printf("Paciente nao existe ou nao ha memoria suficiente para possibilitar sua impressao");
    }
}

int paciente_obter_ID(PACIENTE* aux) {
    if (aux != NULL) return(aux->id);
    else return(-1);
}

void paciente_imprimir_nome(PACIENTE* aux) {
    if(aux!=NULL) printf("%s", aux->nome);
}

void paciente_consultar_historico(PACIENTE* aux) {
    if(aux!=NULL) historico_consultar(aux->procedimentos);
}

bool paciente_adicionar_procedimento(PACIENTE* aux, PROCEDIMENTO* procedimento) {
    if (aux != NULL) {
        inserir_procedimento(aux->procedimentos, procedimento);
        return true;    
    }
    return false;
}

PROCEDIMENTO* paciente_desfazer_procedimento(PACIENTE* aux) {
    if(aux != NULL) {
        PROCEDIMENTO* p = desfazer_procedimento(aux->procedimentos);
        return p;
    }
    return NULL;
}