//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//---------------------------{ MENU DO ADMIN )---------------------------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "admin.h"
#include "utils.h"

int menuAdmin(){
    int opcao = 0; // Inicializa com um valor inválido
    int tamanhoMenu = 6; // Quantidade de opções do menu. Para usar na função validarInput()

    do{
        limparTela();

        printf("===============================================================\n");
        printf("                  TELA PRINCIPAL - ADMIN\n");
        printf("===============================================================\n\n");
        printf("   [1] - CRUD de Sessões\n");
        printf("   [2] - CRUD de Usuários\n");
        printf("   [3] - CRUD de Reservas\n");
        printf("   [4] - Consultas\n");
        printf("   [5] - Relatórios\n");
        printf("   [6] - Voltar ao menu inicial\n\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        opcao = validarInput(tamanhoMenu);

    } while(opcao < 1 || opcao > 6); // Repete o menu se a opção for inválida

    return opcao;
}
