// structs.h
#ifndef STRUCTS_H  // Guardas de inclusão (evita erro de redefinição)
#define STRUCTS_H


// (S1) Registro Independente 1 
typedef struct Sessoes{
    int id;
    char horario_inicio[6];
    char horario_final[6];
    char data[9];
    int sala;
    char assento[10][10];
    char nome_filme[50];
    int limIdade;
    float valorIngresso;
}Sessoes;

// (S2) Registro Independente 2
typedef struct Usuarios{
    char nome[70];
    int idade;
    char cpf[15];
    char senha[15];
    float saldo;
}Usuarios;

// (S3) Registro Relacional
typedef struct Reservas{
    int id;                
    char cpf_usuario[15];   // Aponta para um Usuario (S2). O cpf é único.
    int id_sessao;          // Aponta para S1 
    char assento[4];        // Informação adicional (ex: "F10")
} Reservas;

#endif