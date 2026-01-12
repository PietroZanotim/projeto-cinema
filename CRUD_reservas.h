//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//-----------------------{ CRUD PARA STRUCT RESERVAS }-------------------------
//-----------------------------------------------------------------------------

#ifndef CRUD_RESERVAS_H  // Guardas de inclusão (evita erro de redefinição)
#define CRUD_RESERVAS_H

#include "structs.h" // Precisa conhecer a struct Reserva e Usuarios
#include "reservas.h"

// --- CRUD RESERVA (Estrutura 3 - Relacional) ---
int menu_CRUD_reservas();
void adicionar_reserva(Reservas *reservas, int *qtdReservas, Usuarios *usuarios, int qtdUsuarios, Sessoes *sessoes, int qtdSessoes);
void excluir_reserva(Reservas *reservas, int *qtdReservas, Usuarios *usuarios);
void modificar_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, Sessoes *sessoes, int qtdSessoes);
void visualizar_reserva_id(Reservas *reserva, int qtdReservas, Usuarios *usuarios);
void visualizar_todas_reservas(Reservas *reserva, int qtdReservas, Usuarios *usuarios); //declarar funções do crud

#endif
