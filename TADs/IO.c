#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

static bool salvar_string(FILE* arquivo, const char* texto) {
    int tamanho = 0;
    if (texto != NULL) {
        tamanho = (int) strlen(texto);
    }

    if (fwrite(&tamanho, sizeof(int), 1, arquivo) != 1) {
        return false;
    }

    if (tamanho > 0 && fwrite(texto, sizeof(char), tamanho, arquivo) != (size_t) tamanho) {
        return false;
    }

    return true;
}

static bool carregar_string(FILE* arquivo, char** texto) {
    int tamanho = 0;
    if (fread(&tamanho, sizeof(int), 1, arquivo) != 1) {
        return false;
    }

    if (tamanho < 0) {
        return false;
    }

    char* buffer = NULL;
    size_t bytes = (size_t) tamanho;

    if (bytes > 0) {
        buffer = (char*) calloc(bytes + 1, sizeof(char));
        if (buffer == NULL) {
            return false;
        }

        if (fread(buffer, sizeof(char), bytes, arquivo) != bytes) {
            free(buffer);
            return false;
        }
    } else {
        buffer = (char*) calloc(1, sizeof(char));
        if (buffer == NULL) {
            return false;
        }
    }

    if (texto != NULL) {
        *texto = buffer;
    } else {
        free(buffer);
    }

    return true;
}

bool SAVE(LISTA *lista, FILA *fila) {
    FILE* arquivo = fopen("hospital_data.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para salvar os dados");
        return false;
    }

    int n_pacientes_lista = 0;
    if (lista != NULL) {
        n_pacientes_lista = lista_tamanho(lista);
        if (n_pacientes_lista < 0) {
            n_pacientes_lista = 0;
        }
    }

    if (fwrite(&n_pacientes_lista, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return false;
    }

    for (int i = 0; i < n_pacientes_lista; i++) {
        PACIENTE* paciente = listar_pacientes_por_posicao(lista, i);
        if (paciente == NULL) {
            fclose(arquivo);
            return false;
        }

        int id = paciente_obter_ID(paciente);
        if (fwrite(&id, sizeof(int), 1, arquivo) != 1) {
            fclose(arquivo);
            return false;
        }

        if (!salvar_string(arquivo, paciente_obter_nome(paciente))) {
            fclose(arquivo);
            return false;
        }

        HISTORICO* historico = paciente_obter_historico(paciente);
        int total_procedimentos = historico_tamanho(historico);
        if (total_procedimentos < 0) {
            total_procedimentos = 0;
        }

        if (fwrite(&total_procedimentos, sizeof(int), 1, arquivo) != 1) {
            fclose(arquivo);
            return false;
        }

        for (int j = 0; j < total_procedimentos; j++) {
            PROCEDIMENTO* procedimento = historico_obter_procedimento_por_posicao(historico, j);
            const char* descricao = procedimento_obter_descricao(procedimento);
            if (!salvar_string(arquivo, descricao)) {
                fclose(arquivo);
                return false;
            }
        }
    }

    int total_pacientes_fila = 0;
    if (fila != NULL) {
        total_pacientes_fila = fila_tamanho(fila);
        if (total_pacientes_fila < 0) {
            total_pacientes_fila = 0;
        }
    }

    if (fwrite(&total_pacientes_fila, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return false;
    }

    if (fila != NULL && total_pacientes_fila > 0) {
        PACIENTE** buffer = (PACIENTE**) malloc(sizeof(PACIENTE*) * (size_t) total_pacientes_fila);
        if (buffer == NULL) {
            fclose(arquivo);
            return false;
        }

        for (int i = 0; i < total_pacientes_fila; i++) {
            buffer[i] = fila_atender(fila);
            PACIENTE* p = buffer[i];
            int id_paciente = (p != NULL) ? paciente_obter_ID(p) : -1;
            if (fwrite(&id_paciente, sizeof(int), 1, arquivo) != 1) {
                free(buffer);
                fclose(arquivo);
                return false;
            }
        }

        for (int i = 0; i < total_pacientes_fila; i++) {
            if (buffer[i] != NULL) {
                fila_inserir(fila, buffer[i]);
            }
        }

        free(buffer);
    }

    fclose(arquivo);
    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if (lista == NULL || fila == NULL) {
        return false;
    }

    if (*lista != NULL) {
        lista_destruir(*lista);
        *lista = NULL;
    }

    if (*fila != NULL) {
        fila_apagar(fila);
    }

    FILE* arquivo = fopen("hospital_data.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com sistema vazio.\n");
        *lista = lista_criar();
        *fila = fila_criar();
        return (*lista != NULL && *fila != NULL);
    }

    LISTA* nova_lista = lista_criar();
    FILA* nova_fila = fila_criar();
    if (nova_lista == NULL || nova_fila == NULL) {
        if (nova_lista != NULL) {
            lista_destruir(nova_lista);
        }
        if (nova_fila != NULL) {
            fila_apagar(&nova_fila);
        }
        fclose(arquivo);
        return false;
    }

    int n_pacientes_lista = 0;
    if (fread(&n_pacientes_lista, sizeof(int), 1, arquivo) != 1 || n_pacientes_lista < 0) {
        lista_destruir(nova_lista);
        fila_apagar(&nova_fila);
        fclose(arquivo);
        return false;
    }

    for (int i = 0; i < n_pacientes_lista; i++) {
        int id = 0;
        if (fread(&id, sizeof(int), 1, arquivo) != 1) {
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }

        char* nome_lido = NULL;
        if (!carregar_string(arquivo, &nome_lido)) {
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }

        PACIENTE* paciente = paciente_criar((nome_lido != NULL) ? nome_lido : "", id);
        free(nome_lido);
        if (paciente == NULL) {
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }

        HISTORICO* historico = paciente_obter_historico(paciente);
        int total_procedimentos = 0;
        if (fread(&total_procedimentos, sizeof(int), 1, arquivo) != 1 || total_procedimentos < 0 || total_procedimentos > MAX_PROCEDIMENTOS) {
            paciente_apagar(&paciente);
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }

        for (int j = 0; j < total_procedimentos; j++) {
            char* descricao_lida = NULL;
            if (!carregar_string(arquivo, &descricao_lida)) {
                paciente_apagar(&paciente);
                lista_destruir(nova_lista);
                fila_apagar(&nova_fila);
                fclose(arquivo);
                return false;
            }

            PROCEDIMENTO* procedimento = procedimento_criar((descricao_lida != NULL) ? descricao_lida : "");
            free(descricao_lida);
            if (procedimento == NULL || !inserir_procedimento(historico, procedimento)) {
                free(procedimento);
                paciente_apagar(&paciente);
                lista_destruir(nova_lista);
                fila_apagar(&nova_fila);
                fclose(arquivo);
                return false;
            }
        }

        if (!paciente_cadastrar(nova_lista, paciente)) {
            paciente_apagar(&paciente);
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }
    }

    int total_pacientes_fila = 0;
    if (fread(&total_pacientes_fila, sizeof(int), 1, arquivo) != 1 || total_pacientes_fila < 0) {
        lista_destruir(nova_lista);
        fila_apagar(&nova_fila);
        fclose(arquivo);
        return false;
    }

    for (int i = 0; i < total_pacientes_fila; i++) {
        int id_paciente = 0;
        if (fread(&id_paciente, sizeof(int), 1, arquivo) != 1) {
            lista_destruir(nova_lista);
            fila_apagar(&nova_fila);
            fclose(arquivo);
            return false;
        }

        PACIENTE* paciente = paciente_buscar(nova_lista, id_paciente);
        if (paciente != NULL) {
            if (!fila_inserir(nova_fila, paciente)) {
                lista_destruir(nova_lista);
                fila_apagar(&nova_fila);
                fclose(arquivo);
                return false;
            }
        }
    }

    fclose(arquivo);

    *lista = nova_lista;
    *fila = nova_fila;
    return true;
}
