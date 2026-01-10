//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE SUSUÁRIO }-------------
//-----------------------------------------------------------------------------

#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// Protótipos
// Note que agora passamos o vetor e a quantidade para as funcoes
int buscaCpfCadastro(Usuarios *lista, int qtdUsuarios, char *cpfTemp);
int validarCPF(Usuarios *lista, int qtdUsuarios, char *destCpf, int modoCadastro);
int login(Usuarios *lista, int qtdUsuarios);
void cadastro(Usuarios *lista, int *qtdUsuarios, int max);
int menuLogin(Usuarios *usuario, int indiceUsuario);
void verSaldo(Usuarios *usuario, int indiceUsuario);
void modificarSenha(Usuarios *Usuarios, int indiceUsuario);
void exclusaoUsuario(Usuarios *usuario, int indiceUsuario, int *qtdUsuario, char *exclusaoBreak);
void visualizarReservas(Reservas *reservas, int qtdReservas,  Usuarios *usuarios, int indiceUsuario, Sessoes *sessoes, int qtdSessoes);

#endif