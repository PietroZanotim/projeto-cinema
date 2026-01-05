//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE RESERVA }--------------
//-----------------------------------------------------------------------------

#include "structs.h"
#include "utils.h"

int buscar_indice_reserva(Reservas *reservas, int qtdReservas, int idProcurado); //declarar funções para usar em reserva.c
void imprimir_dados_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int resultado_validacao);
