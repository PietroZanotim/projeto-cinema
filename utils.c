//---------------------------!! SOBRE O ARQUIVO !!-----------------------------
//-----------{ FUNCOES QUE NÃO POSSUEM COMO PARAMENTRO O USUÁRIO }-------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "structs.h"

void limparTela(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls || clear");
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #else
        for(int i = 0; i < 50; i++) printf("\n");
    #endif
}

int menuPrincipal(){
    int opcao = 0; // Inicializa com um valor inválido
    int tamanhoMenu = 4; // Quantidade de opções no menu. Para usar na função validarInput()

    do{
        limparTela();
        printf("==============================================\n");
        printf("       SISTEMA DE GERENCIAMENTO DE CINEMA\n");
        printf("==============================================\n\n");
        printf("   [1] - Fazer Login\n");
        printf("   [2] - Cadastrar Novo Usuario\n");
        printf("   [3] - Saber Mais\n");
        printf("   [4] - Sair do Programa\n");
        printf("\n--------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        // Validação de tipo de input
        opcao = validarInput(tamanhoMenu);
    }while(opcao < 1 || opcao > 4); // Repete o menu se a opção for inválida
    // Retorna a opção válida (1, 2, 3 ou 4)
    return opcao;
}

int confirmarSaida(){
    char resposta;
    limparTela();
    do{
        printf("=========================================\n");
        printf("              SAIR DO PROGRAMA\n");
        printf("=========================================\n\n");
        printf("Voce tem certeza que deseja sair?\n");
        printf("Todos os dados serao salvos.\n\n");
        printf("[S] - Sim, desejo sair\n");
        printf("[N] - Nao, quero voltar ao menu\n");
        printf("\nDigite sua escolha: ");

        // espaço antes do %c para consumir buffer
        if(scanf(" %c", &resposta) != 1){
            resposta = ' '; // Define como inválido se o scanf falhar
        }

        // Limpa o buffer de entrada para a próxima iteração
        while (getchar() != '\n');

        resposta = toupper(resposta); // Converte para maiúsculo

        if(resposta != 'S' && resposta != 'N'){
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while(getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    }while(resposta != 'S' && resposta != 'N');

    if(resposta == 'S'){
        limparTela();
        return 1; // 1 = Sim, sair
    }else{
        return 0; // 0 = Não, voltar
    }
}

int confirmarRetorno(){
    char resposta;
    limparTela();
    do{
        printf("=========================================\n");
        printf("          RETONAR AO MENU PRINCIPAL      \n");
        printf("=========================================\n\n");
        printf("Voce tem certeza que deseja retornar?\n");
        printf("Todos os dados serao salvos.\n\n");
        printf("[S] - Sim, desejo voltar\n");
        printf("[N] - Nao, desejo permancer\n");
        printf("\nDigite sua escolha: ");

        // espaço antes do %c para consumir buffer
        if(scanf(" %c", &resposta) != 1){
            resposta = ' '; // Define como inválido se o scanf falhar
        }

        // Limpa o buffer de entrada para a próxima iteração
        while (getchar() != '\n');

        resposta = toupper(resposta); // Converte para maiúsculo

        if(resposta != 'S' && resposta != 'N'){
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while(getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); //Aguarda o usuário pressionar Enter
        }
    }while (resposta != 'S' && resposta != 'N');

    if(resposta == 'S'){
        limparTela();
        return 1; //Sim, sair
    }else{
        return 0; //Não, voltar
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
        while(getchar() != '\n');
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
    }while(valid == 1);
}

//Função informacional do projeto
int saberFuncionalidades(int modo){
    limparTela();

    // Se o modo for 1, mostrar apenas as informações para o usuário
    if(modo == 1){

        printf("==================================================================\n");
        printf("                    FUNCIONALIDADES - USUÁRIO                     \n");
        printf("==================================================================\n\n");

        // 1 - CRIAR CONTA
        printf(" 1 - CRIAR CONTA:\n");
        printf("     No menu principal, digite 2 para registrar-se e poder utilizar \n");
        printf("     o sistema de reserva de filmes e acessar seu saldo de dinheiro.\n");
        printf("     (*Importante*: Lembre-se dos dados de cadastro para o login.)\n\n");

        // 2 - REALIZAR LOGIN
        printf(" 2 - REALIZAR LOGIN:\n");
        printf("     No menu principal, digite 1 para realizar o login. E necessario\n");
        printf("     ja ter uma conta criada. Realize o login sempre que iniciar.\n\n");

        // 3 - VISUALIZAR FILMES
        printf(" 3 - VISUALIZAR FILMES:\n");
        printf("     Logado, digite 1 para ver filmes, programacoes, idades minimas,\n");
        printf("     datas, horarios, salas, assentos e valores. Apos visualizar,\n");
        printf("     voce podera comprar seu ingresso.\n\n");

        // 4 - VISUALIZAR SESSÕES
        printf(" 4 - VISUALIZAR SESSOES:\n");
        printf("     Logado, digite 2 para conferir suas reservas: nome do filme,\n");
        printf("     data, horario, numero da sala e o assento escolhido.\n\n");

        // 5 - VISUALIZAR E ADICIONAR SALDO
        printf(" 5 - VISUALIZAR E ADICIONAR SALDO:\n");
        printf("     Logado, digite 3 para gerenciar seu saldo. Voce pode visualizar seu saldo atual e realizar\n");
        printf("     depositos, sendo R$100.00 o valor maximo permitido.\n\n");

        // 6 - ALTERAR SUA SENHA
        printf(" 6 - ALTERAR SUA SENHA:\n");
        printf("     Logado, digite 4 para atualizar sua senha de acesso atual.\n\n");

        // 7 - EXCLUIR CONTA
        printf(" 7 - EXCLUIR CONTA:\n");
        printf("     Logado, digite 5 para excluir sua conta. Seus dados serao\n");
        printf("     exibidos antes da confirmacao. (*ATENCAO*: Acao permanente!)\n\n");

        printf("==================================================================\n");
        printf(" >> Aperte [Enter] para voltar: ");
    }
    // Se o modo for 2, mostar apenas as informações do admin
    else{
        printf("==================================================================\n");
        printf("|                    FUNCIONALIDADES - ADMIN                     |\n");
        printf("==================================================================\n\n");

        // 1 - CRUD SESSÕES
        printf(" [1] CRUD SESSOES:\n");
        printf("     No menu do admin, digite 1 para gerenciar as sessoes.\n");
        printf("     Permite: adicionar, remover, editar e visualizar sessoes.\n\n");

        // 2 - CRUD USUÁRIOS
        printf(" [2] CRUD USUARIOS:\n");
        printf("     No menu do admin, digite 2 para gerenciar os usuarios.\n");
        printf("     Permite: adicionar, remover, editar e visualizar usuarios.\n\n");

        // 3 - CRUD RESERVAS
        printf(" [3] CRUD RESERVAS:\n");
        printf("     No menu do admin, digite 3 para gerenciar as reservas.\n");
        printf("     Permite: adicionar, remover, editar e visualizar reservas.\n\n");

        // 4 - CONSULTAS
        printf(" [4] CONSULTAS:\n");
        printf("     No menu do admin, digite 4 para consultar informacoes.\n");
        printf("     Filtros disponiveis: nome do filme, data e CPF do cliente.\n\n");

        // 5 - RELATÓRIO
        printf(" [5] RELATORIO:\n");
        printf("     No menu do admin, digite 5 para gerar arquivos (.txt).\n");
        printf("     Exporta reservas detalhadas com base no filtro escolhido.\n\n");

        printf("==================================================================\n");
        printf(" >> Aperte [Enter] para voltar: ");
    }
    

    // Chama a função voltar, se retornar 1 a função saberFuncionalidade se encerra
    if(voltar() == 1){
        return 0;
    }
}

int saberSessao(){
    limparTela();
    //Adicionar informação sobre as sessões
}

int saberFilmes(){
    limparTela();
    //Adicionar informação sobre os filmes
}

int saberMais(){
    int escolha = 0; // Inicializa como opção inválida
    int tamanhoMenu = 5;
    limparTela();
    do{
        printf("==============================================\n");
        printf("                 SAIBA MAIS\n");
        printf("==============================================\n\n");
        printf("   [1] - Funcionalidades - Usuário\n");
        printf("   [2] - Funcionalidades - Admin\n");
        printf("   [3] - Sessão e Horários\n");
        printf("   [4] - Filmes\n");
        printf("   [5] - Voltar\n");
        printf("\n--------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação do input
        escolha = validarInput(tamanhoMenu);

        //Condições para selecionar a função escolhida pelo usuário
        if(escolha == 1 && escolha == 2){
            saberFuncionalidades(escolha);
        }
        
        else if(escolha == 3){
            saberSessao();
        }

        else if(escolha == 4){
            saberFilmes();
        }

        else{
            limparTela();
            break;
        }
    }while(escolha != 5);
    return 0;
}

// Recebe a string da data como parâmetro
int validar_formato_data(char *data){

    // --- PARTE 1: VALIDAÇÃO ESTRUTURAL (A que já tínhamos) ---

    // 1. Verificar tamanho exato (DD/MM/AA tem 8 caracteres)
    if(strlen(data) != 8) return -1;
    // 2. Verificar as barras nas posições 2 e 5 (01/34/67)
    if(data[2] != '/' || data[5] != '/') return -2;
    // 3. Verificar se os outros caracteres são números
    for(int i = 0; i < 8; i++){
        // Pula as posições das barras
        if(i == 2 || i == 5) continue;

        // Se não for dígito, erro
        if(!isdigit(data[i])) return -3;
    }

    // --- PARTE 2: VALIDAÇÃO LÓGICA (A Nova) ---

    int dia, mes, ano;

    // O sscanf extrai os números da string "DD/MM/AA" e joga nas variáveis int
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);

    // 4. Validação simples de Dia (1 a 31)
    if(dia < 1 || dia > 31) return -4;

    // 5. Validação de Mês (1 a 12)
    if(mes < 1 || mes > 12) return -5;

    // 6. Validacao de Ano
    if(ano < 26) return -6;

    return 0; // Sucesso
}

int validarInput(int tamanhoMenu){
    char input[50];
    int opcao;
    int entradaValida = 0;

    do{
        fgets(input, 50, stdin);

        // 1. Verifica se é um número inteiro válido
        if(sscanf(input, "%d", &opcao) != 1){
            printf("Erro: Voce digitou letras ou simbolos.\n");
            printf("Por favor, digite um numero entre 1 e %d.\n", tamanhoMenu);
            continue; // Volta para o início do loop
        }

        // 2. Verifica se o número está dentro do intervalo do menu
        if(opcao < 1 || opcao > tamanhoMenu){
            printf("Opcao invalida! O numero deve ser entre 1 e %d.\n", tamanhoMenu);
            continue; // Volta para o início do loop
        }

        // Se passou pelas duas barreiras acima, a entrada é válida
        entradaValida = 1;

    }while(!entradaValida);

    return opcao;
}
