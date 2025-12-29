//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//-----------------------{ CRUD PARA STRUCT RESERVAS }-------------------------
//-----------------------------------------------------------------------------

#ifndef CRUD_RESERVAS_H  // Guardas de inclusão (evita erro de redefinição)
#define CRUD_RESERVAS_H

#include "structs.h" // Precisa conhecer a struct Reserva e Usuarios

// --- CRUD RESERVA (Estrutura 3 - Relacional) ---
int menu_CRUD_reservas();
void adicionar_reserva();
void excluir_reserva();
void modificar_reserva();
void visualizar_reserva_id(Reservas *reserva, int qtdReservas, Usuarios *usuarios);
void visualizar_todas_reservas(); //declarar funções do crud

#endif
