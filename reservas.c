//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE RESERVA }--------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "reservas.h"
#include "sessoes.h"

int buscar_indice_reserva(Reservas *reservas, int qtdReservas, int idProcurado){ //codar as fun��es previamente declaradas em reserva.h
    int i;
    for(i=0; i<qtdReservas; i++){
        if(reservas[i].id_sessao == idProcurado){
            return i; //indice da reserva
        }
    }
    return -1;
}

void imprimir_dados_reserva(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("==========================================================\n");
    printf("           Reserva:\n");
    printf("==========================================================\n");
    printf("Nome: %s.\n", usuarios[indice].nome);
    printf("CPF: %s.\n", reservas[indice].cpf_usuario);
    printf("ID: %d.\n", reservas[indice].id);
    printf("ID Sessão: %d.\n", reservas[indice].id_sessao);
    printf("Assento: %s.\n", reservas[indice].assento);
}

void modificarNome(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    Usuarios temp;

    printf("\n==============================================\n");
    printf("              Modificar Nome\n");
    printf("\n==============================================\n");
    printf("              Insira o novo Nome\n");
    printf("\n----------------------------------------------\n");
    printf("Nome: ");

    while (getchar() != '\n');
    fgets(temp.nome, sizeof(temp.nome), stdin);
    temp.nome[strcspn(temp.nome, "\n")] = '\0'; // Boa prática limpar o \n
    strcpy(usuarios[indice].nome, temp.nome);

    printf("\n----------------------------------------------\n");
    printf("              Nome Modificado com Sucesso!\n");
    printf("             Pressione ENTER para continuar.\n");
    printf("\n----------------------------------------------\n");
    getchar();
}

void modificarCPF(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){

    printf("\n==============================================\n");
    printf("                Modificar CPF\n");
    printf("\n==============================================\n");
    printf(" Digite o novo CPF neste formato XXX.XXX.XXX-XX\n");
    printf("\n-----------------------------------------------\n");
    printf("CPF: ");


}

void modificarID(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("\n----------------------------------------------\n");
    printf("              Modificar ID\n");
    printf("\n----------------------------------------------\n");
}

void modificarIDsessao(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice){
    printf("\n----------------------------------------------\n");
    printf("              Modificar ID Sessão\n");
    printf("\n----------------------------------------------\n");
}

void modificarAssento(Reservas *reservas, int qtdReservas, Usuarios *usuarios, int indice, Sessoes *sessoes, int qtdSessoes){
    int indiceSessao = -1;
    for(int i = 0; i < qtdSessoes; i++){
        if(sessoes[i].id == reservas[indice].id_sessao){
            indiceSessao = i;
            break;
        }
    }

    if(indiceSessao == -1){
        printf("Erro: Sessão da reserva não encontrada.\n");
        return;
    }

    Sessoes *sessaoAtual = &sessoes[indiceSessao];

    /* ==========================================================
     LÓGICA PARA LIBERAR O ASSENTO ANTIGO
     ============================================================
    */
    char *assentoAntigo = reservas[indice].assento;
    int linhaAntigaIdx = assentoAntigo[0] - 'A'; // pega a letra e subtrai 'A', descobrindo o índice da linha antiga
    int colunaAntigaIdx = atoi(&assentoAntigo[1]) - 1; // função atoi transforma string em int, &assentoAntigo[1] pega a string a partir do segundo caractere, -1 pois array começa em 0

    sessaoAtual->assento[linhaAntigaIdx][colunaAntigaIdx] = 0; //l ibera o assento na matriz (define como 0)

    /* ==========================================================
     LÓGICA PARA SELECIONAR NOVO ASSENTO
     ============================================================
    */
    int linhaAssento;
    int colunaAssento;

    printf("\n==============================================\n");
    printf("              Modificar Assento\n");
    printf("\n==============================================\n");
    printf("            Selecione um novo Assento\n");
    printf("\n----------------------------------------------\n");

    printf("Assentos:\n");

    char Linha[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    for(int L = 0; L < 10; L++){
        for(int C = 0; C < 10; C++){
            if(C != 9){
                if(sessaoAtual->assento[L][C] == 0) printf("%c%d ",Linha[L],C);
                else printf("X ");
            } else {
                if(sessaoAtual->assento[L][C] == 0) printf("%c%d\n",Linha[L],C);
                else printf("X\n");
            }
        }
    }
    printf("_________________________________________________________________\n");
    printf("                             TELA\n");

    int valido=0;
    do{
        printf("\nDigite a linha do assento desejado (Ex.1): ");
        scanf("%d", &linhaAssento);
        linhaAssento -= 1;

        printf("\nDigite a coluna do assento desejado (Ex.1): ");
        scanf("%d", &colunaAssento);
        colunaAssento -= 1;

        if(linhaAssento < 0 || linhaAssento > 9 || colunaAssento < 0 || colunaAssento > 9){
            printf("Posição inválida! Tente novamente.\n");
        }else{
            if(sessaoAtual->assento[linhaAssento][colunaAssento] != 0){ // Se diferente de 0, está ocupado
                printf("Sentimos muito, este assento está ocupado (X). Escolha outro.\n");
            }else{
                valido = 1;
            }
        }
    } while(valido == 0);

    sessaoAtual->assento[linhaAssento][colunaAssento] = 1; // marca o novo assento como ocupado

    //atualizar a string na struct de Reserva
    char novaLetra = 'A' + linhaAssento;
    int novoNumero = colunaAssento + 1;

    // sprintf formata e guarda dentro da string 'reservas[indice].assento'
    sprintf(reservas[indice].assento, "%c%d", novaLetra, novoNumero);

    printf("\n----------------------------------------------\n");
    printf("          Assento Modificado com Sucesso!\n");
    printf("          Pressione ENTER para continuar.\n");
    printf("----------------------------------------------\n");

    while(getchar() != '\n'); // Limpa buffer
    getchar();

}
