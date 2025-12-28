//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//---------------------------{ FUNCOES DO ADMIN }------------------------------
//-----------------------------------------------------------------------------

#ifndef PERSISTENCIA_H  // Guardas de inclusão (evita erro de redefinição)
#define PERSISTENCIA_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// --- PERSISTÊNCIA (Requisito 3) ---
// Funções para carregar/salvar os vetores em arquivos binários
int inicializar_sistema(Usuarios *lista); // Pode englobar os carregamentos
void finalizar_sistema();   // Pode englobar os salvamentos

#endif