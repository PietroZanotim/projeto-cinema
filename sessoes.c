//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE SESSOES }--------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "sessoes.h"
#include "structs.h" // Precisa conhecer a struct Sessoes

int buscaSessao(Sessoes *sessao,int id, int qtdSessoes){
    for(int i=0; i<qtdSessoes; i++){
        if(sessao[i].id==id){
            return i;
        }
    }
    return -1;
}

void listarSessoes(Sessoes *sessao, int quantidadeSessoes, Usuarios *usuario, int indiceUsuario, Reservas *reserva, int *qtdReservas){

    limparTela();

    for(int i=0; i<quantidadeSessoes; i++){

        printf("Filme: %d - Id: %d | Idade Minima: %d\n", sessao[i].nome_filme, sessao[i].id, sessao[i].limIdade);
        printf("Data: %s | Horario: %s - %s\n", sessao[i].data, sessao[i].horario_inicio, sessao[i].horario_final);
        printf("Sala: %d\n", sessao[i].sala);
        printf("Valor: %d\n", sessao[i].valorIngresso);
        printf("Assentos:\n");
        
        char Linha = {A, B, C, D, E, F, G, H, I, J};

        for(int L = 1; L <= 10; L++){
            for(int C = 1; C <= 10; C++){
                if(C != 9){
                    if(sessao[i].assento[L][C] == 0) printf("%c%d ",Linha[L],C);
                    else printf("X ");
                } else {
                    if(sessao[i].assento[L][C] == 0) printf("%c%d\n",Linha[L],C);
                    else printf("X\n");
                }
            }
        }
        printf("_________________________________________________________________\n");
        printf("                             TELA\n");
    }
        char resposta;

        do{
        printf("\nDeseja comprar um ingresso? (S/N): ");
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

    if(resposta=='S'){
        int id;
        int indiceSessao;
        int linhaAssento;
        int colunaAssento;

        printf("\nDigite o id do filme: ");
        
        do{
            scanf("%d", &id);

            indiceSessao = buscaSessao(sessao, id, quantidadeSessoes);
        
            if(indiceSessao==-1){
                printf("\nId não localizado, digite novamente.\nDigite o id do filme: ");
            } else if(usuario[indiceUsuario].idade < sessao[indiceSessao].limIdade){
                printf("\nIdade não permitida para este filme, tente novamente.\nDigite o id do filme: ");
                indiceSessao=-1;
            } else if(usuario[indiceUsuario].saldo < sessao[indiceSessao].valorIngresso){
                printf("\nNão foi possível adquirir o ingresso, valor insuficiente. Tente novamente.\nDigite o id do filme: ");
                indiceSessao=-1;
            }
        }while(indiceSessao==-1);

        do{
            printf("\nDigite a linha do assento desejado (Ex.1): ");
            scanf("%d", &linhaAssento);
            linhaAssento -= 1;

            printf("\nDigite a coluna do assento desejado (Ex.1): ");
            scanf("%d", &colunaAssento);
            colunaAssento -= 1;

            if(sessao[indiceSessao].assento[linhaAssento][colunaAssento]=='X'){ 
                printf("Sentimos muito, este assento está ocupado...\n");
            }
            //Assentos com o char "O" estarão livres, e os com "X", ocupados;
        } while (sessao[indiceSessao].assento[linhaAssento][colunaAssento]=='X');

        usuario[indiceUsuario].saldo -= sessao[indiceSessao].valorIngresso; // Dando baixa no saldo do usuário;

        reserva[*qtdReservas].id = *qtdReservas;
        reserva[*qtdReservas].id_sessao = sessao[indiceSessao].id;
        strcpy(reserva[*qtdReservas].cpf_usuario,usuario[indiceUsuario].cpf);

        //reserva[*qtdReservas].assento = ??? Devemos analisar depois como atribuir...
        
        *qtdReservas++;

        limparTela();
        printf("==============================================\n");
        printf("      Ingresso adquirido com sucesso!");
        printf("\n==============================================\n");
        printf("\n[Enter] para retornar ao menu login...");
        getchar(); // Aguarda o usuário enviar o enter

    } else {
        limparTela();
        printf("\n[Enter] para retornar ao menu login...");
        getchar(); // Aguarda o usuário enviar o enter
    }

}