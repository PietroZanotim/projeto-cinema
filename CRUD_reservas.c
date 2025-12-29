#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "reservas.h"
#include "utils.h"



int menu_CRUD_reservas() //codar as funções previamente declaradas em CRUD_reservas.h
{
    int opcao;
    do
    {
        limparTela();

        printf("===============================================================\n");
        printf("                       CRUD de Reservas\n");
        printf("===============================================================\n\n");
        printf("   [1] - Adicionar reserva\n");
        printf("   [2] - Excluir reserva\n");
        printf("   [3] - Modificar resera\n");
        printf("   [4] - Visualizar reserva por id\n");
        printf("   [5] - Visualizar todos as reservas\n");
        printf("   [6] - Voltar ao menu inicial\n\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        if (scanf("%d", &opcao) != 1)
        {
            // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
            // limpamos o buffer de entrada para evitar um loop infinito.
            opcao = 0; // Reseta para um valor inválido
            while (getchar() != '\n'); // Limpa o buffer
        }

        // Validação de intervalo numérico
        if (opcao < 1 || opcao > 6)
        {
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }
    }
    while(opcao < 1 || opcao > 6);

    return opcao; //isso retorna para a função main na linha 115 para opcao_3
}

void visualizar_reserva_id(Reservas *reservas, int qtdReservas, Usuarios *usuarios)
{
    int idProcurado;

    limparTela();
    printf("================================================\n");
    printf("             Visualizar reservas por ID\n");
    printf("================================================\n\n");
    printf("             Digite o Id da reserva\n");
    printf("\n----------------------------------------------\n");
    printf("ID: ");
    int resultado_validacao; //Usado para pegarmos o indice do usuário.

    while (1)
    {
        // Limpa o buffer sempre antes de ler
        while (getchar() != '\n');
        scanf("%d", &idProcurado);

        resultado_validacao =  buscar_indice_reserva(reservas, qtdReservas, idProcurado); //se achar o id, retorna posicao

        if(resultado_validacao == -1)
        {
            puts("\nEsse ID não existe.");
            printf("ID: ");
        }
        else
        {
            // Aqui ele retorna apenas o indice do usuario... Tudo ok, basta imprimir os dados.
            break;
        }
    }

    limparTela();
    printf("==========================================================\n");
    printf("           Reserva:\n");
    printf("==========================================================\n");
    printf("Nome: %s.\n", usuarios[resultado_validacao].nome);
    printf("CPF: %s.\n", reservas[resultado_validacao].cpf_usuario);
    printf("ID: %d.\n", reservas[resultado_validacao].id);
    printf("ID Sessão: %d.\n", reservas[resultado_validacao].id_sessao);
    printf("Assento: %s.\n", reservas[resultado_validacao].assento);

    printf("\n[Enter] para continuar...\n");
    getchar();
}

void visualizar_todas_reservas(Reservas *reservas, int qtdReservas, Usuarios *usuarios){
    int i;

    limparTela();
    for(i=0; i<qtdReservas; i++){
        printf("Nome: %s.\n", usuarios[i].nome);
        printf("CPF: %s.\n", reservas[i].cpf_usuario);
        printf("ID: %d.\n", reservas[i].id);
        printf("ID Sessão: %d.\n", reservas[i].id_sessao);
        printf("Assento: %s.\n", reservas[i].assento);
        printf("-------------------------------------------------------\n");
    }
}
