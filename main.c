#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "usuarios.h"

#define MAX_USUARIOS 100 

int main(){
    // Criação das variáveis "Globais" dentro da main
    Usuarios listaUsuarios[MAX_USUARIOS];
    int qtdUsuarios = 0; 
    
    while (1) {
        int opcao = menuPrincipal();

        switch (opcao){
            case 1:
                executarLogin(listaUsuarios, qtdUsuarios);
                break;
            
            case 2:
                // Passamos o endereço de qtdUsuarios (&) para poder alterar o valor original
                executarCadastro(listaUsuarios, &qtdUsuarios, MAX_USUARIOS);
                break;

            case 3:
                // saberMais();
                break;

            case 4:
                if (confirmarSaida() == 1) return 0;
                break;
        }
    }
    return 0;
}