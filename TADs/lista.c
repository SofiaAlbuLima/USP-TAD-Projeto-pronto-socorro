#include <stdio.h>
	#include "paciente.h"
	#include "historico.h"

typedef struct no_{
    PACIENTE *paciente;
    struct no_ *prox; 
}NO;

typedef struct lista{
    NO *inicio;
    NO *fim;
    int tamanho;
}LISTA;

LISTA* lista_criar(){
    LISTA *l = (LISTA*) malloc(sizeof(LISTA));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}


void paciente_cadastrar(LISTA* l, PACIENTE* p){
    if((!lista_cheia(l)) && (l != NULL)){
        NO* pnovo = (NO*) malloc(sizeof(NO));
        pnovo->paciente = p;
        pnovo->prox = NULL;

        if(l->tamanho == 0){
            l->inicio = pnovo;
        } else {
            l->fim->prox = pnovo;
        }
        l->fim = pnovo;
        l->tamanho++;

        return true;
    }else{
        return false;
    }
}
PACIENTE* paciente_buscar(LISTA* l, int chave){
    if((l != NULL) && (l->tamanho > 0)){
        NO* p = l->inicio;
        while(p != NULL){
            if(paciente_obter_ID(p->paciente) == chave){
                return p->paciente;
            }
            p = p->prox;
        }
    }
    return NULL;
}
PACIENTE* obito_registrar(LISTA* l, int chave){
    if (l != NULL){
        NO *p = l->inicio; NO *aux = NULL;
        while(p != NULL && (paciente_obter_ID(p->paciente)) != chave){
            aux = p;
            p = p->prox;
        }
        if(p != NULL) {
            if(p == l->inicio) { 
                l->inicio = p->prox;
                p->prox = NULL;
            } 
            else {
                aux->prox = p->prox;
                p->prox = NULL;
            }
            if(p == l->fim)
                l->fim = aux;
            PACIENTE *it = p->paciente;
            l->tamanho--; 
            free(p);
            return (it);
        }
    }
    return (NULL);
}
void pacientes_listar(LISTA* l){
    if((l != NULL) && (l->tamanho > 0)){
        NO* p = l->inicio;
        while(p != NULL){
            paciente_imprimir(p->paciente);
            p = p->prox;
        }
    }
}

    int lista_tamanho(LISTA* l){
        if(l != NULL){
            return l->tamanho;
        } else {
            return -1;
        }
    }
    bool lista_vazia(LISTA* l){
        if((l != NULL) && (l->tamanho == 0)){
            return true;
        } else {
            return false;
        }
    }
    bool lista_cheia(LISTA* l){
        if(l != NULL){
            NO* p = (NO*) malloc(sizeof(NO));
            if(p == NULL){
                return true;
            } else {
                free(p);
                return false;
            }
        } else {
            return true;
        }
    }
    void lista_destruir(LISTA* l){
        if(l != NULL){
            NO* p = l->inicio;
            while(p != NULL){
                NO* aux = p;
                p = p->prox;
                paciente_apagar(&(aux->paciente));
                free(aux);
            }
            free(l);
        }
    }