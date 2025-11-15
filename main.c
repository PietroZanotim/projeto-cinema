#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// (S1) Registro Independente 1 
typedef struct Sessoes{
    int id;
    char horario_inicio[6];
    char horario_final[6];
    char data[9];
    int sala;
    char assento[15][15];
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
 
// Função para limpar a tela verificando qual o OS
void limparTela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls || clear");
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #else
        for(int i = 0; i < 50; i++) printf("\n");
    #endif
}


//-----------------------------------------------------------------------------
//---------------------------{ MENU PRINCIPAL }--------------------------------
//-----------------------------------------------------------------------------
int menuPrincipal() {
    int opcao = 0; // Inicializa com um valor inválido

    do {
        limparTela(); 

        printf("=========================================\n");
        printf("   SISTEMA DE GERENCIAMENTO DE CINEMA\n");
        printf("=========================================\n\n");
        printf("   [1] - Fazer Login\n");
        printf("   [2] - Cadastrar Novo Usuario\n");
        printf("   [3] - Saber Mais (Sobre o Projeto)\n");
        printf("   [4] - Sair do Programa\n");
        printf("\n-----------------------------------------\n");
        printf("Digite a opcao desejada: ");

        // Validação de tipo de input
        if (scanf("%d", &opcao) != 1) {
            // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
            // limpamos o buffer de entrada para evitar um loop infinito.
            opcao = 0; // Reseta para um valor inválido
            while (getchar() != '\n'); // Limpa o buffer
        }

        // Validação de intervalo numérico        
        if (opcao < 1 || opcao > 4) {
            printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (opcao < 1 || opcao > 4); // Repete o menu se a opção for inválida

    // Retorna a opção válida (1, 2, 3 ou 4)
    return opcao;
}

//-----------------------------------------------------------------------------
//---------------------------{ OPCAO 1 - LOGIN }-------------------------------
//-----------------------------------------------------------------------------
int opcao1(){
    
    int opcaoTemp;
    printf("Digite a ação que deseja realizar: \n");
        printf("[1] Login.\n");
        printf("[2] Cadastrar.\n");
        printf("[3] Sair.\n");
        
        do{
            
            scanf("%d", &opcaoTemp);
            if(!(opcaoTemp==1 || opcaoTemp==2 || opcaoTemp==3)){
                printf("\nOpcao inválida! Digite novamente: ");
            }
            
        }while(!(opcaoTemp==1 || opcaoTemp==2 || opcaoTemp==3));
    
    return opcaoTemp;
}

//-----------------------------------------------------------------------------
//---------------------------{ OPCAO 2 - CADASTRO }----------------------------
//-----------------------------------------------------------------------------
int escolha2(){

    int opcaoTemp;
    printf("Digite a ação que deseja realizar: \n");
    printf("[1] Reservar.\n");
    printf("[2] Visualizar suas reservas.\n");
    printf("[3] Saldo/Deposito em conta.\n");
    printf("[4] Sair.\n");
        
    do{
        scanf("%d", &opcaoTemp);
        if(!(opcaoTemp==1 || opcaoTemp==2 || opcaoTemp==3 || opcaoTemp==4)){
            printf("\nOpcao inválida! Digite novamente: ");
        }
    }while(!(opcaoTemp==1 || opcaoTemp==2 || opcaoTemp==3 || opcaoTemp==4));

    return opcaoTemp;
}

//-----------------------------------------------------------------------------
//-------------------------{ OPCAO 3 - SABER MAIS }----------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------{ OPCAO PARA SAIR }-----------------------------
//-----------------------------------------------------------------------------
int confirmarSaida() {
    char resposta;

    limparTela(); 

    do {
        printf("=========================================\n");
        printf("              SAIR DO PROGRAMA\n");
        printf("=========================================\n\n");
        printf("Voce tem certeza que deseja sair?\n");
        printf("Todos os dados serao salvos.\n\n");
        printf("[S] - Sim, desejo sair\n");
        printf("[N] - Nao, quero voltar ao menu\n");
        printf("\nDigite sua escolha: ");

        // espaço antes do %c para consumir buffer
        if (scanf(" %c", &resposta) != 1) {
            resposta = ' '; // Define como inválido se o scanf falhar
        }

        // Limpa o buffer de entrada para a próxima iteração
        while (getchar() != '\n'); 

        resposta = toupper(resposta); // Converte para maiúsculo

        if (resposta != 'S' && resposta != 'N') {
            printf("\nOpcao invalida! Digite S ou N.\n Pressione Enter para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
        }

    } while (resposta != 'S' && resposta != 'N');

    if (resposta == 'S') {
        return 1; // 1 = Sim, sair
    } else {
        return 0; // 0 = Não, voltar
    }
}



int validaCpf(struct Usuarios usuarios[], int qtdUsuarios, int *posicao){
    int flag=0;
    char cpftemp[15];
    strcpy(cpftemp,"");
    
    fgets(cpftemp,15,stdin);
    cpftemp[strcspn(cpftemp,"\n")] = '\0';
    
    for(int i = 0; i < qtdUsuarios; i++){
        if(strcmp(cpftemp,usuarios[i].cpf)==0){
            flag=1;
            *posicao=i;
        } 
    }
  
    if(flag==0){
    printf("CPF não encontrado, digite novamente: ");
    }
    
    return flag;
}

int validaSenha(struct Usuarios usuarios[], int qtdUsuarios, int posicao){
    int flag=0;
    char senhaTemp[15];
    
    fgets(senhaTemp,15,stdin);
    senhaTemp[strcspn(senhaTemp,"\n")] = '\0';
                        
    if(strcmp(senhaTemp,usuarios[posicao].senha)==0){
        flag=1;
    } 
    
                        
    if(flag==0){
        printf("Senha inválida, digite novamente: ");
    }
    
    return flag;
}





/*void listarInicial(int a, struct Filmes *filmes[]){
    
    int i=0;
    
    while( i < a){
        int flag=1;
        printf("id Nº%d: ", (i+1));
        scanf("%d", &filmes[i]->id);
        
        for(int b=0; b < i; b++){
            if(filmes[i]->id==filmes[b]->id){
                flag=0;
                break;
            }
        }
        
        if(flag==0){
            continue;
        }
        
        getchar();
        fgets(filmes[i]->nome,49,stdin);
        filmes[i]->nome[strcspn(filmes[i]->nome,"\n")] = '\0';
        
        for(int b = 0; b < 6; i++){
            
            fgets(filmes[i]->horario[b].horas,5,stdin);
            filmes[i]->horario[b].horas[strcspn(filmes[i]->horario[b].horas,"\n")] = '\0';
            
            int atribuiAssentos=1;
            for(int c = 0; c < 15; c++){
                for(int d = 0; d < 15; d++){
                    filmes[i]->horario[b].assento[c][d] = atribuiAssentos;
                    atribuiAssentos++;
                }
            }
            
        }
        
        i++;
        
    }
    
};
*/

//-----------------------------------------------------------------------------
//--------------------------------{ MAIN }-------------------------------------
//-----------------------------------------------------------------------------

int main(){
    
    int idReservas=0; // Para marcar o id das reservas;
    // Colocando um tamanho fixo, até vermos vetor dinâmico;
    int qtdFilmes=3; 
    int qtdUsuarios=5;
    int qtdReservas=4050;
    
    struct Usuarios usuarios[qtdUsuarios];
    struct Reservas reservas[qtdReservas];

    strcpy(usuarios[0].cpf,"111.111.111-00");
    strcpy(usuarios[0].senha,"123456");
    
    //listarInicial(qtdFilmes, &filmes); Desconsiderar por enquanto

    // Inicializa o menu e atribui o valor a variável opcao.
    int opcao = menuPrincipal();

    while (1) { 
        switch (opcao){
            case 1:
                /* code */
                break;
            
            case 2:
                break;

            case 3:
                break;

            case 4:
            confirmarSaida();
                if (confirmarSaida() == 0) { // Se a função retornar 0 (Não)
                    opcao = 0; // Reseta a opção para o loop continuar
                }
                    // Se a função retornar 1 (Sim), opcao continua 4
                    // e o loop 'while' vai terminar.
                    break;
        }
    }

    

    while(1){
        
        int opcao;
        //opcao = escolha1(); // Menu;
        getchar();
        

        switch(opcao){
            
                case 1: // Login do usuario;
                    int posicao;
                    int flag;
                    
                    printf("Digite seu CPF (000.000.000-00): ");
                    
                    do{
                        
                        flag = validaCpf(usuarios, qtdUsuarios, &posicao);
                        
                    } while(flag==0);
                    getchar();

                    printf("Digite sua senha: ");
                    
                    do{
                        
                       flag = validaSenha(usuarios, qtdUsuarios, posicao);
                        
                    }while(flag==0);
                    
                    printf("\n\nLogin realizado com sucesso!\n\n"); // Abaixo segue oque usuario pode fazer;
                    
                    opcao = escolha2();
                    
                    switch(opcao){
                        
                        case 1:
                        break;
                        
                        case 2:
                        break;
                        
                        case 3:
                        break;
                        
                        
                    }
                    
                    
                break;
                
                case 2: // Cadastro do usuário;
                
                
                
                break;
                
                default: // Saida do sistema para menu novamente;
                break;
                
        }
        
        if(opcao==3){
            break;
        }
        
    }
    
    
    printf("\n_________\nEncerrando...\n\n");
    
    return 0;

}