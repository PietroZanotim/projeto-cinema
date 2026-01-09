#include <stdio.h>
#include <string.h>
#include "utils.h"

void CONS_reservas_por_filme(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
    char nome_do_filme[50];
    int sessao_encontrada = 0;

    // 1. Loop para pegar o nome do filme válido
    do {
        limparTela();
        printf("===============================================================\n");
        printf("                       Consulta De Reserva\n");
        printf("                        Pelo Nome Do Filme\n");
        printf("===============================================================\n\n");
        printf("Digite o nome do filme (ou digite 'q' para sair): ");
        
        scanf(" %[^\n]", nome_do_filme);

        if(strcmp(nome_do_filme, "q") == 0) return; // Retorna para o menu anterior

        // Verifica se existe pelo menos uma sessão com esse filme
        sessao_encontrada = 0;
        for(int i = 0; i < qtdSessoes; i++){
            // strcmp retorna 0 se for IGUAL
            if(strcmp(nome_do_filme, listaSessoes[i].nome_do_filme) == 0){
                sessao_encontrada = 1;
                break;
            }
        }

        if(sessao_encontrada == 0){
            printf("\nNão existe nenhuma sessão com esse filme.\n");
            printf("Pressione ENTER para tentar novamente...");
            while(getchar() != '\n');
            getchar();
        }

    } while(sessao_encontrada == 0);

    // 2. Exibição das Reservas
    limparTela();
    printf("!! -- Reservas para o filme: %s -- !!\n\n", nome_do_filme);
    
    int reservas_achadas = 0;

    // Estratégia: Percorrer Reservas e verificar se a Sessão dela é do filme escolhido
    for(int i = 0; i < qtdReservas; i++){
        
        // Para cada reserva, precisamos descobrir qual é o nome do filme da sessão dela
        // Vamos procurar a sessão correspondente a esta reserva
        for(int j = 0; j < qtdSessoes; j++){
            
            // Se achamos a sessão desta reserva E o nome do filme bate
            if(listaReservas[i].id_sessao == listaSessoes[j].id && 
               strcmp(listaSessoes[j].nome_do_filme, nome_do_filme) == 0) {
                
                printf("----------------------------------------------------------\n");
                printf("Reserva ID: %d | CPF Cliente: %s\n", listaReservas[i].id, listaReservas[i].cpf_usuario);
                printf("Sessão ID: %d | Assento: %s\n", listaReservas[i].id_sessao, listaReservas[i].assento);
                printf("Data: %s | Horário: %s\n", listaSessoes[j].data, listaSessoes[j].horario);
                reservas_achadas++;
                break; // Achou a sessão, pula para a próxima reserva
            }
        }
    }

    if(reservas_achadas == 0){
        printf("\nNenhuma reserva encontrada para este filme.\n");
    }

    printf("\n\nPressione ENTER para voltar...");
    while(getchar() != '\n');
    getchar();
}

void CONS_reservas_por_data(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
    char data[11]; // Aumentei para 11 para caber o \0 com segurança (DD/MM/AAAA)
    int data_valida = 0;

    // 1. Loop para pegar a data válida
    do{
        limparTela();
        printf("===============================================================\n");
        printf("                       Consulta De Reserva\n");
        printf("                            Pela Data\n");
        printf("===============================================================\n\n");
        printf("Digite a data (DD/MM/AAAA) ou 'q' para sair: ");

        scanf(" %[^\n]", data);

        if(strcmp(data, "q") == 0) return;
        
        int ret = validar_formato_data(data); 
        
        if(ret == 0) {
            data_valida = 1;
        } else {
            printf("\nFormato inválido! Use XX/XX/XXXX.\n");
            printf("Pressione ENTER para tentar novamente...");
            while(getchar() != '\n');
            getchar();
        }

    } while(data_valida == 0);

    // 2. Exibição das Reservas
    limparTela();
    printf("!! -- Reservas para a data: %s -- !!\n\n", data);

    int reservas_achadas = 0;

    for(int i = 0; i < qtdReservas; i++){
        // Procura a sessão da reserva
        for(int j = 0; j < qtdSessoes; j++){
            // Match: ID bate E Data bate
            if(listaReservas[i].id_sessao == listaSessoes[j].id && 
               strcmp(listaSessoes[j].data, data) == 0) {
                
                printf("----------------------------------------------------------\n");
                printf("Filme: %s\n", listaSessoes[j].nome_do_filme);
                printf("Reserva ID: %d | CPF: %s\n", listaReservas[i].id, listaReservas[i].cpf_usuario);
                printf("Horário: %s | Assento: %s\n", listaSessoes[j].horario, listaReservas[i].assento);
                reservas_achadas++;
                break; 
            }
        }
    }

    if(reservas_achadas == 0){
        printf("\nNenhuma reserva encontrada nesta data.\n");
    }

    printf("\n\nPressione ENTER para voltar...");
    while(getchar() != '\n');
    getchar();
}


void CONS_reservas_por_cpf(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
    char cpf[15];
    
    limparTela();
    printf("===============================================================\n");
    printf("                       Consulta De Reserva\n");
    printf("                            Pelo CPF\n");
    printf("===============================================================\n\n");
    printf("Digite o CPF do cliente (ou 'q' para sair): ");

    scanf(" %[^\n]", cpf);

    if(strcmp(cpf, "q") == 0) return;

    // Busca direta
    printf("\n!! -- Reservas do cliente CPF: %s -- !!\n", cpf);
    
    int encontrou = 0;

    for(int i = 0; i < qtdReservas; i++){
        // Verifica se o CPF da reserva é igual ao digitado
        if(strcmp(listaReservas[i].cpf_usuario, cpf) == 0){
            
            // Opcional: Buscar dados da sessão para mostrar o nome do filme
            char nomeFilme[50] = "Desconhecido";
            char dataSessao[11] = "--/--/--";
            
            for(int s = 0; s < qtdSessoes; s++){
                if(listaSessoes[s].id == listaReservas[i].id_sessao){
                    strcpy(nomeFilme, listaSessoes[s].nome_do_filme);
                    strcpy(dataSessao, listaSessoes[s].data);
                    break;
                }
            }

            printf("\n==========================================================\n");
            printf("Reserva ID: %d\n", listaReservas[i].id);
            printf("Filme: %s\n", nomeFilme);
            printf("Data: %s\n", dataSessao);
            printf("Assento: %s\n", listaReservas[i].assento);
            printf("==========================================================\n");
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("\nNenhuma reserva encontrada para este CPF.\n");
    }

    printf("\n\nPressione ENTER para voltar...");
    while(getchar() != '\n');
    getchar();
}