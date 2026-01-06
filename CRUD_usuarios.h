//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//--------------- ------{ CRUD PARA A STRUC USUARIOS }-------------------------
//-----------------------------------------------------------------------------

#ifndef CRUD_USUARIOS_H  // Guardas de inclusão (evita erro de redefinição)
#define CRUD_USUARIOS_H

#include "structs.h" // Precisa conhecer a struct Usuarios


// --- CRUD USUÁRIO (Estrutura 2) ---
int menu_CRUD_usuarios();
void adicionar_usuario(Usuarios *lista, int *qtdUsuarios, int max);
void excluir_usuario(Usuarios *lista, int *qtdUsuarios);
void modificar_usuario(Usuarios *lista, int *qtdUsuarios);
void visualizar_usuario_cpf(Usuarios *lista, int *qtdUsuarios);
void visualizar_todos_usuarios(Usuarios *lista, int qtdUsuario);


#endif