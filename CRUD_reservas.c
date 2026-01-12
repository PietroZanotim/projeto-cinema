#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "reservas.h"
#include "sessoes.h"
#include "utils.h"

int menu_CRUD_reservas() //codar as funções previamente declaradas em CRUD_reservas.h
{
    int opcao;
    int tamanhoMenu = 6; // Quantidade de opções do menu. Para usar na função validarInput()
    do
    {
        limparTela();

        printf("===============================================================\n");
        printf("                       CRUD de Reservas\n");
        printf("===============================================================\n\n");
        printf("   [1] - Adicionar reserva\n");
        printf("   [2] - Excluir reserva\n");
        printf("   [3] - Modificar reserva\n");
        printf("   [4] - Visualizar reserva por id\n");
        printf("   [5] - Visualizar todos as reservas\n");
        printf("   [6] - Voltar ao menu inicial\n\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        opcao = validarInput(tamanhoMenu);

    }
    while(opcao < 1 || opcao > 6);

    return opcao; //isso retorna para a função main na linha 115 para opcao_3
}

void adicionar_reserva(Reservas *reservas, int *qtdReservas, Usuarios *usuarios, int qtdUsuarios, Sessoes *sessoes, int qtdSessoes){
    int usuarioProcurado;
    int i;

    limparTela();
    printf("================================================\n");
    printf("              Adicionar reserva\n");
    printf("================================================\n\n");
    printf("            Selecione um usuário\n");
    printf("\n----------------------------------------------\n");

    for(i=0; i<qtdUsuarios; i++){
        printf("Usuário %d:\n", i+1);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("CPF: %s\n", usuarios[i].cpf);
        printf("Idade: %d\n", usuarios[i].idade);
        printf("Saldo: %f\n", usuarios[i].saldo);
        printf("\n------------------\n");
    }
    printf("Usuário: ");

    while (1){
        scanf("%d", &usuarioProcurado);
        if(usuarioProcurado < 1 || usuarioProcurado > qtdUsuarios){
            puts("\nEsse usuário não existe.");
            printf("Usuário: ");
        }else{
            break; //tudo certo, para sair do while
        }
    }
    usuarioProcurado--; //transformar em indice
    limparTela();
    printf("Usuário: %s:\n", usuarios[usuarioProcurado].nome);
    printf("CPF: %s\n", usuarios[usuarioProcurado].cpf);
    printf("Idade: %d\n", usuarios[usuarioProcurado].idade);
    printf("Saldo: %f\n", usuarios[usuarioProcurado].saldo);
    printf("\n------------------\n");

    listarSessoes(sessoes, qtdSessoes, usuarios, usuarioProcurado, reservas, qtdReservas);
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
    imprimir_dados_reserva(reservas, qtdReservas, usuarios, resultado_validacao);

    printf("\n[Enter] para continuar...\n");
    getchar();
}

void visualizar_todas_reservas(Reservas *reservas, int qtdReservas, Usuarios *usuarios){
    int i;

    limparTela();
    for(i=0; i<qtdReservas; i++){
        imprimir_dados_reserva(reservas, qtdReservas, usuarios, i);
    }
}

void modificar_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, Sessoes *sessoes, int qtdSessoes, int qtdUsuarios){
    int idProcurado, opcao, resultado_validacao;
    int tamanhoMenu = 5; // Quantidade de opções do menu. Para usar na função validarInput()
    limparTela();
    printf("================================================\n");
    printf("              Modificação de reserva\n");
    printf("================================================\n\n");
    printf("              Digite o ID da reserva\n");
    printf("\n----------------------------------------------\n");
    printf("ID: ");
    while (1)
    {
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
    imprimir_dados_reserva(reservas, qtdReservas, usuarios, resultado_validacao);


    do{
        printf("===============================================================\n");
        printf("                       Selecione uma Opção\n");
        printf("===============================================================\n\n");
        printf("   [1] - Modificar Nome\n");
        printf("   [2] - Modificar CPF\n");
        printf("   [3] - Modificar ID\n");
        printf("   [4] - Modificar ID Sessão\n");
        printf("   [5] - Modificar Assento\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        opcao = validarInput(tamanhoMenu);

    }
    while(opcao < 1 || opcao > 5);
    printf("\n\n");
    switch(opcao){
        case 1: modificarNome(reservas, qtdReservas, usuarios, resultado_validacao); break;
        case 2: modificarCPF(reservas, qtdReservas, usuarios, resultado_validacao, qtdUsuarios); break;
        case 3: modificarID(reservas, qtdReservas, resultado_validacao); break;
        case 4: modificarIDsessao(reservas, qtdReservas, resultado_validacao); break;
        case 5: modificarAssento(reservas, qtdReservas, usuarios, resultado_validacao, sessoes, qtdSessoes); break;
    }
}
