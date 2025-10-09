// escolhemos uma aplicação sequencial, visto que a quantidade máxima de históricos é pequena e é mais simples de ser implementado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

typedef struct historico {
    PROCEDIMENTO* procedimentos[MAX_PROCEDIMENTOS];
    int tamanho;
} HISTORICO;

typedef struct procedimento {
    char descricao[MAX_DESCRICAO];
} PROCEDIMENTO;

HISTORICO* historico_criar(void){
    HISTORICO* h = (HISTORICO*) malloc(sizeof(HISTORICO));

    if(h != NULL){
        h->tamanho = 0;
        for(int i = 0; i < MAX_PROCEDIMENTOS; i++){ // Inicializa todas as posições como NULL
            h->procedimentos[i] = NULL;
        }
    }
    return h;
}

bool historico_apagar(HISTORICO** h){
    if(h != NULL && *h != NULL){
        for(int i = 0; i < (*h)->tamanho; i++){
            free((*h)->procedimentos[i]);
        }
        free(h);
        *h = NULL;
        return true;
    }
    return false;
}

bool historico_vazio(HISTORICO* h){
    if(h != NULL){
        return((h->tamanho ==0) ? true : false);
        return false;
    }
}

bool historico_cheio(HISTORICO* h){
    if(h != NULL){
        return((h->tamanho == MAX_PROCEDIMENTOS) ? true : false);
        return false;
    }
}

int historico_tamanho(HISTORICO* h){
    return ((h != NULL) ? h->tamanho : -1);
}

bool inserir_procedimento(HISTORICO* h, PROCEDIMENTO* p){
    if(h != NULL && p != NULL && !historico_cheio(h)){
        h->procedimentos[h->tamanho] = p;
        h->tamanho++;
        return true;
    }
    return false;
}

PROCEDIMENTO* desfazer_procedimento(HISTORICO* h){
    PROCEDIMENTO* i;
    if(h != NULL && !historico_vazio(h)){
        h->tamanho--;
        i = h->procedimentos[h->tamanho];
        h->procedimentos[h->tamanho] = NULL;
        return i;
    }
    return NULL;
}

void historico_consultar(HISTORICO* h){
    if(h != NULL && !historico_vazio(h)){
        printf("| Historico de procedimentos:\n");
        for(int i = h->tamanho - 1; i >= 0; i--){
            printf("| - %s\n", h->procedimentos[i]->descricao);
        }
    } else {
        printf("Historico vazio.\n");
    }
}

PROCEDIMENTO* historico_obter_procedimento_por_posicao(HISTORICO* h, int pos){
    if(h == NULL || pos < 0 || pos >= h->tamanho){
        return NULL;
    }
    return h->procedimentos[pos];
}

