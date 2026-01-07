//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE RESERVA }--------------
//-----------------------------------------------------------------------------

#include "structs.h"
#include "utils.h"

int buscar_indice_reserva(Reservas *reservas, int qtdReservas, int idProcurado); //declarar funções para usar em reserva.c
void imprimir_dados_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int resultado_validacao);
void modificarNome(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice);
void modificarCPF(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice);
void modificarID(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice);
void modificarIDsessao(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice);
void modificarAssento(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice, Sessoes *sessoes, int qtdSessoes);
