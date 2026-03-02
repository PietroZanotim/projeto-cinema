#include "structs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// fwrite: copia da memória para o arquivo
// fread: copia do arquivo para a memória

//------------------------------------
//-------{ Carregar Usuarios }--------
//------------------------------------
int carregar_usuarios(Usuarios **listaUsuarios, int *capacidade) {
    FILE *p_usuarios_bin = fopen("usuarios.bin", "rb");
    int qtdUsuarios_bin = 0;

    if (p_usuarios_bin == NULL) {
        *capacidade = 5;
        
        // Alocar memória via ponteiro duplo.
        *listaUsuarios = malloc((*capacidade) * sizeof(Usuarios));
        if (*listaUsuarios == NULL) {
            fprintf(stderr, "Critical: Memory allocation failed during initial user load.\n");
            exit(EXIT_FAILURE);
        }

        // Sistema temporário para acessar o admin
        qtdUsuarios_bin = 1;
        
        // Note: We dereference the double pointer first: (*listaUsuarios)[index]
        strcpy((*listaUsuarios)[0].nome, "Admin");
        strcpy((*listaUsuarios)[0].cpf, "000.000.000-00");
        strcpy((*listaUsuarios)[0].senha, "123senha");
        (*listaUsuarios)[0].saldo = 1000.00;
        (*listaUsuarios)[0].idade = 30;

        // Write the new file
        p_usuarios_bin = fopen("usuarios.bin", "wb");
        if (p_usuarios_bin != NULL) {
            fwrite(&qtdUsuarios_bin, sizeof(int), 1, p_usuarios_bin);
            fwrite(*listaUsuarios, sizeof(Usuarios), 1, p_usuarios_bin);
            fclose(p_usuarios_bin);
        }
    } 
    else {
        // File exists. Read the header (Logical Size) first.
        fread(&qtdUsuarios_bin, sizeof(int), 1, p_usuarios_bin);

        // Calculate needed capacity (Geometric growth buffer)
        // If we have 10 users, allocate space for 20. If 0, allocate 5.
        *capacidade = (qtdUsuarios_bin > 0) ? (qtdUsuarios_bin * 2) : 5;

        // Allocate the exact necessary memory based on the file's reality
        *listaUsuarios = malloc((*capacidade) * sizeof(Usuarios));
        if (*listaUsuarios == NULL) {
            fprintf(stderr, "Critical: Memory allocation failed while loading existing users.\n");
            fclose(p_usuarios_bin);
            exit(EXIT_FAILURE); 
        }

        // Safely bring data from the hard drive to the newly sized RAM block
        fread(*listaUsuarios, sizeof(Usuarios), qtdUsuarios_bin, p_usuarios_bin);
        fclose(p_usuarios_bin);
    }

    return qtdUsuarios_bin; // Return the logical size
}

//------------------------------------
//--------{ Carregar Sessoes }--------
//------------------------------------
int carregar_sessoes(Sessoes **listaSessoes, int *capacidade) {
    FILE *p_sessoes_bin = fopen("sessoes.bin", "rb");
    int qtdSessoes_bin = 0;

    if (p_sessoes_bin == NULL) {
        *capacidade = 5;
        *listaSessoes = calloc(*capacidade, sizeof(Sessoes)); // calloc for zeroed seats
        if (*listaSessoes == NULL) {
            fprintf(stderr, "Critical: Memory allocation failed for Sessoes.\n");
            exit(EXIT_FAILURE);
        }
        return 0; // No file, return 0 items
    }

    fread(&qtdSessoes_bin, sizeof(int), 1, p_sessoes_bin);
    *capacidade = (qtdSessoes_bin > 0) ? (qtdSessoes_bin * 2) : 5;

    *listaSessoes = calloc(*capacidade, sizeof(Sessoes));
    if (*listaSessoes == NULL) {
        fprintf(stderr, "Critical: Memory allocation failed for Sessoes.\n");
        fclose(p_sessoes_bin);
        exit(EXIT_FAILURE);
    }

    fread(*listaSessoes, sizeof(Sessoes), qtdSessoes_bin, p_sessoes_bin);
    fclose(p_sessoes_bin);
    return qtdSessoes_bin;
}

//------------------------------------
//-------{ Carregar Reservas }--------
//------------------------------------
int carregar_reservas(Reservas **listaReservas, int *capacidade) {
    FILE *p_reservas_bin = fopen("reservas.bin", "rb");
    int qtdReservas_bin = 0;

    if (p_reservas_bin == NULL) {
        *capacidade = 5;
        *listaReservas = malloc((*capacidade) * sizeof(Reservas));
        if (*listaReservas == NULL) {
            fprintf(stderr, "Critical: Memory allocation failed for Reservas.\n");
            exit(EXIT_FAILURE);
        }
        return 0;
    }

    fread(&qtdReservas_bin, sizeof(int), 1, p_reservas_bin);
    *capacidade = (qtdReservas_bin > 0) ? (qtdReservas_bin * 2) : 5;

    *listaReservas = malloc((*capacidade) * sizeof(Reservas));
    if (*listaReservas == NULL) {
        fprintf(stderr, "Critical: Memory allocation failed for Reservas.\n");
        fclose(p_reservas_bin);
        exit(EXIT_FAILURE);
    }

    fread(*listaReservas, sizeof(Reservas), qtdReservas_bin, p_reservas_bin);
    fclose(p_reservas_bin);
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

// União das funções para chamar na main
void salvar_dados(Usuarios *listaUsuarios, Sessoes *listaSessoes, Reservas *listaReservas, int qtdUsuarios, int qtdSessoes, int qtdReservas){
    salvar_usuarios(listaUsuarios, qtdUsuarios);
    salvar_sessoes(listaSessoes, qtdSessoes);
    salvar_reservas(listaReservas, qtdReservas);
}
