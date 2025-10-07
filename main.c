#include <stdio.h>
#include <stdbool.h>

int menu();

int main () {
    int acao;
    while (true) { // falta abrir arquivo de histórico
        acao = menu();
        switch (acao) {
            case 1: 
                break;
            case 2: 
                break;
            case 3: 
                break;
            case 4: 
                break;
            case 5: 
                break;
            case 6: 
                break;
            case 7: 
                break;
            case 8: 
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