#ifndef PACIENTE_H
	#define PACIENTE_H
	
	#include <stdbool.h>

	typedef struct paciente_ PACIENTE;

	PACIENTE* paciente_criar(PACIENTE paciente);
	bool paciente_apagar();
	void paciente_imprimir();
	int paciente_obter_ID();
    char* paciente_obter_name();
    HISTORICO* paciente_consultar_historico();
	bool paciente_adicionar_procedimento(); // do histórico médico
    bool paciente_desfazer_procedimento(); // do histórico médico

#endif