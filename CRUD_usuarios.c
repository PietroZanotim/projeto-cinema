#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "usuarios.h"
#include "utils.h"

// --- CRUD USUÁRIO (Estrutura 2) ---
void adicionar_usuario(Usuarios *lista, int *qtdUsuarios, int max){
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
    printf("            Digite o nome completo         \n");
    printf("\n----------------------------------------------\n");
    printf("Nome: ");
    
    while (getchar() != '\n'); 
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0'; // Boa prática limpar o \n

    limparTela(); 
    printf("================================================\n");
    printf("                   Cadastro\n");
    printf("================================================\n\n");
    printf("        Digite a idade (ex.: 20)\n");
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
    printf(" Digite o CPF neste formato XXX.XXX.XXX-XX\n");
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
            puts("Digite seu CPF neste fomato XXX.XXX.XXX-XX");
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
    lista[*qtdUsuarios] = novoUsuario;
    (*qtdUsuarios)++; 

    limparTela(); 
    printf("============================================================\n");
    printf("  Usuario cadastrado com sucesso! [Enter] para continuar...\n");
    printf("============================================================\n");
    getchar();
}

void excluir_usuario(Usuarios *lista, int *qtdUsuarios){

    limparTela();
    printf("================================================\n");
    printf("             Exclusão de usuário por CPF\n");
    printf("================================================\n\n");
    printf("            Digite o CPF do usuário        \n");
    printf("\n----------------------------------------------\n");
    printf("CPF: ");

    int resultado_validacao; //Usado para pegarmos o indice do usuário.
    int contErros=0; //Adicionei essa váriavel para caso o usuário erre 3 vezes o CPF na busca, saia deste menu;

    while (1) {
        if(contErros==3){
            break;
        }
        // Limpa o buffer sempre antes de ler
        while (getchar() != '\n');

        // Passamos o endereço de novoUsuario.cpf para salvar se for validado
        int resultado_validacao = validarCPF(lista, *qtdUsuarios, NULL, 0); //Usamos o validar cpf como no login, para validar se existe este CPF;

        if (resultado_validacao == 0) {
             // 0: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX");
            printf("CPF: ");
            contErros++;
        } else if(resultado_validacao == -1) { 
            puts("\nEsse CPF não foi encontrado.");
            printf("CPF: ");
            contErros++;
        } else {
             // Aqui ele retorna apenas o indice do usuario... Tudo ok, basta imprimir os dados.
            break;
        }
    }

    if(contErros==3){
        limparTela();
        while (getchar() != '\n');
        printf("==================================================================\n");
        printf("  Número máximo de tentativas atingidas! [Enter] para continuar...\n");
        printf("==================================================================\n");
        getchar();
    } else {

        limparTela();
        printf("==========================================================\n");
        printf("           Usuário: %s\n", lista[resultado_validacao].nome);
        printf("==========================================================\n");
        printf("Idade: %d\n.", lista[resultado_validacao].idade);
        printf("CPF: %s.\n", lista[resultado_validacao].cpf);
        printf("Senha: %s.\n", lista[resultado_validacao].senha);
        printf("Saldo: %.2f.\n", lista[resultado_validacao].saldo);
        
        char resposta;

        do{
            printf("\nDeseja confirmar a exclusão? (S/N): ");
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
            
            //"Exclusão" dos dados do usuário...
            strcpy(lista[resultado_validacao].nome,"");
            lista[resultado_validacao].idade = 0;
            strcpy(lista[resultado_validacao].cpf,"");
            lista[resultado_validacao].saldo = 0.00;
            strcpy(lista[resultado_validacao].senha,"");

            }

        printf("\n[Enter] para continuar...\n");
        getchar();

    }

}

void modificar_usuario(Usuarios *lista, int *qtdUsuarios){

    limparTela();
    printf("================================================\n");
    printf("              Modificação de usuário\n");
    printf("================================================\n\n");
    printf("            Digite o CPF do usuário        \n");
    printf("\n----------------------------------------------\n");
    printf("CPF: ");

    int resultado_validacao; //Usado para pegarmos o indice do usuário.
    int contErros=0; //Adicionei essa váriavel para caso o usuário erre 3 vezes o CPF na busca, saia deste menu;

    while (1) {
        if(contErros==3){
            break;
        }
        // Limpa o buffer sempre antes de ler
        while (getchar() != '\n');

        // Passamos o endereço de novoUsuario.cpf para salvar se for validado
        int resultado_validacao = validarCPF(lista, *qtdUsuarios, NULL, 0); //Usamos o validar cpf como no login, para validar se existe este CPF;

        if (resultado_validacao == 0) {
             // 0: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX");
            printf("CPF: ");
            contErros++;
        } else if(resultado_validacao == -1) { 
            puts("\nEsse CPF não foi encontrado.");
            printf("CPF: ");
            contErros++;
        } else {
             // Aqui ele retorna apenas o indice do usuario... Tudo ok, basta imprimir os dados.
            break;
        }
    }

    if(contErros==3){
        limparTela();
        while (getchar() != '\n');
        printf("==================================================================\n");
        printf("  Número máximo de tentativas atingidas! [Enter] para continuar...\n");
        printf("==================================================================\n");
        getchar();
    } else {

        limparTela();
        printf("==========================================================\n");
        printf("           Usuário: %s\n", lista[resultado_validacao].nome);
        printf("==========================================================\n");
        printf("Idade: %d\n.", lista[resultado_validacao].idade);
        printf("CPF: %s.\n", lista[resultado_validacao].cpf);
        printf("Senha: %s.\n", lista[resultado_validacao].senha);
        
        printf("---------------------------------------------------------------\n");
        printf("   [1] - Alterar nome.\n");
        printf("   [2] - Alterar idade.\n");
        printf("   [3] - Alterar CPF.\n");
        printf("   [4] - Alterar senha.\n"); // Alteração dos registros.
        printf("---------------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");

        int opcao=0;

        do{
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


        switch(opcao){

            case 1:

            limparTela();
            printf("==========================================================\n");
            printf("           Usuário: %s\n", lista[resultado_validacao].nome);
            printf("==========================================================\n");
            printf("Nome atualizado: ");
            getchar();

            char nome[70];
            fgets(nome,70,stdin);
            nome[strcspn(nome,"\n")] = '\0';

            strcpy(lista[resultado_validacao].nome,nome);

            limparTela();
            printf("===============================================================\n");
            printf("                 Nome atualizado com sucesso!");
            printf("\n===============================================================\n");
            printf("\n[Enter] para retornar ao menu login...");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário enviar o enter

            break;

            case 2:

            limparTela();
            printf("==========================================================\n");
            printf("           Usuário: %s\n", lista[resultado_validacao].nome);
            printf("==========================================================\n");
            printf("Idade atualizada: ");

            int idade;

            while(scanf(" %d", &idade) != 1 || idade >= 100){
                printf("\nIdade inválida, digite novamente: ");
                getchar();
            }

            lista[resultado_validacao].idade = idade;

            limparTela();
            printf("===============================================================\n");
            printf("                 Idade atualizada com sucesso!");
            printf("\n===============================================================\n");
            printf("\n[Enter] para retornar ao menu login...");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário enviar o enter

            break;

            case 3:

            limparTela();
            printf("==========================================================\n");
            printf("           Usuário: %s\n", lista[resultado_validacao].nome);
            printf("==========================================================\n");
            printf("CPF atualizado: ");

            int resultado_validacaoLocal; //Usado para pegarmos o indice do usuário.
            int contErros=0; //Adicionei essa váriavel para caso o usuário erre 3 vezes o CPF na busca, saia deste menu;
            char cpfTemp[15];

            while (1) {

                if(contErros==3){
                break;
                }
                // Limpa o buffer sempre antes de ler
                while (getchar() != '\n');
                
                int resultado_validacaoLocal = validarCPF(lista, *qtdUsuarios, cpfTemp, 0); //Usamos o validar cpf como no login, para validar se existe este CPF;

                if (resultado_validacaoLocal == 0) {
                    // 0: CPF em formato incorreto
                    puts("\nVocê digitou o CPF incorretamente.");
                    puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX");
                    printf("CPF: ");
                    contErros++;
                } else if(resultado_validacaoLocal == -1) { 
                    strcpy(lista[resultado_validacao].cpf, cpfTemp); // O cpf digitado não existe... Válido!!!
                    break;
                    contErros++;
                } else {
                    puts("\nEsse CPF esta sendo utilizado.");
                    printf("CPF: ");
                    contErros++;
                }
            }

            if(contErros==3){
                limparTela();
                while (getchar() != '\n');
                printf("==================================================================\n");
                printf("  Número máximo de tentativas atingidas! [Enter] para continuar...\n");
                printf("==================================================================\n");
                getchar();
            } else {
                limparTela();
                printf("===============================================================\n");
                printf("                 CPF atualizado com sucesso!");
                printf("\n===============================================================\n");
                printf("\n[Enter] para retornar ao menu login...");
                while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
                getchar(); // Aguarda o usuário enviar o enter
            }

            break;

            case 4:
            
            while (getchar() != '\n');
            limparTela();
            printf("==========================================================\n");
            printf("             Usuário: %s\n", lista[resultado_validacao].nome);
            printf("==========================================================\n");
            printf("Senha atualizada: ");

            char senha[15];
            fgets(senha,15,stdin);
            senha[strcspn(senha,"\n")] = '\0';

            strcpy(lista[resultado_validacao].senha,senha);

            limparTela();
            printf("===============================================================\n");
            printf("                 Senha atualizada com sucesso!");
            printf("\n===============================================================\n");
            printf("\n[Enter] para retornar ao menu login...");
            while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)
            getchar(); // Aguarda o usuário enviar o enter

            break;

        }
    }
}

void visualizar_usuario_cpf(Usuarios *lista, int *qtdUsuarios){ 

    limparTela();
    printf("================================================\n");
    printf("             Consulta de usuário por CPF\n");
    printf("================================================\n\n");
    printf("            Digite o CPF do usuário        \n");
    printf("\n----------------------------------------------\n");
    printf("CPF: ");

    int resultado_validacao; //Usado para pegarmos o indice do usuário.
    int contErros=0; //Adicionei essa váriavel para caso o usuário erre 3 vezes o CPF na busca, saia deste menu;

    while (1) {
        if(contErros==3){
            break;
        }
        // Limpa o buffer sempre antes de ler
        while (getchar() != '\n');

        // Passamos o endereço de novoUsuario.cpf para salvar se for validado
        int resultado_validacao = validarCPF(lista, *qtdUsuarios, NULL, 0); //Usamos o validar cpf como no login, para validar se existe este CPF;

        if (resultado_validacao == -2) {
             // 0: CPF em formato incorreto
            puts("\nVocê digitou o CPF incorretamente.");
            puts("Digite o seu CPF neste formato XXX.XXX.XXX-XX");
            printf("CPF: ");
            contErros++;
        } else if(resultado_validacao == -1) { 
            puts("\nEsse CPF não foi encontrado.");
            printf("CPF: ");
            contErros++;
        } else {
             // Aqui ele retorna apenas o indice do usuario... Tudo ok, basta imprimir os dados.
            break;
        }
    }

    if(contErros==3){
        limparTela();
        while (getchar() != '\n');
        printf("==================================================================\n");
        printf("  Número máximo de tentativas atingidas! [Enter] para continuar...\n");
        printf("==================================================================\n");
        getchar();
    } else {

        limparTela();
        printf("%d\n", resultado_validacao);
        printf("==========================================================\n");
        printf("           Usuário: %s\n", lista[resultado_validacao].nome);
        printf("==========================================================\n");
        printf("Idade: %d\n.", lista[resultado_validacao].idade);
        printf("CPF: %s.\n", lista[resultado_validacao].cpf);
        printf("Senha: %s.\n", lista[resultado_validacao].senha);
        printf("Saldo: %.2f.\n", lista[resultado_validacao].saldo);
        
        while (getchar() != '\n');
        printf("\n[Enter] para continuar...\n");
        getchar();

    }
}

void visualizar_todos_usuarios(Usuarios *lista, int qtdUsuario){

    limparTela();
    printf("==========================================================\n");
    printf("            Consulta geral dos usuários\n");
    printf("----------------------------------------------------------\n");
    
    for(int i=0; i<qtdUsuario; i++){ //Considerando o admin!!;

        printf("==========================================================\n");
        printf("               Usuário: %s\n", lista[i].nome);
        printf("==========================================================\n");
        printf("Idade: %d\n", lista[i].idade);
        printf("CPF: %s\n", lista[i].cpf);
        printf("Senha: %s\n", lista[i].senha);
        printf("Saldo: R$ %.2f\n", lista[i].saldo);

    }

    while (getchar() != '\n'); // Limpa o buffer (caso tenha sobrado algo)    
    printf("\n[Enter] para continuar...\n");
    getchar();

}

int menu_CRUD_usuarios(){
    int opcao;
    do{
        limparTela(); 

        printf("===============================================================\n");
        printf("                       CRUD de Usuários\n");
        printf("===============================================================\n\n");
        printf("   [1] - Adicionar usuário\n");
        printf("   [2] - Excluir usuário\n");
        printf("   [3] - Modificar usuário\n");
        printf("   [4] - Visualizar usuário por CPF\n"); 
        printf("   [5] - Visualizar todos os usuários\n"); 
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
    } while(opcao < 1 || opcao > 6);

    return opcao;
}