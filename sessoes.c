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

void listarSessoes(Sessoes *sessao, int quantidadeSessoes, Usuarios *usuario, int indiceUsuario, Reservas *reserva, int *qtdReservas, int *qtdIdReservas){

    printf("===============================================================\n");
    printf("                      SESSOES DISPONÍVEIS:");
    printf("\n===============================================================\n");

    if(quantidadeSessoes==0){
        printf("\nSentimos muito... Nenhum filme disponivel no momento.\n");
        printf("\n[Enter] para retornar ao menu login...");
        getchar();
    }
    else{
        for(int i=0; i<quantidadeSessoes; i++){
            printf("Filme: %s - Id: %d | Idade Minima: %d\n", sessao[i].nome_filme, sessao[i].id, sessao[i].limIdade);
            printf("Data: %s | Horario: %s - %s\n", sessao[i].data, sessao[i].horario_inicio, sessao[i].horario_final);
            printf("Sala: %d\n", sessao[i].sala);
            printf("Valor: %.2lf\n", sessao[i].valorIngresso);
            printf("Assentos:\n");

            char Linha[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

            for(int L = 0; L < 10; L++){
                for(int C = 0; C < 10; C++){
                    if(C != 9){
                        if(sessao[i].assento[L][C] == '0'){
                            printf("%c%d     ",Linha[L],C);
                        }else{
                            printf("X     ");
                        }
                    }else{
                        if(sessao[i].assento[L][C] == '0'){
                            printf("%c%d\n",Linha[L],C);
                        }else{
                            printf("X\n");
                        }
                    }
                }
            }
            printf("_________________________________________________________________\n");
            printf("                             TELA\n\n\n");
        }
        char resposta;

        do{
            printf("\nDeseja comprar um ingresso? (S/N): ");
            if(scanf(" %c", &resposta) != 1){
                resposta = ' '; // Define como inválido se o scanf falhar
            }

            // Limpa o buffer de entrada para a próxima iteração
            while(getchar() != '\n');

            resposta = toupper(resposta); // Converte para maiúsculo

            if(resposta != 'S' && resposta != 'N'){
                printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
                while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
                getchar(); // Aguarda o usuário pressionar Enter
            }

        }while(resposta != 'S' && resposta != 'N');

        char opcao; //Variavel usada para validar a saida do usuario e a leitura do id

        if(resposta=='S'){
            int indiceSessao;
            char linhaAssento;
            int linhaAssentoInt; //Usado apenas para preencher a posição da matriz;
            int colunaAssento;

            printf("\nDigite o id do filme (Digite 'q', para sair): ");

            do{
                scanf(" %c", &opcao);

                if(opcao=='q' || opcao=='Q'){
                    opcao = toupper(opcao);
                    break;
                }
                else{

                    int id = opcao - '0';

                    indiceSessao = buscaSessao(sessao, opcao, quantidadeSessoes);

                    if(indiceSessao==-1){
                        printf("\nId não localizado, digite novamente.\nDigite o id do filme: ");
                    }else if(usuario[indiceUsuario].idade < sessao[indiceSessao].limIdade){
                        printf("\nIdade não permitida para este filme, tente novamente.\nDigite o id do filme: ");
                        indiceSessao=-1;
                    }else if(usuario[indiceUsuario].saldo < sessao[indiceSessao].valorIngresso){
                        printf("\nNão foi possível adquirir o ingresso, valor insuficiente. Tente novamente.\nDigite o id do filme: ");
                        indiceSessao=-1;
                    }
                }
            }while(indiceSessao==-1);

            if(!(opcao=='q' || opcao=='Q')) { //Se o usuario optou por sair já finaliza;
                do{
                    do{
                        printf("\nDigite a linha do assento desejado (Ex.A): ");
                        scanf(" %c", &linhaAssento);
                        linhaAssento = toupper(linhaAssento);

                        if(linhaAssento<'A' || linhaAssento>'J') {
                            printf("Linha de assento inválida!");
                        }
                    }while(linhaAssento<'A' || linhaAssento>'J');

                    int linhaAssentoInt = converteLinhaAssento(linhaAssento);

                    do{
                        printf("\nDigite a coluna do assento desejado (Ex.1): ");
                        scanf("%d", &colunaAssento);

                        if(colunaAssento<0 || colunaAssento>9){
                            printf("Coluna de assento inválida!");
                        }

                    }while(colunaAssento<0 || colunaAssento>9);

                    if(sessao[indiceSessao].assento[linhaAssentoInt][colunaAssento]=='1'){
                        printf("Sentimos muito, este assento está ocupado...\n");
                    }

                    //Assentos com o char "O" estarão livres, e os com "1", ocupados;
                }while (sessao[indiceSessao].assento[linhaAssentoInt][colunaAssento]=='1');

                usuario[indiceUsuario].saldo -= sessao[indiceSessao].valorIngresso; // Dando baixa no saldo do usuário;

                reserva[*qtdReservas].id = *qtdIdReservas; // Adiciona o id à reserva;
                (*qtdIdReservas)++;

                reserva[*qtdReservas].id_sessao = sessao[indiceSessao].id;
                strcpy(reserva[*qtdReservas].cpf_usuario, usuario[indiceUsuario].cpf);

                reserva[*qtdReservas].assento[0] = linhaAssento; // Primeiro copio a linha, (Ex.A);

                // Logo depois concateno com a colunaAssento transformada em char;
                reserva[*qtdReservas].assento[1] = (char)colunaAssento;

                //Incremento a qtdReservas cadastradas;
                (*qtdReservas)++;

                limparTela();
                printf("==============================================\n");
                printf("      Ingresso adquirido com sucesso!");
                printf("\n==============================================\n");
                printf("\n[Enter] para retornar ao menu login...");
                getchar(); // Aguarda o usuário enviar o enter
            }
        }

        if(resposta=='S' || opcao=='Q'){
            limparTela();
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            printf("\n[Enter] para retornar ao menu login...");
            getchar(); // Aguarda o usuário enviar o enter
        }
    }
}

int converteLinhaAssento(char linha){
    switch(linha){
        case 'A': return 0; break;
        case 'B': return 1; break;
        case 'C': return 2; break;
        case 'D': return 3; break;
        case 'E': return 4; break;
        case 'F': return 5; break;
        case 'G': return 6; break;
        case 'H': return 7; break;
        case 'I': return 8; break;
        case 'J': return 9; break;
    }
}
