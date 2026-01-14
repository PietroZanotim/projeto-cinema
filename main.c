#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utils.h"
#include "usuarios.h"
#include "sessoes.h"
#include "reservas.h"
#include "admin.h"
#include "persistencia.h"
#include "CRUD_sessoes.h"
#include "CRUD_usuarios.h"
#include "CRUD_reservas.h"
#include "cons_rel.h"

#define MAX_USUARIOS 5
#define MAX_SESSOES 5
#define MAX_RESERVAS 10

int main()
{
    // Criação das variáveis "Globais" dentro da main
    Usuarios listaUsuarios[MAX_USUARIOS];
    Sessoes listaSessoes[MAX_SESSOES];
    Reservas listaReservas[MAX_RESERVAS];

    //Sessao temporaria para testarmos

    listaSessoes[0].id = 0;
    strcpy(listaSessoes[0].nome_filme,"Cinema");
    listaSessoes[0].limIdade = 18;
    listaSessoes[0].sala = 1;
    listaSessoes[0].valorIngresso = 20.00;
    strcpy(listaSessoes[0].data,"20/02/2026");
    strcpy(listaSessoes[0].horario_inicio,"14:30");
    strcpy(listaSessoes[0].horario_final,"16:00");
    for(int L = 0; L < 10; L++) {
        for(int C = 0; C < 10; C++) {
            listaSessoes[0].assento[L][C] = '0';
        }
    }

    // Sistema temporário para acessar o admin
    listaUsuarios[0].idade = 0;
    strcpy(listaUsuarios[0].nome, "Admin");
    strcpy(listaUsuarios[0].cpf, "000.000.000-00");
    strcpy(listaUsuarios[0].senha, "123senha");

    int qtdUsuarios = 1; // 1 por causa do Admin
    int qtdSessoes = 1; // Sessao teste;
    int qtdReservas = 0;

    // Variaveis para marcar o id, pois se usarmos as váriaveis qtd, pode haver duplicidade....
    int idReservas=0;
    int idSessoes=0;

    while (1)
    {
        int opcao = menuPrincipal();

        switch (opcao)
        {
        case 1: // Login do usuario;

            int indiceUsuario = login(listaUsuarios, qtdUsuarios); // Pegamos a posição do usuario;

            if (indiceUsuario == 0)
            {
                // Menu do admin
                while(1)
                {
                    int opcao = menuAdmin();
                    switch(opcao)
                    {
                    case 1:
                        // CRUD de Sessões
                        while(1)
                        {
                            int opcao_1 = menu_CRUD_sessoes();
                            switch(opcao_1)
                            {
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
                            if (opcao_1 == 6)
                            {
                                if(confirmarRetorno() == 1) break;
                                else continue;
                            }
                        }
                        break;
                    case 2:
                        // CRUD de Usuários
                        while(1)
                        {
                            int opcao_2 = menu_CRUD_usuarios();
                            switch(opcao_2)
                            {
                            case 1:
                                adicionar_usuario(listaUsuarios, &qtdUsuarios, MAX_USUARIOS);
                                break;
                            case 2:
                                excluir_usuario(listaUsuarios, &qtdUsuarios); // Verificar o controle de memória...
                                break;
                            case 3:
                                modificar_usuario(listaUsuarios, &qtdUsuarios);
                                break;
                            case 4:
                                visualizar_usuario_cpf(listaUsuarios, &qtdUsuarios);
                                break;
                            case 5:
                                visualizar_todos_usuarios(listaUsuarios, qtdUsuarios);
                                break;
                            }
                            if (opcao_2 == 6)
                            {
                                if(confirmarRetorno() == 1) break;
                                else continue;
                            }
                        }
                        break;
                    case 3:
                        // CRUD de Reservas
                        while(1)
                        {
                            int opcao_3 = menu_CRUD_reservas();
                            switch(opcao_3)
                            {
                                case 1:
                                    adicionar_reserva(listaReservas, &qtdReservas, listaUsuarios, qtdUsuarios, listaSessoes, qtdSessoes, &idReservas);
                                    break;
                                case 2:
                                    excluir_reserva(listaReservas, &qtdReservas, listaUsuarios);
                                    break;
                                case 3:
                                    modificar_reserva(listaReservas, qtdReservas, listaUsuarios, listaSessoes, qtdSessoes);
                                    break;
                                case 4:
                                    visualizar_reserva_id(listaReservas, qtdReservas, listaUsuarios);
                                    break;
                                case 5:
                                    visualizar_todas_reservas(listaReservas, qtdReservas, listaUsuarios);
                                    break;
                            }
                            if (opcao_3 == 6)
                            {
                                if(confirmarRetorno() == 1) break;
                                else continue;
                            }
                        }
                        break;
                    case 4:
                        // Consultas
                        while(1){
                            int opcao_4 = menu_consulta();
                            switch(opcao_4){
                                case 1:
                                    CONS_reservas_por_filme(listaUsuarios, listaSessoes, listaReservas, qtdUsuarios, qtdSessoes, qtdReservas);
                                    break;
                                case 2:
                                    CONS_reservas_por_data(listaUsuarios, listaSessoes, listaReservas, qtdUsuarios, qtdSessoes, qtdReservas);
                                    break;
                                case 3:
                                    CONS_reservas_por_cpf(listaUsuarios, listaSessoes, listaReservas, qtdUsuarios, qtdSessoes, qtdReservas);
                                    break;
                            }
                            if (opcao_4 == 4){
                                if(confirmarRetorno() == 1) break;
                                else continue;
                            }
                        }
                        break;
                    case 5:
                        // Relatórios
                        while(1){
                            int opcao_5 = menu_relatorio();
                            switch(opcao_5){
                                case 1:
                                    REL_listar_usuarios(listaUsuarios, qtdUsuarios);
                                    break;
                                case 2:
                                    REL_listar_sessoes(listaSessoes, qtdSessoes);
                                    break;
                                case 3:
                                    RELATORIO_reservas_completo(listaUsuarios, qtdUsuarios, listaSessoes, qtdSessoes, listaReservas, qtdReservas);
                                    break;
                            }
                            if (opcao_5 == 4){
                                if(confirmarRetorno() == 1) break;
                                else continue;
                            }
                        }
                        break;
                    }
                    if (opcao == 6)
                    {
                        if(confirmarRetorno() == 1) break;
                        else continue;
                    }
                }
            }
            else
            {
                //Menu dos demais usuarios;
                while(1)
                {
                    char exclusaobreak = 'N'; // Adicionei para caso o usuário seja excluido, saia do menu;

                    int opcao = menuLogin(listaUsuarios, indiceUsuario);

                    switch(opcao)
                    {
                    case 1:
                        limparTela();
                        listarSessoes(listaSessoes, qtdSessoes, listaUsuarios, indiceUsuario, listaReservas, &qtdReservas, &idReservas);
                        break;

                    case 2:
                        visualizarReservas(listaReservas, qtdReservas, listaUsuarios, indiceUsuario, listaSessoes, qtdSessoes);
                        break;

                    case 3:
                        verSaldo(listaUsuarios, indiceUsuario);
                        break;

                    case 4:
                        modificarSenha(listaUsuarios, indiceUsuario);
                        break;

                    case 5:
                        exclusaoUsuario(listaUsuarios, indiceUsuario, &qtdUsuarios, &exclusaobreak);
                        break;
                    }

                    if (opcao == 6)
                    {
                        if(confirmarRetorno() == 1) break;
                        else continue;
                    }

                    if(exclusaobreak=='S'){ //Se o usuario excluir esse registro atual, saia do menu;
                        break;
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
            if (confirmarSaida() == 1){
                finalizar_sistema(listaUsuarios, listaSessoes, listaReservas, qtdUsuarios, qtdSessoes, qtdReservas);
                return 0;
            }
            break;
        }
    }
    return 0;
}
