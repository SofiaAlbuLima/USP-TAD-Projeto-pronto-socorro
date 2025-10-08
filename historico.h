#ifndef HISTORICO_H
	#define HISTORICO_H

    #include <stdbool.h>

    typedef struct historico HISTORICO;
    typedef struct procedimento PROCEDIMENTO;

    #define MAX_PROCEDIMENTOS 10
    #define MAX_DESCRICAO 100

    HISTORICO* criar_historico();
    void apagar_historico(HISTORICO** h);

    bool historico_vazio(HISTORICO* h);
    bool historico_cheio(HISTORICO* h);
    int pilha_tamanho(HISTORICO* h);

    bool inserir_procedimento(HISTORICO* h, PROCEDIMENTO* p);
    PROCEDIMENTO* desfazer_procedimento(HISTORICO* h);

    void consultar_historico(HISTORICO* h); 
#endif