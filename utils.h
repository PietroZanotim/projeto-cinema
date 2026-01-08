//---------------------------!! SOBRE O ARQUIVO !!-----------------------------
//-----------{ FUNCOES QUE NÃO POSSUEM COMO PARAMETRO O USUÁRIO }-------------
//-----------------------------------------------------------------------------


#ifndef UTILS_H
#define UTILS_H

void limparTela();
void saberHorarios();
void saberFilmes();
int menuPrincipal();
int confirmarSaida();
int confirmarRetorno();
int voltar();
int saberFuncionalidade();
int saberMais();
int validarInput(int tamanhoMenu);
int validar_formato_data(char* data);

// Adicionar
int buscar_indice_sessao(int id_sessao);
int buscar_indice_usuario(char* cpf);


#endif
