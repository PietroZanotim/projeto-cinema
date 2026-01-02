//--------------------------!! SOBRE O ARQUIVO !!------------------------------
//----------{ FUNCOES QUE CONSULTAM/ALTERAM A STRUCT DE SUSUÁRIO }-------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "utils.h"

//-----------------------------------------------------------------------------
//-----------------------------{ FUNCÕES DE CPF }------------------------------
//-----------------------------------------------------------------------------

int buscaCpfCadastro(Usuarios *lista, int qtdUsuarios, char *cpfTemp){
    int i;
    for(i = 0; i < qtdUsuarios; i++){
        if(strcmp(lista[i].cpf,cpfTemp)==0) return i; // CPF já está cadastrado
    }
    return -1; // CPF não está cadastrado 
}


// modoCadastro: 1 = verificando para cadastrar (não pode existir), 0 = verificando para login (tem que existir)
// destCpf: ponteiro para onde vamos copiar o CPF validado (pode ser NULL se for login)
int validarCPF(Usuarios *lista, int qtd, char *destCpf, int modoCadastro){
    int i;
    char cpfTemp[15];
    scanf(" %14[^\n]", cpfTemp);
    // Caso formos voltar para o fgets: fgets(cpfTemp, sizeof(cpfTemp),stdin);
    // Remover quebra de linha se existir
    cpfTemp[strcspn(cpfTemp, "\n")] = '\0';
    // 1. Verificar tamanho
    if (strlen(cpfTemp) != 14) return -2;
    // 2. Verificar formato fixo XXX.XXX.XXX-XX
    if (cpfTemp[3] != '.' || cpfTemp[7] != '.' || cpfTemp[11] != '-') return -2;
    // 3. Verificar se os dígitos são numéricos
    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue;
        if (!isdigit(cpfTemp[i])) return -2;
    }
    // 4. Verifica se o CPF já está cadastrado
    int indiceEncontrado = buscaCpfCadastro(lista, qtd, cpfTemp);

    if (modoCadastro == 1) { // ***MODO CADASTRO****
        if (indiceEncontrado == -1) {
            if(destCpf != NULL) strcpy(destCpf, cpfTemp); //Passa o cpf para o destCpf caso tudo estiver correto. 
            return 1; // Sucesso
        }
        else return -1; // Erro: já existe
    }
    
    if (modoCadastro == 0) { // ***MODO LOGIN***
        
        if(indiceEncontrado == -1){
            if(destCpf != NULL){
            strcpy(destCpf, cpfTemp); //If para modificar o CPF no CRUD de usuarios(modificar CPF).
            }
        }
         
        // Queremos logar, então TEM que existir (retorna o indice)
        if (indiceEncontrado == -1) return -1; 
        else return indiceEncontrado;
    }
}

//-----------------------------------------------------------------------------
//---------------------------{ OPCAO 1 - LOGIN }-------------------------------
//-----------------------------------------------------------------------------

int login(Usuarios *lista, int qtdUsuarios){
    int indiceUsuario;
    limparTela(); 
    printf("================================================\n");
    printf("                      Login\n");
    printf("================================================\n\n");
    printf(" Digite o seu CPF neste formato XXX.XXX.XXX-XX\n");
    printf("\n-----------------------------------------------\n");
    printf("CPF: ");

    while (1) {
        while (getchar() != '\n');
        // Passamos NULL no destCpf pois no login não vamos salvar o CPF em lugar nenhum por enquanto
        indiceUsuario = validarCPF(lista, qtdUsuarios, NULL, 0); 

        if (indiceUsuario == -2) { // -2: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX");
            printf("CPF: ");
        } else if (indiceUsuario == -1) { // -1: CPF já está cadastrado
            puts("\nEsse CPF não foi encontrado.");
            puts("Digite um outro CPF ou retorne ao menu.");
            printf("CPF: ");
        } else {
            break; // CPF achado, indiceUsuario tem a posição dele no vetor
        }     
    }

    limparTela(); 
    printf("=========================================\n");
    printf("                  Login\n");
    printf("=========================================\n\n");
    printf("           Digite a sua senha\n");
    printf("\n-----------------------------------------\n");
    printf("Senha: ");
    
    while (getchar() != '\n');

    char senhaTemp[15];
    while(1){
        fgets(senhaTemp, sizeof(senhaTemp), stdin);
        senhaTemp[strcspn(senhaTemp, "\n")] = '\0'; // Remove o \n

        if(strcmp(senhaTemp, lista[indiceUsuario].senha) == 0) break;   
        else {
            puts("\nSenha invalida. Digite novamente:\nSenha: ");
        }
    }

    limparTela();
    printf("=========================================================\n");
    printf("  Login realizado com sucesso! [Enter] para continuar...\n");
    printf("=========================================================\n");
    getchar();

    return indiceUsuario; // Alteração para retornar o indice do usuario, de modo a acessá-lo no painel do login.
}

//-----------------------------------------------------------------------------
//---------------------------{ OPCAO 2 - CADASTRO }----------------------------
//-----------------------------------------------------------------------------
void cadastro(Usuarios *lista, int *qtdUsuarios, int max){
    // Verifica capacidade antes de começar
    if (*qtdUsuarios >= max) {
        printf("Erro: Banco de dados cheio.\n");
        getchar();
        return;
    }

    Usuarios novoUsuario; // Variável local temporária (substitui a global usuarios_temp)

    limparTela(); 
    printf("================================================\n");
    printf("                    Cadastro\n");
    printf("================================================\n\n");
    printf("            Digite o seu nome completo         \n");
    printf("\n----------------------------------------------\n");
    printf("Nome: ");
    
    while (getchar() != '\n'); 
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0'; // Boa prática limpar o \n

    limparTela(); 
    printf("================================================\n");
    printf("                   Cadastro\n");
    printf("================================================\n\n");
    printf("        Digite a sua idade (ex.: 20)\n");
    printf("\n-----------------------------------------------\n");
    printf("Idade: ");
    scanf(" %d", &novoUsuario.idade);
    while(novoUsuario.idade < 1 || novoUsuario.idade > 200) {
        while (getchar() != '\n');
        puts("\n\nVocê digitou incorretamente. Por favor, digite um número");
        printf("Idade: ");
        scanf(" %d", &novoUsuario.idade);
    }
    
    

    limparTela(); 
    printf("================================================\n");
    printf("                  Cadastro\n");
    printf("================================================\n\n");
    printf(" Digite o seu CPF neste formato XXX.XXX.XXX-XX\n");
    printf("\n-----------------------------------------------\n");
    printf("CPF: ");

    while (1) {
        // Limpa o buffer sempre antes de ler
        while (getchar() != '\n');

        // Passamos o endereço de novoUsuario.cpf para salvar se for validado
        int resultado_validacao = validarCPF(lista, *qtdUsuarios, novoUsuario.cpf, 1);

        if (resultado_validacao == 1) { // 1: Tudo correto, CPF validado e não cadastrado
            break;
        } else if (resultado_validacao == -2) { // -2: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste fomato XXX.XXX.XXX-XX");
            printf("CPF: ");
        } else if (resultado_validacao == -1) { // -1: CPF já está cadastrado
            puts("\nEsse CPF já está cadastrado.");
            puts("Digite um outro CPF ou retorne ao menu.");
            printf("CPF: ");
        }
    }

    limparTela(); 
    printf("=========================================\n");
    printf("                Cadastro\n");
    printf("=========================================\n\n");
    printf("           Digite a sua senha\n");
    printf("\n-----------------------------------------\n");
    printf("Senha: ");
    
    while (getchar() != '\n'); 
    fgets(novoUsuario.senha, sizeof(novoUsuario.senha), stdin);
    novoUsuario.senha[strcspn(novoUsuario.senha, "\n")] = '\0';

    // IndiceUsuario do admin é 0, portanto, para os próximos usuários: IndiceUsuario = qtdUsuario
    // Antes de incrementar o qtdUsuario
    lista[*qtdUsuarios] = novoUsuario;
    // Incrementamos a quantidade de usuários
    (*qtdUsuarios)++; 

    limparTela();
    
    printf("============================================================\n");
    printf("  Usuario cadastrado com sucesso! [Enter] para continuar...\n");
    printf("============================================================\n");
    getchar();
}


//-----------------------------------------------------------------------------
//---------------------------{ MENU DE LOGIN }---------------------------------
//-----------------------------------------------------------------------------
int menuLogin(Usuarios *usuario, int indiceUsuario) {

    int opcao = 0; // Inicializa com um valor inválido

        do {

            limparTela(); 

            printf("===============================================================\n");
            printf("       TELA PRINCIPAL - Olá: %s\n", usuario[indiceUsuario].nome);
            printf("===============================================================\n\n");
            printf("   [1] - Visualizar filmes disponíveis.\n");
            printf("   [2] - Visualizar minhas sessões.\n");
            printf("   [3] - Visualizar meu saldo.\n");
            printf("   [4] - Alterar senha.\n"); // Alteração dos registros.
            printf("   [5] - Excluir esta conta.\n"); // Remoção dos registros.
            printf("   [6] - Voltar ao menu inicial\n\n");
            printf("---------------------------------------------------------------\n");
            printf("Digite a opcao desejada: ");

            // Validação de tipo de input
            if (scanf("%d", &opcao) != 1) {
                // Se o scanf falhar (ex: usuário digitou 'a' em vez de '1'),
                // limpamos o buffer de entrada para evitar um loop infinito.
                opcao = 0; // Reseta para um valor inválido
                while (getchar() != '\n'); // Limpa o buffer
            }

            // Validação de intervalo numérico        
            if (opcao < 1 || opcao > 6) {
                printf("\nOpcao invalida! Pressione Enter para tentar novamente.");
                while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
                getchar(); // Aguarda o usuário pressionar Enter
            }

        } while (opcao < 1 || opcao > 6); // Repete o menu se a opção for inválida
        
        return opcao;

}


//-----------------------------------------------------------------------------
//---------------------{ VISUALIZAR SALDO DO USUARIO }-------------------------
//-----------------------------------------------------------------------------

void verSaldo(Usuarios *usuario, int indiceUsuario){

    limparTela();

    printf("===============================================================\n");
    printf("              Saldo de: %s\n", usuario[indiceUsuario].nome);
    printf("===============================================================\n\n");
    printf("\nSeu saldo atual: R$%.2f\n", usuario[indiceUsuario].saldo);

    char resposta;
    
    do{
        printf("\nDeseja realizar um depósito? (S/N): ");
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

    if(resposta=='S'){
        float valorDeposito;
        printf("\n*** MAX - R$100.00 | POR OPERAÇÃO ***");
        printf("\nDigite o valor que deseja depositar: ");

        while(scanf("%f", &valorDeposito)!=1 || valorDeposito>100.00){
            printf("\nValor digitado inválido ou acima do permitido!");
            printf("\n[Enter] para tentar novamente.");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário pressionar Enter
            limparTela();
            printf("\nDigite o valor que deseja depositar: ");
        }

        usuario[indiceUsuario].saldo += valorDeposito*1.0;

        limparTela();
        printf("===============================================================\n");
        printf("                 Depósito realizado com sucesso!");
        printf("\n===============================================================\n");
        printf("\n[Enter] para retornar ao menu login...");
        while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
        getchar(); // Aguarda o usuário enviar o enter

    } else {
        limparTela();
        printf("\n[Enter] para retornar ao menu login...");
        getchar(); // Aguarda o usuário enviar o enter
    }
}
