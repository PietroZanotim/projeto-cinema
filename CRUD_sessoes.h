//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------------------{ CRUD PARA A SCTRUC SESSOES }-------------------------
//-----------------------------------------------------------------------------

#ifndef CRUD_SESSOES_H  // Guardas de inclusão (evita erro de redefinição)
#define CRUD_SESSOES_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// --- CRUD SESSÃO (Estrutura 1) ---
int menu_CRUD_sessoes();
void adicionar_sessao();
void excluir_sessao();
void modificar_sessao();
// Nota: Visualizar Sessão está em outro arquivo.


#endif