//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//---------------------------{ MENU DO ADMIN )---------------------------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "admin.h"
#include "utils.h"

int menuAdmin() {
    int opcao = 0; // Inicializa com um valor inválido

    do {
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
        if (scanf("%d", &opcao) != 1) {
            // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
            // limpamos o buffer de entrada para evitar um loop infinito.
            opcao = 0; // Reseta para um valor inválido
            while (getchar() != '\n'); // Limpa o buffer
        }

        // Validação de intervalo numérico        
        if (opcao < 1 || opcao > 6) {
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (opcao < 1 || opcao > 6); // Repete o menu se a opção for inválida

    return opcao;
}