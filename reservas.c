//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE RESERVA }--------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
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
