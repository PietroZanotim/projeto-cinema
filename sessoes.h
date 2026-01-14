//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE SESSOES }--------------
//-----------------------------------------------------------------------------

#ifndef SESSOES_H  // Guardas de inclusão (evita erro de redefinição)
#define SESSOES_H

#include "structs.h" // Precisa conhecer a struct Usuarios

void listarSessoes(Sessoes *sessao, int quantidadeSessoes, Usuarios *usuario, int indiceUsuario, Reservas *reserva, int *qtdReservas, int *qtdIdReservas);
int buscaSessao(Sessoes *sessao,int id, int qtdSessoes);
int converteLinhaAssento(char linha);

#endif