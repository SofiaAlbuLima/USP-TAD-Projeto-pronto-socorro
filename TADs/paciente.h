#ifndef PACIENTE_H
	#define PACIENTE_H

	#include "historico.h"
	#include <stdbool.h>
	
	#define TAM_NOME 101

	typedef struct paciente_ PACIENTE;

	PACIENTE* paciente_criar(char string[], int i);
	bool paciente_apagar(PACIENTE** aux);
	void paciente_imprimir_fila(PACIENTE* aux);
	void paciente_imprimir_lista(PACIENTE* aux);
	int paciente_obter_ID(PACIENTE* aux);
    void paciente_imprimir_nome(PACIENTE* aux);
	char* paciente_obter_nome(PACIENTE* aux);
	HISTORICO* paciente_obter_historico(PACIENTE* aux);
    void paciente_consultar_historico(PACIENTE* aux);
	bool paciente_adicionar_procedimento(PACIENTE* aux, PROCEDIMENTO* procedimento); // do histórico médico
    PROCEDIMENTO* paciente_desfazer_procedimento(PACIENTE* aux); // do histórico médico
#endif