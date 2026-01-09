//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//------------------ -----{ CONSULTAS E RELATÓRIOS }---------------------------
//-----------------------------------------------------------------------------

#ifndef CONS_REL_H  // Guardas de inclusão (evita erro de redefinição)
#define CONS_REL_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// --- CONSULTAS NA TELA (Requisito 5f - Output Terminal) ---
// Deve mostrar dados da Reserva + Nome do Filme + Nome do Usuário
void CONS_reservas_por_filme(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas);
void CONS_reservas_por_data(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas);
void CONS_reservas_por_cpf(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas);
int menu_consulta();

// --- RELATÓRIOS EM TXT (Requisito 5g - Output Arquivo) ---
void REL_listar_usuarios(Usuarios *listaUsuarios, int qtdUsuarios);
void REL_listar_usuarios(Usuarios *listaUsuarios, int qtdUsuarios);
void RELATORIO_reservas_completo(Usuarios *listaUsuarios, int qtdUsuarios, 
                                 Sessoes *listaSessoes, int qtdSessoes, 
                                 Reservas *listaReservas, int qtdReservas);

#endif
