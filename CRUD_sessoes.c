#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "utils.h"


int menu_CRUD_sessoes(){
    int opcao;
    int tamanhoMenu = 6; //Quantidade de opções do menu. Para usar na função validarInput()
    do{
        limparTela();

        printf("===============================================================\n");
        printf("                       CRUD de Sessões\n");
        printf("===============================================================\n\n");
        printf("   [1] - Adicionar sessão\n");
        printf("   [2] - Excluir sessão\n");
        printf("   [3] - Modificar sessão\n");
        printf("   [4] - Visualizar sessão por id\n");
        printf("   [5] - Visualizar todas as sessões\n");
        printf("   [6] - Voltar ao menu inicial\n\n");
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");


        // Validação do tipo de input
        opcao = validarInput(tamanhoMenu);

    }while(opcao < 1 || opcao > 6);

    return opcao;
}
