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
    char data[11]; 

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
        
        int resultado_validacao = validar_formato_data(data); 
        
        if (resultado_validacao == -1) {
            printf("\nErro: Tamanho incorreto. Digite 8 digitos (Ex: 01/01/24).\n");
            getchar(); getchar(); 
        } 
        else if (resultado_validacao == -2) {
            printf("\nErro: Faltam as barras. Use o formato XX/XX/XX.\n");
            getchar(); getchar();
        } 
        else if (resultado_validacao == -3) {
            printf("\nErro: Digite apenas numeros e barras.\n");
            getchar(); getchar();
        }
        // NOVOS TRATAMENTOS DE ERRO
        else if (resultado_validacao == -4) {
            printf("\nErro: Dia invalido! Digite entre 01 e 31.\n");
            getchar(); getchar();
        }
        else if (resultado_validacao == -5) {
            printf("\nErro: Mes invalido! Digite entre 01 e 12.\n");
            getchar(); getchar();
        }

    } while(resultado_validacao != 0);

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

int menu_consulta(){
    int opcao;
    do {
        // limparTela(); 
        printf("=======================================================\n");
        printf("                    MENU DE CONSULTAS       \n");
        printf("=======================================================\n");
        printf("Escolha o filtro para a consulta:\n");
        printf("1. Filtrar por Nome do Filme\n");
        printf("2. Filtrar por Data da Sessao\n");
        printf("3. Filtrar por CPF do Cliente\n");
        printf("4. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 4) {
            printf("Opcao invalida!\n");
        }
    } while (opcao < 1 || opcao > 4);

    return opcao;
}

// ===============================================
// ================= RELATÓRIOS ==================
// ===============================================

void REL_listar_usuarios(Usuarios *listaUsuarios, int qtdUsuarios) {
    // 1. Abrir o arquivo em modo de escrita texto ("w")
    FILE *f_relatorio;
    f_relatorio = fopen("relatorio_clientes.txt", "w");

    if (f_relatorio == NULL) {
        printf("Erro ao criar o arquivo de relatório!\n");
        return;
    }

    // 2. Cabeçalho (Note que usamos fprintf em vez de printf)
    fprintf(f_relatorio, "=========================================================================\n");
    fprintf(f_relatorio, "                        RELATORIO GERAL DE USUARIOS                      \n");
    fprintf(f_relatorio, "=========================================================================\n");
    // Aqui usamos espaçamento fixo para criar colunas:
    // %-30s = String alinhada à esquerda com 30 espaços
    // %-15s = String alinhada à esquerda com 15 espaços
    fprintf(f_relatorio, " %-30s | %-15s | %-5s | %s\n", "NOME", "CPF", "IDADE", "SALDO");
    fprintf(f_relatorio, "-------------------------------------------------------------------------\n");

    // 3. Loop de Dados
    for (int i = 0; i < qtdUsuarios; i++) {
        fprintf(f_relatorio, " %-30s | %-15s | %-5d | R$ %.2f\n", 
                listaUsuarios[i].nome, 
                listaUsuarios[i].cpf, 
                listaUsuarios[i].idade, 
                listaUsuarios[i].saldo);
    }

    // 4. Rodapé (Resumo)
    fprintf(f_relatorio, "-------------------------------------------------------------------------\n");
    fprintf(f_relatorio, "Total de Registros: %d\n", qtdUsuarios);
    fprintf(f_relatorio, "=========================================================================\n");

    // 5. Fechar o arquivo
    fclose(f_relatorio);

    // Feedback visual para o usuário NA TELA (printf normal)
    printf("\nSucesso! O arquivo 'relatorio_clientes.txt' foi gerado na pasta do projeto.\n");
    
    // Pausa para o usuário ler
    printf("Pressione ENTER para voltar...");
    while(getchar() != '\n');
    getchar();
}


void REL_listar_sessoes(Sessoes *listaSessoes, int qtdSessoes){
    // Abrir o arquivo em modo de escrita texto ("w")
    FILE *f_relatorio;
    f_relatorio = fopen("relatorio_sessoes.txt", "w");

    if (f_relatorio == NULL) {
        printf("Erro ao criar o arquivo de relatório!\n");
        return;
    }

    fprintf(f_relatorio, "======================================================================================================================================\n");
    fprintf(f_relatorio, "                                                      RELATORIO GERAL DE SESSOES                                                      \n");
    fprintf(f_relatorio, "======================================================================================================================================\n");
    
    fprintf(f_relatorio, " %-4s | %-25s | %-17s | %-23s | %-10s | %-4s | %-17s | %-15s \n", 
            "ID", "NOME DO FILME", "HORARIO DE INICIO", "HORARIO DE ENCERRAMENTO", "DATA", "SALA", "VALOR DO INGRESSO", "LIMITE DE IDADE");
            
    fprintf(f_relatorio, "--------------------------------------------------------------------------------------------------------------------------------------\n");

    // Loop de Dados
    for (int i = 0; i < qtdSessoes; i++) {
        // Atenção à ordem dos campos e aos tipos (%d para int, %s para char, %f para float)
        fprintf(f_relatorio, " %-4d | %-25s | %-17s | %-23s | %-10s | %-4d | R$ %-14.2f | %-15d \n", 
                listaSessoes[i].id, 
                listaSessoes[i].nome_filme, 
                listaSessoes[i].horario_inicio, 
                listaSessoes[i].horario_final,
                listaSessoes[i].data,
                listaSessoes[i].sala,
                listaSessoes[i].valorIngresso,
                listaSessoes[i].limIdade);
    }

    // Rodapé (Resumo)
    fprintf(f_relatorio, "--------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(f_relatorio, "Total de Registros: %d\n", qtdSessoes);
    fprintf(f_relatorio, "======================================================================================================================================\n");

    // Fechar o arquivo
    fclose(f_relatorio);

    printf("\nSucesso! O arquivo 'relatorio_sessoes.txt' foi gerado na pasta do projeto.\n");
    
    // Pausa para o usuário ler
    printf("Pressione ENTER para voltar...");
    while(getchar() != '\n');
    getchar();
}



void RELATORIO_reservas_completo(Usuarios *listaUsuarios, int qtdUsuarios, 
                                 Sessoes *listaSessoes, int qtdSessoes, 
                                 Reservas *listaReservas, int qtdReservas) {
    
    int opcao = 0;
    char filtro_texto[50]; // Serve para Nome do Filme, CPF ou Data
    char titulo_relatorio[100];

    // --- MENU DE ESCOLHA DO FILTRO (Requisito: Pelo menos 3 opções) ---
    do {
        // limparTela(); 
        printf("=======================================================\n");
        printf("          GERACAO DE RELATORIO DE RESERVAS (TXT)       \n");
        printf("=======================================================\n");
        printf("Escolha o filtro para o relatorio:\n");
        printf("1. Filtrar por Nome do Filme\n");
        printf("2. Filtrar por Data da Sessao\n");
        printf("3. Filtrar por CPF do Cliente\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) return;
        if (opcao < 1 || opcao > 3) {
            printf("Opcao invalida!\n");
        }
    } while (opcao < 1 || opcao > 3);

    // --- CAPTURA DO DADO DE FILTRO ---
    printf("-------------------------------------------------------\n");
    if (opcao == 1) {
        printf("Digite o Nome do Filme exato: ");
        scanf(" %[^\n]", filtro_texto);
        sprintf(titulo_relatorio, "FILTRADO POR FILME: %s", filtro_texto);
    } 
    else if (opcao == 2) {
        printf("Digite a Data (DD/MM/AAAA): ");
        scanf(" %[^\n]", filtro_texto); // Aqui você pode usar sua validação de data se quiser
        sprintf(titulo_relatorio, "FILTRADO POR DATA: %s", filtro_texto);
    } 
    else if (opcao == 3) {
        printf("Digite o CPF do Cliente: ");
        scanf(" %[^\n]", filtro_texto);
        sprintf(titulo_relatorio, "FILTRADO POR CLIENTE: %s", filtro_texto);
    }

    // ABRIR ARQUIVO 
    FILE *f_rel;
    f_rel = fopen("relatorio_reservas_detalhado.txt", "w");

    if (f_rel == NULL) {
        printf("Erro fatal: Nao foi possivel criar o arquivo no disco.\n");
        return;
    }

    fprintf(f_rel, "====================================================================================================================\n");
    fprintf(f_rel, "                                          RELATORIO DETALHADO DE RESERVAS                                           \n");
    fprintf(f_rel, "                                      %s\n", titulo_relatorio);
    fprintf(f_rel, "====================================================================================================================\n");
    fprintf(f_rel, " %-4s | %-25s | %-25s | %-10s | %-5s | %-7s \n", 
            "ID", "CLIENTE (S2)", "FILME (S1)", "DATA", "HORA", "ASSENTO");
    fprintf(f_rel, "--------------------------------------------------------------------------------------------------------------------\n");

    // LOOP DE PROCESSAMENTO E "JOIN"
    int encontrou_algum = 0;
    int contador = 0;

    for (int i = 0; i < qtdReservas; i++) {
        
        // Variáveis auxiliares para guardar os dados cruzados
        Usuarios *usuarioEncontrado = NULL;
        Sessoes *sessaoEncontrada = NULL;

        // BUSCA (JOIN) 1: Achar a Sessão correspondente ao ID guardado na reserva
        for (int s = 0; s < qtdSessoes; s++) {
            if (listaSessoes[s].id == listaReservas[i].id_sessao) {
                sessaoEncontrada = &listaSessoes[s];
                break;
            }
        }

        // BUSCA (JOIN) 2: Achar o Usuário correspondente ao CPF guardado na reserva
        for (int u = 0; u < qtdUsuarios; u++) {
            if (strcmp(listaUsuarios[u].cpf, listaReservas[i].cpf_usuario) == 0) {
                usuarioEncontrado = &listaUsuarios[u];
                break;
            }
        }

        // Se por algum motivo o banco estiver inconsistente (excluiu usuario mas manteve reserva), pular
        if (usuarioEncontrado == NULL || sessaoEncontrada == NULL) continue;

        // VERIFICAÇÃO DO FILTRO ESCOLHIDO
        int deve_imprimir = 0;

        switch (opcao) {
            case 1: // Filtro por Filme (Compara string do filme na struct Sessao)
                if (strcmp(sessaoEncontrada->nome_filme, filtro_texto) == 0) deve_imprimir = 1;
                break;
            case 2: // Filtro por Data (Compara string data na struct Sessao)
                if (strcmp(sessaoEncontrada->data, filtro_texto) == 0) deve_imprimir = 1;
                break;
            case 3: // Filtro por CPF (Compara string cpf na struct Reserva ou Usuario)
                if (strcmp(listaReservas[i].cpf_usuario, filtro_texto) == 0) deve_imprimir = 1;
                break;
        }

        // ESCRITA NO ARQUIVO 
        if (deve_imprimir) {
            fprintf(f_rel, " %-4d | %-25s | %-25s | %-10s | %-5s | %-7s \n",
                    listaReservas[i].id,
                    usuarioEncontrado->nome,       // Dado vindo de S2 (Usuarios)
                    sessaoEncontrada->nome_filme,  // Dado vindo de S1 (Sessoes)
                    sessaoEncontrada->data,
                    sessaoEncontrada->horario_inicio,
                    listaReservas[i].assento);     // Dado vindo de S3 (Reservas)
            
            encontrou_algum = 1;
            contador++;
        }
    }

    // RODAPÉ 
    fprintf(f_rel, "--------------------------------------------------------------------------------------------------------------------\n");
    fprintf(f_rel, "Total de Reservas listadas: %d\n", contador);
    fprintf(f_rel, "====================================================================================================================\n");

    fclose(f_rel);

    // Feedback na tela
    if (encontrou_algum) {
        printf("\n[SUCESSO] Relatorio gerado! Verifique o arquivo 'relatorio_reservas_detalhado.txt'.\n");
    } else {
        printf("\n[AVISO] O relatorio foi gerado, mas nenhum registro foi encontrado com esse filtro.\n");
    }

    printf("Pressione ENTER para continuar...");
    while(getchar() != '\n');
    getchar();
}