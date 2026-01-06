#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "cons_rel.h"
#include "structs.h"

void CONS_reservas_por_filme(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
   
    char nome_do_filme[50];
    int flag=0;
    do{
        limparTela(); 

        printf("===============================================================\n");
        printf("                       Consulta De Reserva\n");
        printf("                        Pelo Nome Do Filme\n");
        printf("===============================================================\n\n");
   
        printf("---------------------------------------------------------------\n");
        printf("Digite o nome do filme (ou digite 'q' para sair): ");

        scanf(" %[^\n]", nome_do_filme);

        if(nome_do_filme[0] == 'q') confirmarRetorno();
        for(int i = 0; i < qtdSessoes; i++){
            if(strcmp(nome_do_filme, listaSessoes[i].nome_filme) == 1){
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
        if(strcmp(nome_do_filme, listaSessoes[i].nome_filme) == 1){
            indice_sessoes[j] == i;
            j++;
        }
    }
    for(int i = 0, j = 0; i < qtdReservas; i++){
        if(listaReservas[i].id_sessao == listaSessoes[indice_sessoes[j]].id){
            j++;
            printf("\n==========================================================\n");
            printf("                  Reserva de ID %d\n", i);
            printf("==========================================================\n");
            printf("CPF: %s.\n", reservas[resultado_validacao].cpf_usuario);
            printf("ID: %d.\n", reservas[resultado_validacao].id);
            printf("ID Sessão: %d.\n", reservas[resultado_validacao].id_sessao);
            printf("Assento: %s.\n", reservas[resultado_validacao].assento);

        }
    }
}