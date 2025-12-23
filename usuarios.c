#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "utils.h"

//-----------------------------------------------------------------------------
//---------------------------{ FUNCÕES AUXILIARES }----------------------------
//-----------------------------------------------------------------------------

int buscaCpfCadastro(Usuarios *lista, int qtdUsuarios, char *cpfTemp){
    int i;
    for(i = 1; i <= qtdUsuarios; i++){
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
    if (strlen(cpfTemp) != 14) return 0;
    // 2. Verificar formato fixo XXX.XXX.XXX-XX
    if (cpfTemp[3] != '.' || cpfTemp[7] != '.' || cpfTemp[11] != '-') return 0;
    // 3. Verificar se os dígitos são numéricos
    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue;
        if (!isdigit(cpfTemp[i])) return 0;
    }
    // 4. Verifica se o CPF já está cadastrado
    int indiceEncontrado = buscaCpfCadastro(lista, qtd, cpfTemp);
    if (modoCadastro == 1) {
        if (indiceEncontrado == -1) {
            if(destCpf != NULL) strcpy(destCpf, cpfTemp); //Passa o cpf para o destCpf caso tudo estiver correto. 
            return 1; // Sucesso
        }
        else return -1; // Erro: já existe
    }
    
    if (modoCadastro == 0) {
        // Queremos logar, então TEM que existir (retorna o indice)
        if (indiceEncontrado == -1) return -1; 
        else return indiceEncontrado;
    }
    return 0;
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

        if (indiceUsuario == 0) { // 0: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste fomato XXX.XXX.XXX-XX");
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
        } else if (resultado_validacao == 0) { // 0: CPF em formato incorreto
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

    // Persistência no vetor principal
    // Incrementamos primeiro, porque o usuário 0 será o admin.
    (*qtdUsuarios)++; 
    lista[*qtdUsuarios] = novoUsuario;

    limparTela();
    
    printf("============================================================\n");
    printf("  Usuario cadastrado com sucesso! [Enter] para continuar...\n");
    printf("============================================================\n");
    getchar();
}