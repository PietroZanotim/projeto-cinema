//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------------------{ CRUD PARA A SCTRUC SESSOES }-------------------------
//-----------------------------------------------------------------------------

#ifndef CRUD_SESSOES_H  // Guardas de inclusão (evita erro de redefinição)
#define CRUD_SESSOES_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// --- CRUD SESSÃO (Estrutura 1) ---
int menu_CRUD_sessoes();
void adicionar_sessao(Sessoes **lista, int *qtdSessoes, int *maxSessoes);
void excluir_sessao(Sessoes *lista, int *qtdSessoes, Reservas *ListaReservas, int qtdREservas);
void modificar_sessao(Sessoes *lista, int qtdSessoes);
int buscaSessao(Sessoes *lista, int id, int qtdSessoes); // Função auxiliar (busca e retorna o id do elemento)
// Nota: Visualizar Sessão está em outro arquivo.

#endif