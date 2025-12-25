#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "structs.h" // Precisa conhecer a struct Sessoes

void listarSessoes(Sessoes *sessao, int quantidadeSessoes, Usuarios *usuario, int indiceUsuario){

    limparTela();

    for(int i=0; i<quantidadeSessoes; i++){

        printf("Filme: %d - Id: %d | Idade Minima: %d\n", sessao[i].nome_filme, sessao[i].id, sessao[i].limIdade);
        printf("Data: %s | Horario: %s - %s\n", sessao[i].data, sessao[i].horario_inicio, sessao[i].horario_final);
        printf("Sala: %d\n", sessao[i].sala);
        printf("Valor: %d\n", sessao[i].sala);
        printf("Assentos: %d\n", sessao[i].sala);
        for(int i=0; i<15; i++){
            for(int a=0; a<15; a++){
            if(a==14){
                printf("[%d]\n",sessao[i].assento[i][a]); // Para pular para outra "linha" de assentos;
            } else {
                printf("[%d] ",sessao[i].assento[i][a]);
            }
            }
        }

        
    }

}