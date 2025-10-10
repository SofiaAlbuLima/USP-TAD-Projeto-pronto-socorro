/* TRABALHO 1 DA DISCIPLINA DE ALGORITMOS E ESTRUTURAS DE DADOS

Alunos:
João Pedro Boaretto, nUSP:  16876293
Lorena Moreira Borges, nUSP: 16883652
Sofia Albuquerque Lima, nUSP: 16900810

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
bool sair();

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
    
    bool flag;
    while (true) {
        flag = false;
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
                flag = sair();
                if(flag == false) return 0;
                break;
            default:
                printf("\nFuncionalidade inexistente. Escolha entre as opcoes abaixo:\n");
        }
    }
    return 0;
}

int menu(){
    int aux;
    printf("\n\n[1] Registrar paciente\n");
    printf("[2] Registrar obito de paciente\n");
    printf("[3] Adicionar procedimento ao historico medico\n");
    printf("[4] Desfazer procedimento do historico medico\n");
    printf("[5] Chamar paciente para atendimento\n");
    printf("[6] Mostrar fila de espera\n");
    printf("[7] Mostrar historico do paciente\n");
    printf("[8] Sair\n\n");
    printf("Digite o numero da operacao desejada [1-8]: ");
    scanf(" %d", &aux);
    return aux;
}

void registrar_paciente(LISTA* registro, FILA* fila) {
    char nome[TAM_NOME];
    int ID;
    printf("\nDigite o nome do paciente (maximo de 100 caracteres): ");
    scanf(" %[^\n\r]s", nome);
    printf("Digite o ID do paciente (numero inteiro): ");
    scanf(" %d", &ID);
    
    if(paciente_buscar(registro, ID) != NULL){
        if(fila_buscar(fila, ID)){
            printf("\nPaciente ja esta na fila de espera.\n");
            return;
        } else {
            printf("\nID ja existente. Colocando na fila.\n");
        }
    }else{
        PACIENTE* p = paciente_criar(nome, ID);
        bool cadastro = paciente_cadastrar(registro, p);
        if(!cadastro){
            printf("\nErro no cadastro do paciente. Tente novamente.\n");
        }
    }
    bool espera = fila_inserir(fila, paciente_buscar(registro, ID));
    if(!espera){
        printf("\nFila cheia. Paciente nao cadastrado na fila de espera.\n");
    }else{
        printf("\nPaciente registrado com sucesso!\n");
    }
    return;
}

void registrar_obito() {
    printf("\nQual paciente voce quer registrar o obito? (digite seu ID)\n");
    int ID_obito; scanf(" %d", &ID_obito);
    if (paciente_buscar(registro, ID_obito) == NULL) {
        printf("\nPaciente nao encontrado. Verifique o ID e tente novamente.\n");
        return;
    } else {
        if(fila_buscar(fila, ID_obito)) {
            printf("\nO paciente a ser registrado como obito esta na fila de espera. Nao e possivel registrar obito para pacientes na fila de espera.\n");
        }else{
            PACIENTE* removido = obito_registrar(registro, ID_obito);
            int ID_falecido = paciente_obter_ID(removido);

            if (removido == NULL) {
                printf("\nErro ao registrar obito no banco de dados. Tente novamente.\n");
            } else {
                printf("\nObito registrado com sucesso para o paciente ");
                paciente_imprimir_nome(removido);
                printf(" (ID: %d).\n", ID_falecido);
                paciente_apagar(&removido);
            }
        }
    }
    return;
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

    if(!procedimento_apagar(&procedimento)) {
        printf("Procedimento ainda na memoria! Memory leak\n");
    }
}

void chamar_paciente_atendimento() {
    PACIENTE* atendido = fila_atender(fila);
    if (atendido == NULL) {
        printf("\nFila de espera vazia. Nenhum paciente para atender.\n");
        return;
    } else {
        printf("\nPaciente ");
        paciente_imprimir_nome(atendido);
        printf(" (ID: %d) chamado para atendimento.\n", paciente_obter_ID(atendido));
        
        if (fila_proximo_atender(fila) != NULL) {
            printf("O proximo Paciente: ");
            paciente_imprimir_nome(fila_proximo_atender(fila));
            printf(" (ID: %d).\n", paciente_obter_ID(fila_proximo_atender(fila)));
        } else {
            printf("Sem proximo paciente.\n");
        }
        
        return;
    }
}

void mostrar_fila_de_espera() {
    if (fila != NULL) {
        if (fila_vazia(fila)) {
            printf("\nFila de espera vazia.\n");
            return;
        }
        printf("\nFila de espera atual:\n");
        fila_imprimir(fila);
    } else {
        printf("\nFila nao existe.\n");
    }
}

void mostrar_historico_paciente() {
    int ID_historico;
    printf("\nDigite o ID do paciente cujo historico voce quer consultar: ");
    scanf(" %d", &ID_historico);
    PACIENTE* paciente = paciente_buscar(registro, ID_historico);
    if (paciente == NULL) {
        printf("\nPaciente nao encontrado. Verifique o ID e tente novamente.\n");
        return;
    } else {
        paciente_consultar_historico(paciente);
        return;
    }
}

bool sair(){
    bool flag;
    printf("\nSalvando dados e encerrando o programa...\n");
        if (SAVE(registro, fila)) {
            printf("Dados salvos com sucesso.\n");

            lista_destruir(registro);
            registro = NULL;
            fila_apagar(&fila);

            flag = false;
        } else {
            printf("Falha ao salvar os dados. Verifique o armazenamento e tente novamente.\n");
            flag = true;
        }
        return flag;
}