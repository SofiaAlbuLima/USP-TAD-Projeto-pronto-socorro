#include <stdio.h>
#include <stdlib.h>
#include "IO.h"

bool SAVE(LISTA *lista, FILA *fila) {
    FILE* arquivo = fopen("hospital_data.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para salvar os dados");
        return false;
    }

    // SALVAR LISTA DE PACIENTES E HISTÓRICOS
    int n_pacientes_lista = lista_tamanho(lista);
    fwrite(&n_pacientes_lista, sizeof(int), 1, arquivo);

    for (int i = 0; i < n_pacientes_lista; i++) {
        PACIENTE* p = lista_obter_paciente_na_posicao(lista, i);
        
        int id = paciente_obter_ID(p);
        char* nome = paciente_obter_nome(p);
        
        fwrite(&id, sizeof(int), 1, arquivo);
        fwrite(nome, sizeof(char), 100, arquivo);

        HISTORICO* h = paciente_obter_historico(p);
        int total_procedimentos = historico_tamanho(h);
        fwrite(&total_procedimentos, sizeof(int), 1, arquivo);

        for (int j = 0; j < total_procedimentos; j++) {
            PROCEDIMENTO* proc = historico_obter_procedimento_na_posicao(h, j);
            fwrite(proc, sizeof(PROCEDIMENTO*), 1, arquivo);
        }
    }

    // SALVAR FILA DE ESPERA (apenas IDs)
    int total_pacientes_fila = fila_tamanho(fila);
    fwrite(&total_pacientes_fila, sizeof(int), 1, arquivo);

    FILA* fila_aux = fila_criar();
    while (!fila_vazia(fila)) {
        PACIENTE* p = fila_atender(fila);
        int id_paciente = paciente_obter_ID(p);
        
        fwrite(&id_paciente, sizeof(int), 1, arquivo);
        fila_inserir(fila_aux, p);
    }
    while(!fila_vazia(fila_aux)) {
        fila_inserir(fila, fila_atender(fila_aux));
    }
    fila_apagar(&fila_aux);

    fclose(arquivo);
    return true; // Sucesso!
}


bool LOAD(LISTA **lista, FILA **fila) {
    *lista = lista_criar();
    *fila = fila_criar();

    FILE* arquivo = fopen("hospital_data.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com sistema vazio.\n");
        return true; // Retorna sucesso com as estruturas vazias.
    }

    // CARREGAR LISTA DE PACIENTES E HISTÓRICOS
    int n_pacientes_lista;
    fread(&n_pacientes_lista, sizeof(int), 1, arquivo);

    for (int i = 0; i < n_pacientes_lista; i++) {
        int id;
        char nome[100];
        fread(&id, sizeof(int), 1, arquivo);
        fread(nome, sizeof(char), 100, arquivo);

        PACIENTE* p = paciente_criar(nome, id);

        HISTORICO* h = paciente_obter_historico(p);
        int total_procedimentos;
        fread(&total_procedimentos, sizeof(int), 1, arquivo);

        for (int j = 0; j < total_procedimentos; j++) {
            PROCEDIMENTO* proc = (PROCEDIMENTO*) malloc(sizeof(PROCEDIMENTO*));
            fread(proc, sizeof(PROCEDIMENTO*), 1, arquivo);
            inserir_procedimento(h, proc);
        }
        
        paciente_cadastrar(*lista, p);
    }

    // RECONSTRUIR FILA DE ESPERA
    int total_pacientes_fila;
    fread(&total_pacientes_fila, sizeof(int), 1, arquivo);
    
    for (int i = 0; i < total_pacientes_fila; i++) {
        int id_paciente;
        fread(&id_paciente, sizeof(int), 1, arquivo);
        
        PACIENTE* p = paciente_buscar(*lista, id_paciente);
        if (p != NULL) {
            fila_inserir(*fila, p);
        }
    }

    fclose(arquivo);
    return true; // Sucesso!
}