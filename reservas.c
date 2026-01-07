//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE RESERVA }--------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reservas.h"

int buscar_indice_reserva(Reservas *reservas, int qtdReservas, int idProcurado){ //codar as fun��es previamente declaradas em reserva.h
    int i;
    for(i=0; i<qtdReservas; i++){
        if(reservas[i].id_sessao == idProcurado){
            return i; //indice da reserva
        }
    }
    return -1;
}

void imprimir_dados_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("==========================================================\n");
    printf("           Reserva:\n");
    printf("==========================================================\n");
    printf("Nome: %s.\n", usuarios[indice].nome);
    printf("CPF: %s.\n", reservas[indice].cpf_usuario);
    printf("ID: %d.\n", reservas[indice].id);
    printf("ID Sessão: %d.\n", reservas[indice].id_sessao);
    printf("Assento: %s.\n", reservas[indice].assento);
}

void modificarNome(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    Usuarios temp;

    printf("\n==============================================\n");
    printf("              Modificar Nome\n");
    printf("\n==============================================\n");
    printf("              Insira o novo Nome\n");
    printf("\n----------------------------------------------\n");
    printf("Nome: ");

    while (getchar() != '\n');
    fgets(temp.nome, sizeof(temp.nome), stdin);
    temp.nome[strcspn(temp.nome, "\n")] = '\0'; // Boa prática limpar o \n
    usuarios[indice].nome[strcspn(usuarios[indice].nome, "\n")] = '\0';

    printf("\n----------------------------------------------\n");
    printf("              Nome Modificado com Sucesso!\n");
    printf("             Pressione ENTER para continuar.\n");
    printf("\n----------------------------------------------\n");
    getchar();
}

void modificarCPF(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    Usuarios temp;

    printf("\n==============================================\n");
    printf("                Modificar CPF\n");
    printf("\n==============================================\n");
    printf(" Digite o novo CPF neste formato XXX.XXX.XXX-XX\n");
    printf("\n-----------------------------------------------\n");
    printf("CPF: ");


}

void modificarID(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("\n----------------------------------------------\n");
    printf("              Modificar ID\n");
    printf("\n----------------------------------------------\n");
}

void modificarIDsessao(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("\n----------------------------------------------\n");
    printf("              Modificar ID Sessão\n");
    printf("\n----------------------------------------------\n");
}

void modificarAssento(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("\n----------------------------------------------\n");
    printf("              Modificar Assento\n");
    printf("\n----------------------------------------------\n");
}
