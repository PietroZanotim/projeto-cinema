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

int converteLinhaAssento(char linha){
    switch(linha){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;
        case 'I': return 8;
        case 'J': return 9;
    }
    return 0; //return para satisfazer o compilador, essa linha nunca sera executada
}

int buscaSessao(Sessoes *sessao, int id, int qtdSessoes){
    for(int i=0; i<qtdSessoes; i++){
        if(sessao[i].id==id){
            return i;
        }
    }
    return -1; // Não encontrou
}

int atribuir_ID(Sessoes *sessao, int maxSessoes){
    for(int id = 1; id < maxSessoes; id++){
        int flag_break = 0;
        for(int i = 0; i < maxSessoes; i++){
            if(sessao[i].id == id){
                flag_break = 1;
                break;
            }
        }
        if(flag_break == 0) return id; // Se não deu break, então ainda não há esse ID
    }
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
                    if(sessao[i].assento[L][C] == '0'){
                        printf("%4c%d ",Linha[L],C);
                    }else{
                        printf(" XX "); //ocupado
                    }
                }
                printf("\n");
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

        if(resposta == 'N'){
            limparTela();
            printf("Você cancelou a compra.\n");
            printf("\n[Enter] para retornar ao menu login...");
            getchar();
        }

        if(resposta=='S'){
            int indiceSessao = -1; // Inicializa com -1 para entrar no loop
            char input[20]; // Buffer para ler ID (número) ou 'q' (letra)
            int idBusca;
            int saiu = 0; //flag para controlar saida

            while(1){
                printf("\nDigite o id do filme (Digite 'q', para sair): ");
                scanf("%s", input);

                if(input[0] == 'q' || input[0] == 'Q'){
                    saiu = 1;
                    break; // Volta para o menu anterior
                }

                idBusca = input[0] - '0'; // Função para converter a string para número inteiro

                indiceSessao = buscaSessao(sessao, idBusca, quantidadeSessoes);

                if(indiceSessao==-1){
                    printf("\nId não localizado, tente novamente.\n");
                }else if(usuario[indiceUsuario].idade < sessao[indiceSessao].limIdade){
                    printf("\nIdade não permitida para este filme, tente novamente.\n");
                    indiceSessao=-1;
                }else if(usuario[indiceUsuario].saldo < sessao[indiceSessao].valorIngresso){
                    printf("\nNão foi possível adquirir o ingresso, valor insuficiente.\n");
                }else{
                    break; // ID existe, idade ok, saldo ok
                }
            }

            if(!saiu && indiceSessao != -1){
                char linhaAssento;
                int colunaAssento;
                int linhaAssentoInt;

                do{ //escolher assento
                    do{ //escolher linha
                        printf("\nDigite a linha do assento desejado (Ex.A): ");
                        scanf(" %c", &linhaAssento);
                        linhaAssento = toupper(linhaAssento);

                        if(linhaAssento<'A' || linhaAssento>'J'){
                            printf("Linha de assento inválida!\n");
                        }
                    }while(linhaAssento<'A' || linhaAssento>'J');

                    linhaAssentoInt = converteLinhaAssento(linhaAssento);

                    do{ //escolher coluna
                        printf("\nDigite a coluna do assento desejado (Ex.1): ");
                        scanf("%d", &colunaAssento);

                        if(colunaAssento<0 || colunaAssento>9){
                            printf("Coluna de assento inválida!\n");
                        }

                    }while(colunaAssento<0 || colunaAssento>9);

                    if(sessao[indiceSessao].assento[linhaAssentoInt][colunaAssento]=='1'){
                        printf("Sentimos muito, este assento está ocupado...\n");
                    }

                    //Assentos com o char "O" estarão livres, e os com "1", ocupados;
                }while(sessao[indiceSessao].assento[linhaAssentoInt][colunaAssento]=='1');

                usuario[indiceUsuario].saldo -= sessao[indiceSessao].valorIngresso; // Dando baixa no saldo do usuário
                sessao[indiceSessao].assento[linhaAssentoInt][colunaAssento] = '1'; // Ocupando o assento

                reserva[*qtdReservas].id = *qtdIdReservas; // Adiciona o id à reserva;
                (*qtdIdReservas)++;

                reserva[*qtdReservas].id_sessao = sessao[indiceSessao].id;
                strcpy(reserva[*qtdReservas].cpf_usuario, usuario[indiceUsuario].cpf);

                reserva[*qtdReservas].assento[0] = linhaAssento; // Primeiro copio a linha, (Ex.A);

                // Logo depois concateno com a colunaAssento transformada em char;
                reserva[*qtdReservas].assento[1] = colunaAssento + '0';

                //Incremento a qtdReservas cadastradas;
                (*qtdReservas)++;

                limparTela();
                printf("\n==============================================\n");
                printf("         Ingresso adquirido com sucesso!");
                printf("\n==============================================\n");
                printf("\n[Enter] para retornar ao menu login...");
                while(getchar() != '\n');
                getchar(); // Aguarda o usuário enviar o enter
            }
            else {
                limparTela();
                printf("Você cancelou a compra.\n");
                printf("\n[Enter] para retornar ao menu login...");
                while(getchar() != '\n');
                getchar();
            }
        }
    }
}
