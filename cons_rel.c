#include <stdio.h>
#include <string.h>
#include "utils.h"

void CONS_reservas_por_filme(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){

    char nome_do_filme[50];
    do{
        limparTela();

        printf("===============================================================\n");
        printf("                       Consulta De Reserva\n");
        printf("                        Pelo Nome Do Filme\n");
        printf("===============================================================\n\n");

        printf("---------------------------------------------------------------\n");
        printf("Digite o nome do filme (ou digite 'q' para sair): ");

        int flag = 0;

        scanf(" %[^\n]", nome_do_filme);

        if(nome_do_filme[0] == 'q') confirmarRetorno();
        for(int i = 0; i < qtdSessoes; i++){
            if(strcmp(nome_do_filme, Sessoes[i].nome_do_filme) == 1){
                flag = 1;
                break;
            }
        }
        limparTela();
        printf("Não existe um filme com esse nome\n Pressione ENTER para tentar novamente\n");
        while(getchar() != '\n');
        getchar();

    } while(flag == 0);


    int indice_sessoes[10];
    printf("!! -- Lista de até 10 Reservas -- !!\n\n");
    // Encontra todos os indices
    for(int i = 0, j = 0; i < qtdSessoes; i++){
        if(strcmp(nome_do_filme, listaSessoes[i].nome_do_filme) == 1){
            indice_sessoes[j] == i;
            j++;
        }
    }
    for(int i = 0, j = 0; i < qtdReservas; i++){
        if(listaReservas[i].id_sessao == listaSessoes[indice_sessoes[j]].id){
            j++;
            printf("\n==========================================================\n");
            printf("             Reserva de ID %d\n", i);
            printf("==========================================================\n");
            printf("CPF: %s.\n", reservas[resultado_validacao].cpf_usuario);
            printf("ID: %d.\n", reservas[resultado_validacao].id);
            printf("ID Sessão: %d.\n", reservas[resultado_validacao].id_sessao);
            printf("Assento: %s.\n", reservas[resultado_validacao].assento);

        }
    }

    void CONS_reservas_por_data(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
        char data[9];
        do{
            limparTela();

            printf("===============================================================\n");
            printf("                       Consulta De Reserva\n");
            printf("                            Pela Data\n");
            printf("===============================================================\n\n");

            printf("---------------------------------------------------------------\n");
            printf("Digite a data (ou digite 'q' para sair): ");

            int flag = 0, flag_formato = 0;

            scanf(" %[^\n]", data);
            do{
                flag_formato = validar_formato_data();
                if(flag_formato == -1) {
                    printf("Tamano da data ficou incorreto\nPressione ENTER para tentar novamente\n");
                    while(getchar != '\n');
                    getchar();
                }
                else if(flag_formato == -2) {
                    printf("O formato da data ficou incorreto. O formato é XX/XX/XX\nPressione ENTER para tentar novamente\n");
                    while(getchar != '\n');
                    getchar();
                }
                else if(flag_formato == -3) {
                    printf("Não pode digitar letras. O formato é XX/XX/XX, onde X é um número\nPressione ENTER para tentar novamente\n");
                    while(getchar != '\n');
                    getchar();
                }
            } while(flag_formato != 0);

            // A lógica abaixo nao funciona, corrigir
            if(data[0] == 'q') confirmarRetorno();
            for(int i = 0; i < qtdSessoes; i++){
                if(strcmp(nome_do_filme, Sessoes[i].nome_do_filme) == 1){
                    flag = 1;
                    break;
                }
            }
            limparTela();
            printf("Não existe alguma sessão nessa data\n Pressione ENTER para tentar novamente\n");
            while(getchar() != '\n');
            getchar();

        } while(flag == 0);

        int indice_sessoes[10];
        printf("!! -- Lista de até 10 Reservas -- !!\n\n");
        // Encontra todos os indices
        for(int i = 0, j = 0; i < qtdSessoes; i++){
            if(strcmp(nome_do_filme, listaSessoes[i].nome_do_filme) == 1){
                indice_sessoes[j] == i;
                j++;
            }
        }
        for(int i = 0, j = 0; i < qtdReservas; i++){
            if(listaReservas[i].id_sessao == listaSessoes[indice_sessoes[j]].id){
                j++;
                printf("\n==========================================================\n");
                printf("             Reserva de ID %d\n", i);
                printf("==========================================================\n");
                printf("CPF: %s.\n", reservas[resultado_validacao].cpf_usuario);
                printf("ID: %d.\n", reservas[resultado_validacao].id);
                printf("ID Sessão: %d.\n", reservas[resultado_validacao].id_sessao);
                printf("Assento: %s.\n", reservas[resultado_validacao].assento);

            }
        }

    }


    void CONS_reservas_por_cpf(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
        char cpf[14];
        do{
            limparTela();

            printf("===============================================================\n");
            printf("                       Consulta De Reserva\n");
            printf("                            Pelo CPF\n");
            printf("===============================================================\n\n");

            printf("---------------------------------------------------------------\n");
            printf("Digite a data (ou digite 'q' para sair): ");

            int flag = 0;

            scanf(" %[^\n]", cpf);

            if(cpf[0] == 'q') confirmarRetorno();
            for(int i = 0; i < qtdSessoes; i++){
                if(strcmp(nome_do_filme, Sessoes[i].nome_do_filme) == 1){
                    flag = 1;
                    break;
                }
            }
            limparTela();
            printf("Não existe um filme com esse nome\n Pressione ENTER para tentar novamente\n");
            while(getchar() != '\n');
            getchar();

        } while(flag == 0);

        int indice_sessoes[10];
        printf("!! -- Lista de até 10 Reservas -- !!\n\n");
        // Encontra todos os indices e seus respectivos IDs
        // (linha 0 -> indice | linha 1 -> ID)
        for(int i = 0, j = 0; i < qtdSessoes; i++){
            if(strcmp(nome_do_filme, listaSessoes[i].nome_do_filme) == 1){
                indice_sessoes[j] == i;
                j++;
            }
        }
        for(int i = 0, j = 0; i < qtdReservas; i++){
            if(listaReservas[i].id_sessao == listaSessoes[indice_sessoes[j]].id){
                j++;
                printf("\n==========================================================\n");
                printf("             Reserva de ID %d\n", i);
                printf("==========================================================\n");
                printf("CPF: %s.\n", reservas[resultado_validacao].cpf_usuario);
                printf("ID: %d.\n", reservas[resultado_validacao].id);
                printf("ID Sessão: %d.\n", reservas[resultado_validacao].id_sessao);
                printf("Assento: %s.\n", reservas[resultado_validacao].assento);

            }
        }

    }
}
