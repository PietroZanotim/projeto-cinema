#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h" // Precisa conhecer a struct Usuarios

// Protótipos
// Note que agora passamos o vetor e a quantidade para as funcoes
int buscaCpfCadastro(Usuarios *lista, int qtd, char *cpfTemp);
int validarCPF(Usuarios *lista, int qtd, char *destCpf, int modoCadastro);
void executarLogin(Usuarios *lista, int qtd);
void executarCadastro(Usuarios *lista, int *qtd, int max);

#endif