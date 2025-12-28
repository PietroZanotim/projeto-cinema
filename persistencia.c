#include "structs.h"
#include <string.h>
#include <stdio.h>

// fwrite: copia da memória para o arquivo
// fread: copia do arquivo para a memória

//------------------------------------
//-------{ Carregar Usuarios }--------
//------------------------------------
int carregar_usuarios(Usuarios *listaUsuarios){
    FILE *p_usuarios_bin;
    p_usuarios_bin = fopen("usuarios.bin", "rb");

    int qtdUsuarios_bin = 1;

    if(p_usuarios_bin == NULL) {    
        // Se não tiver um arquivo .bin, crie um (write mode)
        p_usuarios_bin = fopen("usuarios.bin", "wb");
        
        // Sistema temporário para acessar o admin
        strcpy(listaUsuarios[0].nome, "Admin");
        strcpy(listaUsuarios[0].cpf, "000.000.000-00");
        strcpy(listaUsuarios[0].senha, "123senha");
        listaUsuarios[0].saldo = 1000.00;
        listaUsuarios[0].idade = 30;
        
        // Escreva o cabeçalho (a quantidade)
        fwrite(&qtdUsuarios_bin, sizeof(int), 1, p_usuarios_bin);

        // Escreva o admin (o dado)
        fwrite(listaUsuarios, sizeof(Usuarios), 1, p_usuarios_bin);

        fclose(p_usuarios_bin);
    }
    else {
        // Trazer os dados do disco rígido para a RAM
        // Parâmetros: destino, tamanho em bytes, quantidade, ponteiro do arquivo
        fread(&qtdUsuarios_bin, sizeof(int), 1, p_usuarios_bin);
        fread(listaUsuarios, sizeof(Usuarios), qtdUsuarios_bin, p_usuarios_bin);

        fclose(p_usuarios_bin);
    }

    return qtdUsuarios_bin;
}

//------------------------------------
//--------{ Carregar Sessoes }--------
//------------------------------------
int carregar_sessoes(Sessoes *listaSessoes){
    FILE *p_sessoes_bin;
    p_sessoes_bin = fopen("sessoes.bin", "rb");

    int qtdSessoes_bin = 0;

    // Trazer os dados do disco rígido para a RAM
    if(p_sessoes_bin != NULL){
        fread(&qtdSessoes_bin, sizeof(int), 1, p_sessoes_bin);
        fread(listaSessoes, sizeof(Sessoes), qtdSessoes_bin, p_sessoes_bin);
        fclose(p_sessoes_bin);
    }

    return qtdSessoes_bin;
}

//------------------------------------
//-------{ Carregar Reservas }--------
//------------------------------------
int carregar_reservas(Reservas *listaReservas){
    FILE *p_reservas_bin;
    p_reservas_bin = fopen("reservas.bin", "rb");

    int qtdReservas_bin = 0;

    // Trazer os dados do disco rígido para a RAM
    if(p_reservas_bin != NULL){
        fread(&qtdReservas_bin, sizeof(int), 1, p_reservas_bin);
        fread(listaReservas, sizeof(Reservas), qtdReservas_bin, p_reservas_bin);
        fclose(p_reservas_bin);
    }

    return qtdReservas_bin;
}

//------------------------------------
//--------{ Salvar Usuarios }---------
//------------------------------------
void salvar_usuarios(Usuarios *lista, int qtd){
    FILE *p_bin;
    p_bin = fopen("usuarios.bin", "wb"); // Modo escrita

    // Protocolo de comunicacao (Header) - Primeira informacao será um int
    fwrite(&qtd, sizeof(int), 1, p_bin);
    fwrite(lista, sizeof(Usuarios), qtd, p_bin);
    fclose(p_bin);
}

//------------------------------------
//--------{ Salvar Sessoes }----------
//------------------------------------
void salvar_sessoes(Sessoes *lista, int qtd){
    FILE *p_bin;
    p_bin = fopen("sessoes.bin", "wb"); // Modo escrita

    // Protocolo de comunicacao (Header) - Primeira informacao será um int
    fwrite(&qtd, sizeof(int), 1, p_bin);
    fwrite(lista, sizeof(Sessoes), qtd, p_bin);
    fclose(p_bin);
}

//------------------------------------
//--------{ Salvar Reservas }---------
//------------------------------------
void salvar_reservas(Reservas *lista, int qtd){
    FILE *p_bin;
    p_bin = fopen("reservas.bin", "wb"); // Modo escrita

    // Protocolo de comunicacao (Header) - Primeira informacao será um int
    fwrite(&qtd, sizeof(int), 1, p_bin);
    fwrite(lista, sizeof(Reservas), qtd, p_bin);
    fclose(p_bin);
}

void finalizar_sistema(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
    salvar_usuarios(listaUsuarios, qtdUsuarios);
    salvar_sessoes(listaSessoes, qtdSessoes);
    salvar_reservas(listaReservas, qtdReservas);
}