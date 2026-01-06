//---------------------------!! SOBRE O ARQUIVO !!-----------------------------
//-----------{ FUNCOES QUE NÃO POSSUEM COMO PARAMENTRO O USUÁRIO }-------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "structs.h" // Precisa conhecer a struct Usuarios

void limparTela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls || clear");
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #else
        for(int i = 0; i < 50; i++) printf("\n");
    #endif
}

//-----------------------------------------------------------------------------
//---------------------------{ MENU PRINCIPAL }--------------------------------
//-----------------------------------------------------------------------------
int menuPrincipal() {
    int opcao = 0; // Inicializa com um valor inválido
    int tamanhoMenu = 4; // Quantidade de opções no menu. Para usar na função validarInput()

    do {
        limparTela(); 

        printf("==============================================\n");
        printf("       SISTEMA DE GERENCIAMENTO DE CINEMA\n");
        printf("==============================================\n\n");
        printf("   [1] - Fazer Login\n");
        printf("   [2] - Cadastrar Novo Usuario\n");
        printf("   [3] - Saber Mais (Sobre o Projeto)\n");
        printf("   [4] - Sair do Programa\n");
        printf("\n--------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        opcao = validarInput(tamanhoMenu);

    } while (opcao < 1 || opcao > 4); // Repete o menu se a opção for inválida

    // Retorna a opção válida (1, 2, 3 ou 4)
    return opcao;
}

//-----------------------------------------------------------------------------
//-----------------------------{ OPCAO PARA SAIR }-----------------------------
//-----------------------------------------------------------------------------
int confirmarSaida() {
    char resposta;

    limparTela(); 

    do {
        printf("=========================================\n");
        printf("              SAIR DO PROGRAMA\n");
        printf("=========================================\n\n");
        printf("Voce tem certeza que deseja sair?\n");
        printf("Todos os dados serao salvos.\n\n");
        printf("[S] - Sim, desejo sair\n");
        printf("[N] - Nao, quero voltar ao menu\n");
        printf("\nDigite sua escolha: ");

        // espaço antes do %c para consumir buffer
        if (scanf(" %c", &resposta) != 1) {
            resposta = ' '; // Define como inválido se o scanf falhar
        }

        // Limpa o buffer de entrada para a próxima iteração
        while (getchar() != '\n'); 

        resposta = toupper(resposta); // Converte para maiúsculo

        if (resposta != 'S' && resposta != 'N') {
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (resposta != 'S' && resposta != 'N');

    if (resposta == 'S') {
        limparTela();
        return 1; // 1 = Sim, sair
    } else {
        return 0; // 0 = Não, voltar
    }
}

//-----------------------------------------------------------------------------
//-----------------------------{ OPCAO PARA RETORNAR }-------------------------
//-----------------------------------------------------------------------------
int confirmarRetorno() {
    char resposta;

    limparTela(); 

    do {
        printf("=========================================\n");
        printf("          RETONAR AO MENU PRINCIPAL\n");
        printf("=========================================\n\n");
        printf("Voce tem certeza que deseja retornar?\n");
        printf("Todos os dados serao salvos.\n\n");
        printf("[S] - Sim, desejo sair\n");
        printf("[N] - Nao, quero voltar ao menu\n");
        printf("\nDigite sua escolha: ");

        // espaço antes do %c para consumir buffer
        if (scanf(" %c", &resposta) != 1) {
            resposta = ' '; // Define como inválido se o scanf falhar
        }

        // Limpa o buffer de entrada para a próxima iteração
        while (getchar() != '\n'); 

        resposta = toupper(resposta); // Converte para maiúsculo

        if (resposta != 'S' && resposta != 'N') {
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (resposta != 'S' && resposta != 'N');

    if (resposta == 'S') {
        limparTela();
        return 1; // 1 = Sim, sair
    } else {
        return 0; // 0 = Não, voltar
    }
}

//-----------------------------------------------------------------------------
//-----------------------------{ SABER MAIS }----------------------------------
//-----------------------------------------------------------------------------


//Função para mostrar as funcionalidades do sistema
int saberFuncionalidades(){

    limparTela();

    printf("\n==============================================\n");
    printf("                 FUNCIONALIDADES\n");
    printf("==============================================\n\n");

    //Explicações das funcionalidades do programa
    printf("1- CRIAR CONTA:\n");
    printf("No menu principal, digite 2 para registrar-se e poder utilizar \no sistema de reserva de filmes e acessar seu saldo de dinheiro.\n(*Importante* - Lembre-se de seus dados do cadastro para realizar o login.)\n\n");
    printf("2- REALIZAR LOGIN:\n");
    printf("No menu principal, digite 1 para realizar o login, é necessário \njá ter criado uma conta em nosso sistema para isso.\nÉ necessário realizar o login sempre que você reiniciar nosso sistema.\n\n");
    //printf("3 - RESERVAR UMA SESSÃO:\n");
}



int saberMais(){

    int opcao = 0; 
    int tamanhoMenu = 4; 

    do{
        limparTela();
        
        printf("\n==============================================\n");
        printf("               SAIBA MAIS\n");
        printf("==============================================\n\n");
        printf("   [1] - Funcionalidades\n");
        printf("   [2] - Sessao e Horarios\n");
        printf("   [3] - Filmes\n");
        printf("   [4] - Voltar\n");
        printf("\n--------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação do tipo de input
        opcao = validarInput(tamanhoMenu);

        // Condições
        if(opcao == 1){
            printf("\n--- Voce escolheu Funcionalidades ---\n");
            saberFuncionalidades();

            // Pausa para o usuário ler antes do menu voltar
            printf("Pressione Enter para voltar...");
            getchar(); 
        }
        else if(opcao == 2){
            printf("\n--- Voce escolheu Sessao ---\n");
             // Pausa
            printf("Pressione Enter para voltar...");
            getchar();
        }
        else if(opcao == 3){
            printf("\n--- Voce escolheu Filmes ---\n");
             // Pausa
            printf("Pressione Enter para voltar...");
            getchar();
        }
        else if(opcao == 4){
            printf("\nVoltando...\n");
        }

    } while(opcao != 4);
    
    return 0;
}


int validarInput(int tamanhoMenu){
    char input[50]; // Buffer para guardar o texto digitado
    int opcao;

    // Ler tudo o que foi digitado até o Enter.
    // Isso garante que o buffer fique limpo, sem precisar de loops while.
    fgets(input, 50, stdin);

    // Converter o texto para número usando sscanf
    // sscanf funciona igual scanf, mas lê da variável 'input' em vez do teclado
    if (sscanf(input, "%d", &opcao) != 1) {
        // Entra aqui se o usuário digitou letras ou símbolos
        printf("\nOpcao invalida! (Digite um número). Pressione Enter para tentar novamente.");
        getchar(); // Pausa esperando um Enter
        return 0; 
    }

    // Validação de intervalo numérico (ex: 1 a 4)
    if (opcao < 1 || opcao > tamanhoMenu) {
        printf("\nOpcao invalida! (Numero um número válido). Pressione Enter para tentar novamente.");
        getchar(); // Pausa esperando um Enter
        return 0;
    }

    return opcao;
}