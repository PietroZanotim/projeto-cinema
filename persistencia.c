#include "structs.h"
#include <string.h>

// fwrite: copia da memória para o arquivo
// fread: copia do arquivo para a memória

int inicializar_sistema(Usuarios *lista){
    FILE *p_bin;
    p_bin = fopen("usuarios.bin", "rb");

    // Se não tiver um arquivo .bin, crie um
    if(p_bin == NULL) {
        p_bin = fopen("usuarios.bin", "wb");
        
        // Sistema temporário para acessar o admin
        strcpy(lista[0].nome, "Admin");
        strcpy(lista[0].cpf, "000.000.000-00");
        strcpy(lista[0].senha, "123senha");
        lista[0].saldo = 1000.00;
        lista[0].idade = 30;
        
        int qtd_inicial = 1;

        // Escreva o cabeçalho (a quantidade)
        fwrite(&qtd_inicial, sizeof(int), 1, p_bin);

        // Escreva o admin (o dado)
        fwrite(lista, sizeof(Usuarios), 1, p_bin);

        fclose(p_bin);
        
        // Admin
        return 1;
    }
    else {
        int total_lido;
        // Trazer os dados do disco rígido para a RAM
        // Parâmetros: destino, tamanho em bytes, quantidade, ponteiro do arquivo
        fread(&total_lido, sizeof(int), 1, p_bin);
        // Pega as listas de usuários salvas 
        fread(lista, sizeof(Usuarios), total_lido, p_bin);
        fclose(p_bin);

        // Retorna a quantidade de usuários
        return total_lido;
    }
}