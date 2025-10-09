#ifndef FILA_H
	#define FILA_H
	#include "paciente.h"
	#include <stdbool.h>
	#include <stdio.h>

	typedef struct fila_ FILA;

	#define TAM_FILA 15

	FILA *fila_criar();
	bool fila_inserir(FILA *fila, PACIENTE *p);
	PACIENTE *fila_atender(FILA *fila); // fila_remover
	void fila_apagar(FILA **fila);

	PACIENTE *fila_proximo_atender(FILA *fila); // fila_frente
	int fila_tamanho(FILA *fila);
	bool fila_vazia(FILA *fila);
	bool fila_cheia(FILA *fila);
	void fila_imprimir(FILA *fila);

#endif