#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "utils.h"


int menu_CRUD_sessoes(){
    int opcao;
    do{
        limparTela(); 

        printf("===============================================================\n");
        printf("                       CRUD de Sessões\n");
        printf("===============================================================\n\n");
        printf("   [1] - Adicionar sessão\n");
        printf("   [2] - Excluir sessão\n");
        printf("   [3] - Modificar sessão\n");
        printf("   [4] - Visualizar sessão por id\n"); 
        printf("   [5] - Visualizar todas as sessões\n"); 
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
    } while(opcao < 1 || opcao > 6);

    return opcao;
}