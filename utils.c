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
        if (scanf("%d", &opcao) != 1) {
            // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
            // limpamos o buffer de entrada para evitar um loop infinito.
            opcao = 0; // Reseta para um valor inválido
            while (getchar() != '\n'); // Limpa o buffer
        }

        // Validação de intervalo numérico        
        if (opcao < 1 || opcao > 4) {
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (opcao < 1 || opcao > 4); // Repete o menu se a opção for inválida

    // Retorna a opção válida (1, 2, 3 ou 4)
    return opcao;
}

//-----------------------------------------------------------------------------
//---------------------------{ MENU DE LOGIN }---------------------------------
//-----------------------------------------------------------------------------
int menuLogin(Usuarios *usuario, int indiceUsuario, int *controleAdmin) {

    int opcao = 0; // Inicializa com um valor inválido

    if(usuario[indiceUsuario].nome != "admin"){ //Se o login não for do admin, apresenta esse menu;

        do {

            limparTela(); 

            printf("===============================================================\n");
            printf("       TELA PRINCIPAL - Olá: %s\n", usuario[indiceUsuario].nome);
            printf("===============================================================\n");
            printf("   [1] - Visualizar filmes disponíveis.\n");
            printf("   [2] - Visualizar minhas sessões.\n");
            printf("   [3] - Visualizar meu saldo.\n");
            printf("   [4] - Realizar depósito.\n");
            printf("   [5] - Comprar ingresso.\n"); 
            printf("   [6] - Alterar senha.\n"); // Alteração dos registros.
            printf("   [7] - Excluir esta conta.\n"); // Remoção dos registros.
            printf("   [8] - Voltar ao menu inicial\n");
            printf("\n--------------------------------------------\n");
            printf("Digite a opcao desejada: ");

            // Validação de tipo de input
            if (scanf("%d", &opcao) != 1) {
                // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
                // limpamos o buffer de entrada para evitar um loop infinito.
                opcao = 0; // Reseta para um valor inválido
                while (getchar() != '\n'); // Limpa o buffer
            }

            // Validação de intervalo numérico        
            if (opcao < 1 || opcao > 8) {
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
                while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
                getchar(); // Aguarda o usuário pressionar Enter
            }

        } while (opcao < 1 || opcao > 8); // Repete o menu se a opção for inválida
        
        *controleAdmin = 1; //Se o usuario não for admin, o controle continua 1...
        
        return opcao;

    } else { // Caso o Login seja do admin, apresentará outras opções;
        
    }

}

//-----------------------------------------------------------------------------
//---------------------{ VISUALIZAR SALDO DO USUARIO }-------------------------
//-----------------------------------------------------------------------------

void verSaldo(Usuarios *usuario, int indiceUsuario){

    limparTela();

    printf("===============================================================\n");
    printf("              Saldo de: %s\n", usuario[indiceUsuario].nome);
    printf("===============================================================\n\n");
    printf("\nSeu saldo atual: R$%.2f\n", usuario[indiceUsuario].saldo);

    printf("\n[Enter] para retornar ao menu login...");
    while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
    getchar(); // Aguarda o usuário pressionar Enter

}

//-----------------------------------------------------------------------------
//------------------{ REALIZAR DEPÓSITO NO SALDO DO USUARIO }------------------
//-----------------------------------------------------------------------------

void realizarDeposito(Usuarios *usuario, int indiceUsuario){

    limparTela();

    float valorDeposito=0.00;

    printf("===============================================================\n");
    printf("       Saldo de: - %s\n", usuario[indiceUsuario].nome);
    printf("===============================================================\n\n");
    printf("\n*** MAX - R$100.00 | POR OPERAÇÃO ***");
    printf("\nDigite o valor que deseja depositar: ");

    while(scanf("%f", &valorDeposito)!=1 || valorDeposito>100.00){
        printf("\nValor digitado inválido ou acima do permitido!");
        printf("\n[Enter] para tentar novamente.");
        while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
        getchar(); // Aguarda o usuário pressionar Enter
    }

    usuario[indiceUsuario].saldo += valorDeposito;

    limparTela();
    printf("===============================================================\n");
    printf("                 Depósito realizado com sucesso!");
    printf("\n===============================================================\n");

    printf("\n[Enter] para retornar ao menu login...");
    while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
    getchar(); // Aguarda o usuário pressionar Enter

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

int voltar(){
    char vazio;

    // Validação para voltar ao menu
    int valid = 0;

    do{
        // Consumir o buffer antes de ler a próxima tecla
        while (getchar() != '\n');
        // Lê o caracter do buffer de entrada
        vazio = getchar();

        // Se o usuário digitar Enter, a função retorna 1
        if(vazio == '\n'){
            return 1;
        }
        // Se a condição anterior for falsa, altera o valor da validação para 1
        else{
            valid = 1;
            printf("Digito inválido, aperte Enter para voltar: ");
        }
    }while (valid == 1);
}


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

    printf("Aperte Enter para voltar: ");

    // Chama a função voltar, se retornar 1 a função saberFuncionalidade se encerra
    if(voltar() == 1){
        return 0;
    }
}

//Função para explicar como funciona as sessões e horários dos filmes
void saberHorarios(){

}

//Função para mostrar os detalhes dos filmes disponíveis
void saberFilmes(){

}



int saberMais(){

    int escolha = 0; // Inicializa como opção inválida

    limparTela();
    do{
        printf("==============================================\n");
        printf("                 SAIBA MAIS\n");
        printf("==============================================\n\n");
        printf("   [1] - Funcionalidades\n");
        printf("   [2] - Sessão e Horários\n");
        printf("   [3] - Filmes\n");
        printf("   [4] - Voltar\n");
        printf("\n--------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação do input
        do {
            if (scanf("%d", &escolha) != 1) {
                // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
                // limpamos o buffer de entrada para evitar um loop infinito.
                escolha = 0; // Reseta para um valor inválido
                while (getchar() != '\n'); // Limpa o buffer
            }

            // Validação de intervalo numérico        
            if (escolha < 1 || escolha > 4) {
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
                while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
                getchar(); // Aguarda o usuário pressionar Enter
            }

        } while (escolha < 1 || escolha > 4); // Repete o menu do saber mais se a opção for inválida

        //Condições para selecionar a função escolhida pelo usuário
        if(escolha == 1){
            saberFuncionalidades();
        }
        else if(escolha == 2){
            saberFilmes();
        }
        else if(escolha == 3){
           saberFilmes();
        }
        else{
            break;
        }
    } while(escolha != 4);
}
