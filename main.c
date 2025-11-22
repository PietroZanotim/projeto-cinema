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
//-----------------------------------------------------------------------------
int const qtdUsuarios=5;//Inicializado o vetor de usuarios globalmente, pois é usado não apenas na main;
Usuarios usuarios[qtdUsuarios];
//-----------------------------------------------------------------------------

// (S3) Registro Relacional
typedef struct Reservas{
    int id;                
    char cpf_usuario[15];   // Aponta para um Usuario (S2). O cpf é único.
    int id_sessao;          // Aponta para S1 
    char assento[4];        // Informação adicional (ex: "F10")
} Reservas;
 
//-----------------------------------------------------------------------------
//---------------------------{ FUNCÕES AUXILIARES }----------------------------
//-----------------------------------------------------------------------------

int validarCPF(){
    int i;
    char cpf[15];
    fgets(cpf, sizeof(cpf),stdin);
    // Remover quebra de linha se existir
    cpf[strcspn(cpf, "\n")] = '\0';
    // 1. Verificar tamanho
    if (strlen(cpf) != 14) return 0;
    // 2. Verificar formato fixo XXX.XXX.XXX-XX
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') return 0;
    // 3. Verificar se os dígitos são numéricos
    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue; // posições de pontuação

        if (!isdigit(cpf[i])) return 0;
    }
    return 1;
}

int buscaCpfCadastro(char *cpfTemp, struct Usuarios *usuarios, int qtdUsuarios){
    
    int i,i2;
    int flag=0;
    int contIguais;
    
    //Para validar a igualdade estamos usando um for, pois o strcmp não funciona.
    for(i = 0; i < qtdUsuarios; i++){
        for(i2 = 0; cpfTemp[i2] != '\0'; i2++){
            if(usuarios[i].cpf[i2]==cpfTemp[i2]){
                contIguais++;
            }
        }
        if(contIguais==14){ //Se digito a digito for igual, então o CPF já está cadastrado.
            flag=1;
            return flag;
        }
    }
    
    return flag;
}

int buscaCpfLogin(struct Usuarios *usuarios, int qtdUsuarios, int *posicao){
    int i;
    int flag=0;
    char cpftemp[15];
    strcpy(cpftemp,"");
    
    fgets(cpftemp,15,stdin);
    cpftemp[strcspn(cpftemp,"\n")] = '\0';
    
    for(i = 0; i < qtdUsuarios; i++){
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


//-----------------------------------------------------------------------------
//---------------------------{ OPCAO 2 - CADASTRO }----------------------------
//-----------------------------------------------------------------------------
Usuarios cadastro(){

    // Inicializar structs dentro de cadastro para depoin enviar para as structs inicializadas na main
    Usuarios usuarios_func;

    limparTela(); 

    printf("=========================================\n");
    printf("                Cadastro\n");
    printf("=========================================\n\n");
    printf("        Digite o seu nome completo         \n");
    printf("\n-----------------------------------------\n");
    printf("Nome: ");

    // Limpa o buffer de entrada para a próxima iteração
    while (getchar() != '\n'); 
    fgets(usuarios_func.nome, sizeof(usuarios_func.nome),stdin);

    limparTela(); 

    printf("=========================================\n");
    printf("                Cadastro\n");
    printf("=========================================\n\n");
    printf("        Digite a sua idade (ex.: 20)\n");
    printf("\n-----------------------------------------\n");
    printf("Idade: ");

    // nao utilizo o loop para limpar o buffer aqui, porque o fgets anterior consumirá o \n e o loop ficará infinito.
    scanf(" %d",&usuarios_func.idade);

    limparTela(); 

    printf("=========================================\n");
    printf("                Cadastro\n");
    printf("=========================================\n\n");
    printf("Digite o seu CPF neste fomato XXX.XXX.XXX-XX\n");
    printf("\n-----------------------------------------\n");
    printf("CPF: ");
    
    while (getchar() != '\n');
    // Limpa o buffer sempre antes de ler

    while (1) {
        char cpfTemp[14];
        fgets(cpfTemp,14,stdin);
        cpfTemp[strcspn(cpfTemp,"\n")] = '\0';

        //Validando se o cpf está dentro do formato e se já não foi incluido nos cadastros.
        int flag1 = validarCPF(cpfTemp);

        int flag2 = buscaCpfCadastro(cpfTemp,usuarios,qtdUsuarios);

        if(flag1==0 && flag2==0){
        puts("O CPF digitado está fora do formato ou já está cadastrado.");
        puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX.");
        printf("CPF: ");
        } else if(flag1==0){
        puts("Você digitou o CPF incorretamente.");
        puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX.");
        printf("CPF: ");
        } else if(flag2==0){
        puts("O CPF digitado já está cadastrado.");
        puts("Digite o seu CPF novamente.");
        printf("CPF: ");
        } else {
            break;
        }
    }

    limparTela(); 

    printf("=========================================\n");
    printf("                Cadastro\n");
    printf("=========================================\n\n");
    printf("           Digite a sua senha\n");
    printf("\n-----------------------------------------\n");
    printf("Senha: ");

    // Limpa o buffer de entrada para a próxima iteração
    while (getchar() != '\n'); 
    fgets(usuarios_func.senha, sizeof(usuarios_func.senha),stdin);

    return usuarios_func;
   
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
        limparTela();
        return 1; // 1 = Sim, sair
    } else {
        return 0; // 0 = Não, voltar
    }
}

//-----------------------------------------------------------------------------
//--------------------------------{ MAIN }-------------------------------------
//-----------------------------------------------------------------------------

int main(){
    
    int idReservas=0; // Para marcar o id das reservas;
    // Colocando um tamanho fixo, até vermos vetor dinâmico;
    int qtdFilmes=3; 
    int contUsuarios=0;
    int qtdReservas=4050;
        

    while (1) {
        // Inicializa o menu e atribui o valor a variável opcao.
        int opcao = menuPrincipal();

        switch (opcao){
            case 1:
                /* code */
                break;
            
            case 2:
                usuarios[contUsuarios] = cadastro();
                contUsuarios++;
                break;

            case 3:
                break;

            case 4:
                if (confirmarSaida() == 0) { // Executa a funcao e verifica o resultado
                }
                else {return 0;}
        }
    }

}
