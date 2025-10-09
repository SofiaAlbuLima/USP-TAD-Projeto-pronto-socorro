/* escolhemos uma implementação sequencial por ser mais simples de controlar o tamanho máximo, e porque, no caso
do problema, há apenas uma fila de espera, então não consome tanta memória constantemente. Além disso,
escolhemos uma implementação circular para melhorar a sua eficiência, ao evitar a necessidade do deslocamento
do vetor inteiro toda vez que alguém saísse da fila.
*/
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_ {
    PACIENTE *fila_de_espera[TAM_FILA];
    int inicio; // posição a ser retirada
    int fim; // posição de inserção de pacientes
    int tamanho;
};

FILA *fila_criar() {
    FILA *fila = (FILA*) malloc(sizeof(FILA));
    if (fila != NULL) {
        fila->inicio = 0;
        fila->fim = 0;
        fila->tamanho = 0;
    }
    return(fila);
}

bool fila_inserir(FILA *fila, PACIENTE *p) {
    if(fila != NULL && !fila_cheia(fila)) {
        fila->fila_de_espera[fila->fim] = p;
        fila->fim = ((fila->fim)+1)%TAM_FILA;
        fila->tamanho++;
        return true;
    }
    return false;
}

PACIENTE* fila_atender(FILA *fila) {
    if(fila != NULL && !fila_vazia(fila)) {
        PACIENTE *p = fila->fila_de_espera[fila->inicio];
        fila->fila_de_espera[fila->inicio] = NULL;
        fila->inicio = ((fila->inicio)+1)%TAM_FILA;
        fila->tamanho--;
        return(p);
    }
    return(NULL);
}

void fila_apagar(FILA **fila) {
    free(*fila);
    *fila = NULL;
}

PACIENTE* fila_proximo_atender(FILA *fila) {
    if(fila != NULL && !fila_vazia(fila)) {
        PACIENTE *p = fila->fila_de_espera[fila->inicio];
        return(p);
    }
    return(NULL);
}

int fila_tamanho(FILA *fila) {
    if(fila != NULL) return (fila->tamanho);
    else return (-1);
}

bool fila_vazia(FILA *fila) {
    if (fila != NULL) {
        return (fila->tamanho == 0);
    }
    return true;
}

bool fila_cheia(FILA *fila) {
    if (fila != NULL) return (fila->tamanho == TAM_FILA);
    else return true;
}

void fila_imprimir(FILA *fila) {
    if(fila != NULL) {
        int posicao = fila->inicio;
        for(int i=0; i<fila->tamanho; i++) {
            printf("%d- ", i+1);
            paciente_imprimir(fila->fila_de_espera[posicao]);
            posicao = (posicao+1)%TAM_FILA;
        }
    }
}

