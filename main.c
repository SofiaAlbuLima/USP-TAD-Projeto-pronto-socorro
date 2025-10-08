/* TRABALHO 1 DA DISCIPLINA DE ALGORITMOS E ESTRUTURAS DE DADOS
Alunos:
João Pedro Boaretto, nUSP: 
Lorena Borges, nUSP: 16883652
Sofia Lima, nUSP: 
*/

#include <stdio.h>
#include <stdbool.h>
#include "historico.h" // não sei se o include vai funcionar da forma que está, porque o historico.h está em outro diretório
                       // e tem que dar include nos outros TADs também, talvez quando acabarmos todos.FAltam: fila de espera,
                       // banco de dados e o TAD IO, de persistẽncia dos dados
#define TAM_NOME 101

int menu();
void registrar_paciente();
void registrar_obito();
void adicionar_procedimento_paciente();
void desfazer_procedimento_paciente();
void chamar_paciente_atendimento();
void mostrar_fila_de_espera();

int main () {
    int acao;
    // precisa abrir o arquivo do banco de dados, e quando isso acontecer, colocar o banco de dados numa lista encadeada
    // como LISTA* registro = criar_lista();
    // ai depois if(LOAD(**)
    HISTORICO* H;
    
    while (true) {
        acao = menu();
        switch (acao) {
            case 1: registrar_paciente();
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
            case 7: consultar_historico(H);
                break;
            case 8:
                printf("\nSaindo do programa...\n");
                // precisa salvar na memória
                return 0;
                break;
            default:
                printf("\nFuncionalidade inexistente. Escolha entre as opções abaixo:\n");
        }
    }
    return 0;
}

int menu(){
    int aux;
    printf("\n1. Registrar paciente\n");
    printf("2. Registrar óbito de paciente\n");
    printf("3. Adicionar procedimento ao histórico médico\n");
    printf("4. Desfazer procedimento do histórico médico\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar histórico do paciente\n");
    printf("8. Sair\n");
    scanf(" %d", &aux);
    return aux;
}

void registrar_paciente() {

}

void registrar_obito();
void adicionar_procedimento_paciente();
void desfazer_procedimento_paciente();
void chamar_paciente_atendimento();
void mostrar_fila_de_espera();
void mostrar_historico_paciente();