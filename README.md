# 🎬 Sistema de Gerenciamento de Cinema

**Trabalho Prático da disciplina de Algoritmos e Programação II (FACOM32201)**
**Universidade Federal de Uberlândia (UFU) - Faculdade de Computação (FACOM)**

* **Professor:** Prof. Dr. Thiago Pirola Ribeiro 
* **Disciplina:** FACOM32201 - Algoritmos e Programação II 
* **Turma:** 2025-2 
* **Tema:** Gerenciamento de Cinema

---

## 👥 Integrantes do Grupo

* **Nome Completo:** Gianluca Justino Agostinho
    * **Matrícula:** 12511BSI259
* **Nome Completo:** Letícia Moura Lemos 
    * **Matrícula:** 12511BSI215
* **Nome Completo:** Pietro Alves Zanotim
    * **Matrícula:** 12511BSI227
* **Nome Completo:** Renan Cesar Vieira Mallagoli 
    * **Matrícula:** 12511BSI219
* **Nome Completo:** Rhyan Videira Barros Guidastre
    * **Matrícula:** 12511BSI201

---

## 📝 Sobre o Projeto

Este trabalho consiste na implementação de um sistema de gerenciamento para um estabelecimento de cinema , desenvolvido na linguagem C .

O sistema gerencia dois tipos de registros independentes (Sessões e Usuários) e um registro relacional (Reservas), permitindo a execução de operações CRUD (Cadastrar, Consultar, Alterar e Remover) , além da geração de relatórios e listagens específicas, conforme solicitado na descrição do trabalho.

## 🏛️ Estrutura de Dados

O projeto é fundamentado em três estruturas (`structs`) principais, que atendem aos requisitos de possuírem pelo menos 4 campos e um identificador único :

### 1. `Sessoes` (Registro Independente - S1)

Armazena todas as informações pertinentes a uma sessão de filme específica.

```c
typedef struct Sessoes{
    int id;                 // Chave única 
    char horario_inicio[6];
    char horario_final[6];
    char data[9];
    int sala;
    char assento[10][10];   // Matriz de controle de assentos
    char nome_filme[50];
    int limIdade;
    float valorIngresso;
} Sessoes;
```

### 2. `Usuarios` (Registro Independente - S2)

Armazena os dados dos clientes que utilizam o sistema.

```c
typedef struct Usuarios{
    char nome[70];
    int idade;
    char cpf[15];           // Chave única 
    char senha[15];
    float saldo;
} Usuarios;
```

### 3. `Reservas` (Registro Relacional - S3)

Estrutura relacional que conecta um `Usuario` (S2) a uma `Sessao` (S1), atendendo ao requisito de relacionamento .

```c
typedef struct Reservas{
    int id;                 // Chave única da reserva
    char cpf_usuario[15];   // Chave estrangeira (link para Usuarios) 
    int id_sessao;          // Chave estrangeira (link para Sessoes) 
    char assento[4];        // Informação adicional (ex: "F10") 
} Reservas;
```

---

## ⚙️ Funcionalidades Implementadas

O programa apresenta um menu principal que permite ao usuário navegar por todas as funcionalidades exigidas :

* **Gerenciamento de Sessões (S1):**
    * [ ] Cadastrar, Alterar, Consultar e Remover Sessões .
    * [ ] Listar todas as Sessões cadastradas .
* **Gerenciamento de Usuários (S2):**
    * [ ] Cadastrar, Alterar, Consultar e Remover Usuários .
    * [ ] Listar todos os Usuários cadastrados .
* **Gerenciamento de Reservas (S3):**
    * [ ] Cadastrar, Alterar, Consultar e Remover Reservas .
* **Listagens Avançadas (S3) :**
    * [ ] **Listar por Usuário:** Mostra todas as reservas (com dados da sessão) a partir do CPF de um usuário.
    * [ ] **Listar por Sessão:** Mostra todas as reservas (com dados do usuário) a partir do ID de uma sessão.
    * [ ] **Listar por Data:** Mostra todas as reservas (com dados do usuário e da sessão) a partir de uma data específica.
* **Relatórios em Arquivo (.txt) :**
    * [ ] Relatório 1 (Ocupação por Filme): Gera um arquivo texto listando todas as reservas de um filme específico, cruzando dados do assento (S3) com o nome do cliente (S2) e a sala de exibição (S1).
    * [ ] Relatório 2 (Ocupação por Data): Gera um arquivo texto com todas as reservas de uma data específica, detalhando o horário e filme (S1), juntamente com o nome do cliente (S2) e assento ocupado (S3).
    * [ ] Relatório 3 (Histórico do Cliente): Gera um arquivo texto contendo todas as reservas vinculadas a um CPF, incluindo nome do filme e data (S1), além do valor do ingresso pago.

---

## 💾 Persistência de Dados e Gerenciamento de Memória

### Persistência
Em construção...

Os dados são carregados dos arquivos para os vetores na inicialização do programa e salvos de volta nos arquivos ao selecionar a opção "Sair" .

### Gerenciamento de Memória
Em construção..

---

## 🔐 Regras de Integridade

O sistema implementa todas as restrições de integridade de dados exigidas :

1.  **Chaves Únicas:** O programa não permite o cadastro de um novo `Usuario` com um `cpf` já existente, ou uma nova `Sessao` com um `id` duplicado .
2.  **Integridade Relacional (Criação):** Uma `Reserva` (S3) só pode ser criada se o `cpf_usuario` (S2) e o `id_sessao` (S1) existirem nos seus respectivos cadastros .
3.  **Integridade Relacional (Remoção):** Um `Usuario` (S2) ou uma `Sessao` (S1) não podem ser removidos se estiverem associados a qualquer `Reserva` (S3) existente .

---

## 🖥️ Instruções de Compilação e Execução

### Ambiente de Correção
Este projeto foi desenvolvido e testado para atender rigorosamente ao ambiente de correção especificado:

* **IDE:** CodeBlocks versão 25.03 
* **Sistema Operacional:** MS-Windows 11 

### Passos para Execução
1.  Clone este repositório.
Em construção...

### Estrutura de Arquivos
Em construção...
A pasta do projeto contém :
* `main.c`: Contém a lógica do menu e o fluxo principal .
* `README.md`: Este arquivo.
