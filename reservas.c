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
