#ifndef LISTA_H
	#define LISTA_H

	#include "paciente.h"
	#include "historico.h"
	#include <stdbool.h>

    typedef struct lista LISTA;
    typedef struct no_ NO;

    LISTA* lista_criar();

    bool paciente_cadastrar(LISTA* l, PACIENTE* p); //lista inserir
    PACIENTE* obito_registrar(LISTA* l, int chave); //lista remover
    PACIENTE* paciente_buscar(LISTA* l, int chave); //lista buscar
    void lista_imprimir(LISTA* l); //lista imprimir

    // Auxiliares IO
    PACIENTE* listar_pacientes_por_posicao(LISTA* l, int pos);

    int lista_tamanho(LISTA* l);
    bool lista_vazia(LISTA* l);
    bool lista_cheia(LISTA* l);
    void lista_destruir(LISTA* l);
    
#endif