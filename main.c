/* TRABALHO 1 DA DISCIPLINA DE ALGORITMOS E ESTRUTURAS DE DADOS

Alunos:
JoÃ£o Pedro Boaretto, nUSP:  16876293
Lorena Borges, nUSP: 16883652
Sofia Albuquerque Lima, nUSP: 16900810

*/

#include <stdio.h>
#include <stdbool.h>

#include "./TADs/lista.h"
#include "./TADs/fila.h"
#include "./TADs/IO.h"

#define TAM_NOME 101

int menu();
void registrar_paciente(LISTA* registro, FILA* fila);
void registrar_obito();
void adicionar_procedimento_paciente();
void desfazer_procedimento_paciente();
void chamar_paciente_atendimento();
void mostrar_fila_de_espera();
void mostrar_historico_paciente(HISTORICO* H);

/* VariÃ¡veis globais para funÃ§Ãµes auxiliares simples */
LISTA* registro;
FILA* fila;
HISTORICO* H;

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

    H = NULL;
    
    while (true) {
        acao = menu();
        switch (acao) {
            case 1: registrar_paciente(registro, fila);
                break;
            case 2: registrar_obito();
                break;
            case 3: adicionar_procedimento_paciente();
                break;
            case 4: desfazer_procedimento_paciente();
                break;
            case 5: chamar_paciente_atendimento();
                break;
            case 6: mostrar_fila_de_espera();
                break;
            case 7: mostrar_historico_paciente(H);
                break;
            case 8: {
                printf("\nSalvando dados e encerrando o programa...\n");
                if (SAVE(registro, fila)) {
                    printf("Dados salvos com sucesso.\n");
                } else {
                    printf("Falha ao salvar os dados. Verifique o armazenamento.\n");
                }
                lista_destruir(registro);
                registro = NULL;
                fila_apagar(&fila);
                return 0;
            }
            default:
                printf("\nFuncionalidade inexistente. Escolha entre as opÃ§Ãµes abaixo:\n");
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
                printf("\nFila cheia. Paciente nÃ£o cadastrado na fila de espera.\n");
            }else{
                printf("\nPaciente registrado com sucesso!\n");
            }
            return;
        }
    }
}

void registrar_obito();
void adicionar_procedimento_paciente();
void desfazer_procedimento_paciente();
void chamar_paciente_atendimento();

/* ImplementaÃ§Ãµes simples para evitar erro de link */
void mostrar_fila_de_espera() {
    if (fila != NULL) {
        fila_imprimir(fila);
    } else {
        printf("Fila nao existe.\n");
    }
}

void mostrar_historico_paciente(HISTORICO* H_local) {
    if (H_local != NULL) {
        historico_consultar(H_local);
    } else {
        printf("Historico nao disponivel.\n");
    }
}

/* Stubs simples para funcionalidades ainda nÃ£o implementadas */
void registrar_obito() {
    printf("Funcao registrar_obito ainda nao implementada.\n");
}

void adicionar_procedimento_paciente() {
    printf("Funcao adicionar_procedimento_paciente ainda nao implementada.\n");
}

void desfazer_procedimento_paciente() {
    printf("Funcao desfazer_procedimento_paciente ainda nao implementada.\n");
}

void chamar_paciente_atendimento() {
    printf("Funcao chamar_paciente_atendimento ainda nao implementada.\n");
}
