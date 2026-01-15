#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "reservas.h"
#include "sessoes.h"
#include "utils.h"

int menu_CRUD_reservas(){ //codar as funções previamente declaradas em CRUD_reservas.h
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

void adicionar_reserva(Reservas *reservas, int *qtdReservas, Usuarios *usuarios, int qtdUsuarios, Sessoes *sessoes, int qtdSessoes, int *qtdIdReservas){
    int usuarioProcurado;
    int i;

    if(qtdUsuarios == 1){//1 por causa do admin
        limparTela();
        printf("Não existem usuários cadastrados!\n");
        printf("\n[Enter] para retornar ao menu...\n");
        getchar();
        return;
    }

    limparTela();
    printf("================================================\n");
    printf("              Adicionar reserva\n");
    printf("================================================\n\n");
    printf("            Selecione um usuário\n");
    printf("\n----------------------------------------------\n");

    for(i=1; i<qtdUsuarios; i++){
        printf("Usuário %d:\n", i);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("CPF: %s\n", usuarios[i].cpf);
        printf("Idade: %d\n", usuarios[i].idade);
        printf("Saldo: %f\n", usuarios[i].saldo);
        printf("\n------------------\n");
    }
    printf("\nUsuário: ");

    while (1){
        scanf("%d", &usuarioProcurado);
        if(usuarioProcurado < 1 || usuarioProcurado > qtdUsuarios){
            puts("\nEsse usuário não existe.");
            printf("Usuário: ");
        }else{
            break; //tudo certo, para sair do while
        }
    }

    limparTela();
    printf("Usuário: %s:\n", usuarios[usuarioProcurado].nome);
    printf("CPF: %s\n", usuarios[usuarioProcurado].cpf);
    printf("Idade: %d\n", usuarios[usuarioProcurado].idade);
    printf("Saldo: %f\n", usuarios[usuarioProcurado].saldo);
    printf("\n------------------\n");

    listarSessoes(sessoes, qtdSessoes, usuarios, usuarioProcurado, reservas, qtdReservas, qtdIdReservas);
}

void excluir_reserva(Reservas *reservas, int *qtdReservas, Usuarios *usuarios){
    int reservaProcurada;
    int i;
    char resposta;

    if(*qtdReservas == 0){
        limparTela();
        printf("Não existem reservas feitas!\n");
        printf("\n[Enter] para retornar ao menu...\n");
        getchar();
        return;
    }

    limparTela();
    printf("================================================\n");
    printf("              Excluir reserva\n");
    printf("================================================\n\n");
    printf("            Selecione uma reserva\n");
    printf("\n----------------------------------------------\n");

    for(i=0; i < *qtdReservas; i++){
        printf("Reserva %d:\n", i+1);
        imprimir_dados_reserva(reservas, *qtdReservas, usuarios, i);
        printf("\n------------------\n");
    }
    printf("\nReserva: ");

    while (1){
        scanf("%d", &reservaProcurada);
        if(reservaProcurada < 1 || reservaProcurada > *qtdReservas){
            puts("\nEssa reserva não existe.");
            printf("Reserva: ");
        }else{
            break; //tudo certo, para sair do while
        }
    }
    reservaProcurada--; //transformar em indice

    limparTela();
    imprimir_dados_reserva(reservas, *qtdReservas, usuarios, reservaProcurada);

    do{
        printf("\nDeseja confirmar a exclusão? (S/N): ");
        if (scanf(" %c", &resposta) != 1) {
            resposta = ' '; // Define como inválido se o scanf falhar
        }
        while (getchar() != '\n');
        resposta = toupper(resposta); // Converte para maiúsculo
        if (resposta != 'S' && resposta != 'N') {
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    }while (resposta != 'S' && resposta != 'N');

    if(resposta=='S'){
        int j;
        for(j=0; j < *qtdReservas - 1; j++){ // -1 para não acessar memória indevida
            reservas[j] = reservas[j+1];
        }
    }

        (*qtdReservas)--;
}

void visualizar_reserva_id(Reservas *reservas, int qtdReservas, Usuarios *usuarios){
    int idProcurado;

    if(qtdReservas == 0){
        limparTela();
        printf("Não existem reservas feitas!\n");
        printf("\n[Enter] para retornar ao menu...\n");
        getchar();
        return;
    }

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
    printf("==========================================================\n");
    printf("                  Reserva:\n");
    printf("==========================================================\n");
    imprimir_dados_reserva(reservas, qtdReservas, usuarios, resultado_validacao);

    printf("\n[Enter] para continuar...\n");
    getchar();
}

void visualizar_todas_reservas(Reservas *reservas, int qtdReservas, Usuarios *usuarios){
    int i;

    if(qtdReservas == 0){
        limparTela();
        printf("Não existem reservas feitas!\n");
        printf("\n[Enter] para retornar ao menu...\n");
        getchar();
        return;
    }

    limparTela();
    for(i=0; i<qtdReservas; i++){
        printf("==========================================================\n");
        printf("                  Reserva %d:\n", i+1);
        printf("==========================================================\n");
        imprimir_dados_reserva(reservas, qtdReservas, usuarios, i);
    }
}

void modificar_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, Sessoes *sessoes, int qtdSessoes, int qtdUsuarios){
    int idProcurado, opcao, resultado_validacao;
    int tamanhoMenu = 5; // Quantidade de opções do menu. Para usar na função validarInput()

    if(qtdReservas == 0){
        limparTela();
        printf("Não existem reservas feitas!\n");
        printf("\n[Enter] para retornar ao menu...\n");
        getchar();
        return;
    }

    limparTela();
    printf("================================================\n");
    printf("              Modificação de reserva\n");
    printf("================================================\n\n");
    printf("              Digite o ID da reserva\n");
    printf("\n----------------------------------------------\n");
    printf("ID: ");
    while(1){
        scanf("%d", &idProcurado);

        resultado_validacao =  buscar_indice_reserva(reservas, qtdReservas, idProcurado); //se achar o id, retorna posicao

        if(resultado_validacao == -1){
            puts("\nEsse ID não existe.");
            printf("ID: ");
        }else{
            // Aqui ele retorna apenas o indice do usuario... Tudo ok, basta imprimir os dados.
            break;
        }
    }

    limparTela();
    printf("==========================================================\n");
    printf("                  Reserva:\n");
    printf("==========================================================\n");
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
