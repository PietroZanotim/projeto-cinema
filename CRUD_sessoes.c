#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "sessoes.h"
#include "utils.h"


int menu_CRUD_sessoes(){
    int opcao;
    int tamanhoMenu = 6; //Quantidade de opções do menu. Para usar na função validarInput()
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


        // Validação do tipo de input
        opcao = validarInput(tamanhoMenu);

    }while(opcao < 1 || opcao > 6);

    return opcao;
}

void adicionar_sessao(Sessoes **lista, int *qtdSessoes, int *maxSessoes){
    //Gerenciamento de memória (aumenta 5 posições quando cheio)
    if(*qtdSessoes >= *maxSessoes){
        *maxSessoes += 5;
        Sessoes *temp = (Sessoes *) realloc(*lista, (*maxSessoes) * sizeof(Sessoes));
        if(temp == NULL){
            printf("ERRO: Falha na realocacao de memoria!\n");
            return;
        }
        *lista = temp;
    }

    limparTela();
    int idTemp;
    printf("===============================================\n");
    printf("           Novo cadastro de sessao\n");
    printf("===============================================\n\n");
    printf("         Digite o ID da nova sessão:\n");
    printf("\n---------------------------------------------\n");
    printf("ID: ");
    scanf("%d", &idTemp);

    if(buscaSessao(*lista, idTemp, *qtdSessoes) != -1){
        printf("Erro: Ja existe uma sessao com o ID %d\n", idTemp);
        while (getchar() != '\n');
        getchar();
        return;
    }

    Sessoes nova;
    nova.id = idTemp;

    do{
        limparTela();
        printf("===============================================\n");
        printf("           Novo cadastro de sessao\n");
        printf("===============================================\n\n");
        printf("           Digite o nome do filme:\n");
        printf("\n---------------------------------------------\n");
        printf("Nome do filme: ");

        fgets(nova.nome_filme, sizeof(nova.nome_filme), stdin);
        nova.nome_filme[strcspn(nova.nome_filme, "\n")] = '\0'; // Limpar o \n

         //Caso o não preencha o nome
        if(strlen(nova.nome_filme) == 0){
            printf("\nERRO: O nome do filme nao pode ser vazio!");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }while(strlen(nova.nome_filme) == 0);

    int dataValida = 0;
    do{
        limparTela();
        printf("===============================================\n");
        printf("           Novo cadastro de sessao\n");
        printf("===============================================\n\n");
        printf("     Digite a data no formato (DD/MM/AA):\n");
        printf("\n---------------------------------------------\n");
        printf("Data: ");
        scanf("%8s", nova.data); // Limita a leitura da string
        while(getchar() != '\n'); //Limpa buffer após leitura

        // Validação: tamanho 8 e barras nas posições certas [2,5]
        if(strlen(nova.data) == 8 && nova.data[2] == '/' && nova.data[5] == '/'){
            dataValida = 1;
        }else{
            printf("\nERRO: Formato invalido! Use o padrao DD/MM/DD (ex: 15/01/26).");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
        }
    }while(!dataValida);

    int horaValida = 0;
    do{
        limparTela();
        printf("===============================================\n");
        printf("           Novo cadastro de sessao\n");
        printf("===============================================\n\n");
        printf(" Digite o horário de inicio no formato (HH:MM):\n");
        printf("\n---------------------------------------------\n");
        printf("Horario: ");
        scanf("%5s", nova.horario_inicio);
        while(getchar() != '\n');

        int h, m;
        //sscanf: lê dados de uma string que já existe na memória
        if(sscanf(nova.horario_inicio, "%d:%d", &h, &m) == 2){
            if(h >= 0 && h <= 23 && m >= 0 && m <= 59 && nova.horario_inicio[2] == ':'){
                horaValida = 1;
            }
        }

        if(!horaValida){
            printf("\nERRO: Horario invalido ou formato incorreto!.");
            printf("\nCertifique-se de usar HH:MM (ex: 09:30 ou 22:00).");
            printf("\nPressione [ENTER] para tentar novamente...");
            getchar();
        }

    }while(!horaValida);

    printf("===============================================\n");
    printf("           Novo cadastro de sessao\n");
    printf("===============================================\n\n");
    printf("         Digite o valor do ingresso:\n");
    printf("\n---------------------------------------------\n");
    printf("Valor: R$ ");
    scanf("%f", &nova.valorIngresso);

    printf("===============================================\n");
    printf("           Novo cadastro de sessao\n");
    printf("===============================================\n\n");
    printf("           Digite a idade minima:\n");
    printf("\n---------------------------------------------\n");
    printf("Idade: ");
    scanf("%d", &nova.limIdade);

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            nova.assento[i][j] = 0;
        }
    }

    //"Desferencia' o ponteiro duplo para obter o endereço real
    (*lista)[*qtdSessoes] = nova;
    (*qtdSessoes)++;

    limparTela();
    printf("============================================================\n");
    printf("  Sessao adicionada com sucesso! [Enter] para continuar...\n");
    printf("============================================================\n");
    getchar();
}

void excluir_sessao(Sessoes *lista, int *qtdSessoes, Reservas *listaReservas, int qtdReservas){
    int id, indice;
    char resposta;

    limparTela();
    printf("===============================================\n");
    printf("              Exclusao de sessao\n");
    printf("===============================================\n\n");
    printf("        Digite o ID que deseja excluir:\n");
    printf("\n---------------------------------------------\n");
    printf("ID: ");
    scanf("%d", &id);

    //encontra em qual a posição do vetor a sessão está
    indice = buscaSessao(lista, id, *qtdSessoes);
    if(indice == -1){
        printf("ERRO: Sessao nao encontrada!\n");
        while(getchar() != '\n');
        getchar();
        return;
    }
    //Exibição detalhada dos dados da sessão antes de excluir
    limparTela();
    printf("===============================================\n");
    printf("       Dados da sessão a ser excluida\n");
    printf("===============================================\n\n");
    printf("Filme:        %s\n", lista[indice].nome_filme);
    printf("Data:         %s\n", lista[indice].data);
    printf("Horario:      %s\n", lista[indice].horario_inicio);
    printf("valor:        R$ %.2f\n", lista[indice].valorIngresso);
    printf("Idade Minima: %d anos\n", lista[indice].limIdade);
    printf("===============================================\n");

    //Confirmação da exclusão
    do{
        printf("===============================================\n");
        printf(" Deseja confirmar a exclusao definitiva? (S/N)\n");
        printf("===============================================\n\n");

        if(scanf("%c", &resposta) != 1){
            resposta = ' ';
        }

        while (getchar() != '\n'); // Limpa o buffer de entrada
        resposta = toupper(resposta);

        if(resposta != 'S' && resposta != 'N'){
            printf("\nOpcao invalida! Digite S ou N.\n");
        }
    }while (resposta != 'S' && resposta != 'N');

    // Integridade Relacional
    // Um registro da Estrutura 1 (Sessões) nao pode ser removido se estiver na Estrutura 3 (Reservas).
    if(resposta == 'S'){
        for(int i = 0; i < qtdReservas; i++){
            if(listaReservas[i].id_sessao == id){
                printf("\nERRO: Nao eh possivel excluir.\n");
                printf("Existem reservas vinculadas a esta sessao!\n");
                getchar();
                return;
            }
        }

        //Remoção por deslocamento ("puxa" todos os itens seguintes uma posição para trás).
        for(int i = indice; i < (*qtdSessoes) - 1; i++){
            lista[i] = lista[i+1];
        }
        (*qtdSessoes)--;

        printf("============================================================\n");
        printf("  Sessao removida com sucesso! [Enter] para continuar...\n");
        printf("============================================================\n");
        while (getchar() != '\n');
        getchar();
    }else{
        printf("============================================================\n");
        printf("     Operacao cancelada. A sessao NAO foi removida.\n");
        printf("            [Enter] para retornar ao menu...\n");
        printf("============================================================\n");
        while (getchar() != '\n');
        getchar();
    }
}

void modificar_sessao(Sessoes *lista, int qtdSessoes){
    int id, indice, op;

    limparTela();
    printf("===============================================\n");
    printf("              Alteracao de sessao\n");
    printf("===============================================\n\n");
    printf("   Digite o ID da sessao que deseja alterar:\n");
    printf("\n---------------------------------------------\n");
    printf("ID: ");
    scanf("%d", &id);

    indice = buscaSessao(lista, id, qtdSessoes);
    if(indice == -1){
        printf("Sessao nao encontrada!\n");
        while(getchar() != '\n');
        getchar();
        return;
    }

    do{
        printf("===============================================================\n");
        printf("                   Sessao encontrada: (ID: %d)\n", lista[indice].id);
        printf("===============================================================\n\n");
        printf("[1] - Filme:        %s\n", lista[indice].nome_filme);
        printf("[2] - Data:         %s\n", lista[indice].data);
        printf("[3] - Horario:      %s\n", lista[indice].horario_inicio);
        printf("[4] - valor:        R$ %.2f\n", lista[indice].valorIngresso);
        printf("[5] - Idade Minima: %d anos\n", lista[indice].limIdade);
        printf("[6] - Sair/Concluir\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        scanf("%d", &op);
        while(getchar() != '\n');

        switch(op){
            case 1:
                printf("===============================================\n");
                printf("          Alterando sessao (ID: %d)\n", lista[indice].id);
                printf("===============================================\n\n");
                printf("         Digite novo nome do filme:\n");
                printf("\n---------------------------------------------\n");
                printf("Nome do Filme: ");
                fgets(lista[indice].nome_filme, 50, stdin);
                lista[indice].nome_filme[strcspn(lista[indice].nome_filme, "\n")] = '\0';
                break;

            case 2: {
                int dataOK = 0;
                do{
                    printf("===============================================\n");
                    printf("            Alterando sessao (ID: %d)\n", lista[indice].id);
                    printf("===============================================\n\n");
                    printf("          Digite nova data (DD/MM/AA):\n");
                    printf("\n---------------------------------------------\n");
                    printf("Data: ");
                    scanf("%8s", lista[indice].data);
                    while (getchar() != '\n');

                    if(strlen(lista[indice].data) == 8 && lista[indice].data[2] == '/' && lista[indice].data[5] == '/'){
                        dataOK = 1;
                    } else{
                        printf("ERRO: Formato de data invalido! Use DD/MM/AA.\n");
                    }
                }while(!dataOK);
                break;
            }

            case 3: {
                int horaOK = 0;
                int h, m;
                do{
                    printf("===============================================\n");
                    printf("          Alterando sessao (ID: %d)\n", lista[indice].id);
                    printf("===============================================\n\n");
                    printf("         Digite novo horario (HH:MM):\n");
                    printf("\n---------------------------------------------\n");
                    printf("Horario: ");
                    scanf("%5s", lista[indice].horario_inicio);
                    while (getchar() != '\n');

                    if(sscanf(lista[indice].horario_inicio, "%d:%d", &h, &m) == 2){
                        if(h >= 0 && h <= 23 && m >= 0 && m <= 59 && lista[indice].horario_inicio[2] == ':'){
                            horaOK = 1;
                        }
                    }
                    if(!horaOK){
                        printf("ERRO: Horario invalido! Use HH:MM (00:00 as 23:59).\n");
                    }
                } while (!horaOK);
                break;
            }

            case 4:
                printf("===============================================\n");
                printf("          Alterando sessao (ID: %d)\n", lista[indice].id);
                printf("===============================================\n\n");
                printf("            Digite novo valor R$:\n");
                printf("\n---------------------------------------------\n");
                printf("Valor R$: ");
                scanf("%f", &lista[indice].valorIngresso);
                break;

            case 5:
                printf("===============================================\n");
                printf("          Alterando sessao (ID: %d)\n", lista[indice].id);
                printf("===============================================\n\n");
                printf("          Digite nova idade minima:\n");
                printf("\n---------------------------------------------\n");
                printf("Idade minima: ");
                scanf("%d", &lista[indice].limIdade);
                break;

            case 6:
                printf("\nAlteracoes finalizadas.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                getchar();
        }

        if(op >= 1 && op <= 5){
            printf("============================================================\n");
            printf("     Campo alterado com sucesso! [Enter] para continuar.\n");
            printf("============================================================\n");
            while (getchar() != '\n');
            getchar();
        }
    }while (op != 6);
}

void visualizar_sessao_id(Sessoes *lista, int qtdSessoes){
    int id, indice;

    limparTela();
    printf("===============================================\n");
    printf("              Consultar sessao por ID\n");
    printf("===============================================\n\n");
    printf("  Digite o ID da sessao que deseja vizualizar:\n");
    printf("\n---------------------------------------------\n");
    printf("ID: ");
    scanf("%d", &id);
    while(getchar() != '\n');

    indice = buscaSessao(lista, id, qtdSessoes);

    if(indice == -1){
        printf("\nERRO: Sessao com ID %d nao encontrada\n", id);
    } else{
        limparTela();
        printf("===============================================\n");
        printf("      Dados da sessão ID: %d encontrados\n", id);
        printf("===============================================\n\n");
        printf("Filme:        %s\n", lista[indice].nome_filme);
        printf("Data:         %s\n", lista[indice].data);
        printf("Horario:      %s\n", lista[indice].horario_inicio);
        printf("valor:        R$ %.2f\n", lista[indice].valorIngresso);
        printf("Idade Minima: %d anos\n", lista[indice].limIdade);
        printf("Sala:         %d\n", lista[indice].sala);
        printf("===============================================\n");
    }

    printf("\n[Enter] para continuar...\n");
    while(getchar() != '\n');
    getchar();
}

void visualizar_todas_sessoes(Sessoes *lista, int qtdSessoes){

    limparTela();
    printf("===============================================\n");
    printf("             Listagem de sessoes\n");
    printf("===============================================\n\n");

    if(qtdSessoes == 0){
        printf("Nenhuma sessao cadastrada!\n");
    } else {
        for(int i = 0; i < qtdSessoes; i++){
            printf("===============================================\n");
            printf("        Todas as sessoes encontradas\n");
            printf("===============================================\n\n");
            printf("ID:           %03d\n", lista[i].id);
            printf("Filme:        %-20s\n", lista[i].nome_filme);
            printf("Data:         %s\n", lista[i].data);
            printf("Horario:      %s\n", lista[i].horario_inicio);
            printf("valor:        R$ %.2f\n", lista[i].valorIngresso);
            printf("Idade Minima: %d anos\n", lista[i].limIdade);
            printf("Sala:         %d\n", lista[i].sala);
            printf("===============================================\n");
        }
    }
    printf("\nPressione [Enter] para retornar ao menu...\n");
    while(getchar() != '\n');
    getchar();
}
