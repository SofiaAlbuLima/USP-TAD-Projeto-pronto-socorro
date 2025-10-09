/* TRABALHO 1 DA DISCIPLINA DE ALGORITMOS E ESTRUTURAS DE DADOS

Alunos:
João Pedro Boaretto, nUSP:  16876293
Lorena Borges, nUSP: 16883652
Sofia Albuquerque Lima, nUSP: 16900810

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./TADs/lista.h"
#include "./TADs/fila.h"
#include "./TADs/IO.h"

#define TAM_NOME 101

int menu();
void registrar_paciente(LISTA* registro, FILA* fila);
void registrar_obito();
void adicionar_procedimento_paciente(LISTA* registro);
void desfazer_procedimento_paciente();
void chamar_paciente_atendimento();
void mostrar_fila_de_espera();
void mostrar_historico_paciente();
void sair();

LISTA* registro;
FILA* fila;

int main () {
    int acao;
    registro = NULL;
    fila = NULL;

    if (!LOAD(&registro, &fila)) {
        printf("Falha ao carregar os dados. Iniciando estruturas vazias.\n");
    }

    if (registro == NULL) {
        registro = lista_criar();
    }
    if (fila == NULL) {
        fila = fila_criar();
    }

    if (registro == NULL || fila == NULL) {
        printf("Erro ao inicializar estruturas principais.\n");
        return 1;
    }

    
    while (true) {
        acao = menu();
        switch (acao) {
            case 1: registrar_paciente(registro, fila);
                break;
            case 2: registrar_obito();
                break;
            case 3: adicionar_procedimento_paciente(registro);
                break;
            case 4: desfazer_procedimento_paciente();
                break;
            case 5: chamar_paciente_atendimento();
                break;
            case 6: mostrar_fila_de_espera();
                break;
            case 7: mostrar_historico_paciente();
                break;
            case 8:
                sair();
                return 0;
            default:
                printf("\nFuncionalidade inexistente. Escolha entre as opcoes abaixo:\n");
        }
    }
    return 0;
}

int menu(){
    int aux;
    printf("\n[1] Registrar paciente\n");
    printf("[2] Registrar obito de paciente\n");
    printf("[3] Adicionar procedimento ao historico medico\n");
    printf("[4] Desfazer procedimento do historico medico\n");
    printf("[5] Chamar paciente para atendimento\n");
    printf("[6] Mostrar fila de espera\n");
    printf("[7] Mostrar historico do paciente\n");
    printf("[8] Sair\n\n");
    scanf(" %d", &aux);
    return aux;
}

void registrar_paciente(LISTA* registro, FILA* fila) {
    char nome[TAM_NOME];
    int ID;
    printf("\nDigite o nome do paciente (maximo de 100 caracteres): ");
    scanf(" %[^\n]s", nome);
    printf("Digite o ID do paciente (numero inteiro): ");
    scanf(" %d", &ID);

    if(paciente_buscar(registro, ID) != NULL){
        printf("\nID ja existente. Tente novamente.\n");
        return;
    }else{
        PACIENTE* p = paciente_criar(nome, ID);
        bool cadastro = paciente_cadastrar(registro, p);
        if(!cadastro){
            printf("\nErro no cadastro do paciente. Tente novamente.\n");
            return;
        }else{
            bool espera = fila_inserir(fila, p);
            if(!espera){
                printf("\nFila cheia. Paciente nao cadastrado na fila de espera.\n");
            }else{
                printf("\nPaciente registrado com sucesso!\n");
            }
            return;
        }
    }
}

void registrar_obito() {
    printf("Funcao registrar_obito ainda nao implementada.\n");
}

void adicionar_procedimento_paciente(LISTA* registro) {
    if (registro == NULL) {
        printf("Registro de pacientes indisponivel.\n");
        return;
    }

    int id_paciente;
    printf("Digite o ID do paciente: ");
    if (scanf(" %d", &id_paciente) != 1) {
        printf("Entrada invalida para ID.\n");
        return;
    }

    PACIENTE* paciente = paciente_buscar(registro, id_paciente);
    if (paciente == NULL) {
        printf("Paciente com ID %d nao encontrado.\n", id_paciente);
        return;
    }

    HISTORICO* historico = paciente_obter_historico(paciente);
    if (historico == NULL) {
        printf("Historico do paciente nao disponivel.\n");
        return;
    }

    if (historico_cheio(historico)) {
        printf("Historico do paciente esta cheio. Nao e possivel adicionar novos procedimentos.\n");
        return;
    }

    char descricao[MAX_DESCRICAO];
    printf("Descricao do procedimento (maximo de %d caracteres): ", MAX_DESCRICAO - 1);
    if (scanf(" %100[^\n]", descricao) != 1) {
        printf("Descricao invalida.\n");
        return;
    }

    PROCEDIMENTO* procedimento = procedimento_criar(descricao);
    if (procedimento == NULL) {
        printf("Nao foi possivel registrar o procedimento.\n");
        return;
    }

    if (!paciente_adicionar_procedimento(paciente, procedimento)) {
        printf("Erro ao adicionar procedimento ao historico do paciente.\n");
        return;
    }

    printf("Procedimento adicionado com sucesso ao paciente %d.\n", id_paciente);
}

void desfazer_procedimento_paciente() {
    if (registro == NULL) {
        printf("Registro de pacientes indisponivel.\n");
        return;
    }

    int id_paciente;
    printf("Digite o ID do paciente: ");
    if (scanf(" %d", &id_paciente) != 1) {
        printf("Entrada invalida para ID.\n");
        return;
    }

    PACIENTE* paciente = paciente_buscar(registro, id_paciente);
    if (paciente == NULL) {
        printf("Paciente com ID %d nao encontrado.\n", id_paciente);
        return;
    }

    HISTORICO* historico = paciente_obter_historico(paciente);
    if (historico == NULL) {
        printf("Historico do paciente nao disponivel.\n");
        return;
    }

    if (historico_vazio(historico)) {
        printf("Historico do paciente nao possui procedimentos para desfazer.\n");
        return;
    }

    PROCEDIMENTO* procedimento = paciente_desfazer_procedimento(paciente);
    if (procedimento == NULL) {
        printf("Nao foi possivel desfazer o ultimo procedimento.\n");
        return;
    }

    const char* descricao = procedimento_obter_descricao(procedimento);
    printf("Procedimento removido: %s\n", (descricao != NULL) ? descricao : "(descricao indisponivel)");
    free(procedimento);
}

void chamar_paciente_atendimento() {
    printf("Funcao chamar_paciente_atendimento ainda nao implementada.\n");
}

void mostrar_fila_de_espera() {
    if (fila != NULL) {
        fila_imprimir(fila);
    } else {
        printf("Fila nao existe.\n");
    }
}

void mostrar_historico_paciente() {
    
}

void sair(){
    printf("\nSalvando dados e encerrando o programa...\n");
        if (SAVE(registro, fila)) {
            printf("Dados salvos com sucesso.\n");
        } else {
            printf("Falha ao salvar os dados. Verifique o armazenamento.\n");
        }
        lista_destruir(registro);
        registro = NULL;
        fila_apagar(&fila);
        return;
}
