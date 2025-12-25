#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "usuarios.h"

#define MAX_USUARIOS 5
#define MAX_SESSOES 5
#define MAX_RESERVAS 10

int main(){
    // Criação das variáveis "Globais" dentro da main
    Usuarios listaUsuarios[MAX_USUARIOS];
    Sessoes listaSessoes[MAX_SESSOES];
    Reservas listaReservas[MAX_RESERVAS];

    int qtdUsuarios = 0;
    int qtdSessoes = 0;
    
    while (1) {
        int opcao = menuPrincipal();

        switch (opcao){
            case 1: // Login do usuario;
                    
                int indiceUsuario = login(listaUsuarios, qtdUsuarios); // Pegamos a posição do usuario;
                
                if(listaUsuarios[indiceUsuario].cpf=="000.000.000-00") {
                    //Menu do admin;

                } else {
                    //Menu dos demais usuarios;
                    while(1){

                        int opcao = menuLogin(listaUsuarios, indiceUsuario);

                        switch(opcao){
                            
                            case 1:

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

                            case 6:

                                break;
                        }
                        if(opcao==6){
                            if (confirmarRetorno() == 1){
                                break; // Break para sair do loop do menu de login;
                            }
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