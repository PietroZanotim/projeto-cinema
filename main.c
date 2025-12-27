#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utils.h"
#include "usuarios.h"
#include "sessoes.h"
#include "admin.h"
#include "CRUD_sessoes.h"
#include "CRUD_usuarios.h"
#include "CRUD_reservas.h"

#define MAX_USUARIOS 5
#define MAX_SESSOES 5
#define MAX_RESERVAS 10

int main(){
    // Criação das variáveis "Globais" dentro da main
    Usuarios listaUsuarios[MAX_USUARIOS];
    Sessoes listaSessoes[MAX_SESSOES];
    Reservas listaReservas[MAX_RESERVAS];

    // Sistema temporário para acessar o admin
    strcpy(listaUsuarios[0].nome, "Admin");
    strcpy(listaUsuarios[0].cpf, "000.000.000-00");
    strcpy(listaUsuarios[0].senha, "123senha");

    int qtdUsuarios = 1; // 1 por causa do Admin
    int qtdSessoes = 0;
    int qtdReservas = 0;
    
    while (1) {
        int opcao = menuPrincipal();

        switch (opcao){
            case 1: // Login do usuario;
                    
                int indiceUsuario = login(listaUsuarios, qtdUsuarios); // Pegamos a posição do usuario;
                
                if (indiceUsuario == 0) {
                    // Menu do admin
                    while(1){
                        int opcao = menuAdmin(); 
                        switch(opcao){
                            case 1:
                                // CRUD de Sessões
                                while(1){
                                    int opcao_1 = menu_CRUD_reservas();
                                    switch(opcao_1){
                                        case 1:
                                            //adicionar_sessao();
                                            break;
                                        case 2:
                                            //excluir_sessao();
                                            break;
                                        case 3:
                                            //modificar_sessao();
                                            break;
                                        case 4:
                                            //visualizar_sessao_id();
                                            break;
                                        case 5:
                                            //visualizar_todas_sessoes();
                                            break;
                                    }
                                    if (opcao_1 == 6){
                                        if(confirmarRetorno() == 1) break;
                                        else continue;
                                    }
                                }
                                break;
                            case 2:
                                // CRUD de Usuários
                                while(1){
                                    int opcao_2 = menu_CRUD_usuarios();
                                    switch(opcao_2){
                                        case 1:
                                            adicionar_usuario();
                                            break;
                                        case 2:
                                            excluir_usuario();
                                            break;
                                        case 3:
                                            modificar_usuario();
                                            break;
                                        case 4:
                                            visualizar_usuario_cpf();
                                            break;
                                        case 5:
                                            visualizar_todos_usuarios();
                                            break;
                                    }
                                    if (opcao_2 == 6){
                                        if(confirmarRetorno() == 1) break;
                                        else continue;
                                    }
                                }
                                break;
                            case 3:
                                // CRUD de Reservas
                                while(1){
                                    int opcao_3 = menu_CRUD_reservas();
                                    switch(opcao_3){
                                        case 1:
                                            //adicionar_reserva();
                                            break;
                                        case 2:
                                            //excluir_reserva();
                                            break;
                                        case 3:
                                            //modificar_reserva();
                                            break;
                                        case 4:
                                            //visualizar_reserva_id();
                                            break;
                                        case 5:
                                            //visualizar_todas_reservas();
                                            break;
                                    }
                                    if (opcao_3 == 3){
                                        if(confirmarRetorno() == 1) break;
                                        else continue;
                                    }
                                }
                                break;
                            case 4:
                                // Consultas
                                break;
                            case 5:
                                // Relatórios
                                break;
                        }
                        if (opcao == 6){
                                if(confirmarRetorno() == 1) break;
                                else continue;
                        }
                    }
                } 
                else {
                    //Menu dos demais usuarios;
                    while(1){
                        int opcao = menuLogin(listaUsuarios, indiceUsuario);
                        switch(opcao){
                            case 1:
                                listarSessoes(listaSessoes, qtdSessoes, listaUsuarios, indiceUsuario, listaReservas, &qtdReservas);
                                break;

                            case 2:

                                break;

                            case 3:
                                verSaldo(listaUsuarios, indiceUsuario);
                                break;

                            case 4:
                                break;

                            case 5:

                                break;
                        }
                        if (opcao == 6){
                            if(confirmarRetorno() == 1) break;
                            else continue;
                        }
                    }
                }
                break;
            
            case 2:
                // Passamos o endereço de qtdUsuarios (&) para poder alterar o valor original
                cadastro(listaUsuarios, &qtdUsuarios, MAX_USUARIOS);
                break;

            case 3:
                saberMais();
                break;

            case 4:
                if (confirmarSaida() == 1) return 0;
                break;
        }
    }
    return 0;
}