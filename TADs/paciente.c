#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

void paciente_imprimir_fila(PACIENTE* aux) {
    if(aux != NULL) {
        printf("Nome: %s, ", aux->nome);
        printf("ID: %d\n", aux->id);
    }
    else {
        printf("Paciente nao existe ou nao ha memoria suficiente para possibilitar sua impressao");
    }
}
void paciente_imprimir_lista(PACIENTE* aux) {
    if(aux != NULL) {
        printf("| Nome: %s\n", aux->nome);
        printf("| ID: %d\n", aux->id);
        historico_consultar(aux->procedimentos);
        printf("--------------------------\n");
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

char* paciente_obter_copia_nome(PACIENTE* aux) {
    char *nome = (char *)malloc(TAM_NOME * sizeof(char));
    strcpy(nome, aux->nome);
    if (aux != NULL) return nome;
    return "";
}

bool paciente_deletar_copia_nome(char** nome) {
    if (nome != NULL && *nome != NULL) {
        free(*nome);
        *nome = NULL;
        return true;
    }
    return false;
}

HISTORICO* paciente_obter_historico(PACIENTE* aux) {
    if (aux != NULL) return aux->procedimentos;
    return NULL;
}

void paciente_consultar_historico(PACIENTE* aux) {
    if (aux == NULL) return;
    if (aux->procedimentos != NULL) {
        historico_consultar(aux->procedimentos);
    }
}

bool paciente_adicionar_procedimento(PACIENTE* aux, PROCEDIMENTO* procedimento) {
    if (aux == NULL || procedimento == NULL) {
        return false;
    }

    if (inserir_procedimento(aux->procedimentos, procedimento)) {
        return true;
    }

    free(procedimento);
    return false;
}

PROCEDIMENTO* paciente_desfazer_procedimento(PACIENTE* aux) {
    if(aux != NULL) {
        PROCEDIMENTO* p = desfazer_procedimento(aux->procedimentos);
        return p;
    }
    return NULL;
}
