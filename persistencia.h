//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//---------------------------{ FUNCOES DO ADMIN }------------------------------
//-----------------------------------------------------------------------------

#ifndef PERSISTENCIA_H  // Guardas de inclusão (evita erro de redefinição)
#define PERSISTENCIA_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// --- PERSISTÊNCIA (Requisito 3) ---
// Funções para carregar/salvar os vetores em arquivos binários
int carregar_usuarios(Usuarios *listaUsuarios);
int carregar_sessoes(Sessoes *listaSessoes);
int carregar_reservas(Reservas *listaReservas);



#endif