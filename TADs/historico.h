#ifndef HISTORICO_H
	#define HISTORICO_H

    #include <stdbool.h>

    typedef struct historico HISTORICO;
    typedef struct procedimento PROCEDIMENTO;

    #define MAX_PROCEDIMENTOS 10
    #define MAX_DESCRICAO 101

    HISTORICO* historico_criar();
    bool historico_apagar(HISTORICO** h);

    bool historico_vazio(HISTORICO* h);
    bool historico_cheio(HISTORICO* h);
    int historico_tamanho(HISTORICO* h);

    bool inserir_procedimento(HISTORICO* h, PROCEDIMENTO* p);
    PROCEDIMENTO* desfazer_procedimento(HISTORICO* h);

    void historico_consultar(HISTORICO* h); 
    PROCEDIMENTO* historico_obter_procedimento_por_posicao(HISTORICO* h, int pos);
    PROCEDIMENTO* procedimento_criar(const char descricao[]);
    const char* procedimento_obter_descricao(PROCEDIMENTO* procedimento);
#endif
