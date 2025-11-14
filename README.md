================================================================================
 UNIVERSIDADE FEDERAL DE UBERLÂNDIA (UFU)
 FACULDADE DE COMPUTAÇÃO (FACOM)
 CURSO: BACHARELADO EM SISTEMAS DE INFORMAÇÃO

 DISCIPLINA: FACOM32201 - Algoritmos e Programação II 
 PROFESSOR: Prof. Dr. Thiago Pirola Ribeiro 
 ANO/TURMA: 2025-2 

 TRABALHO PRÁTICO 
================================================================================

 === INTEGRANTES DO GRUPO ===

     * Nome: [Nome Completo do Aluno 1], Matrícula: [Matrícula do Aluno 1]
     * Nome: [Nome Completo do Aluno 2], Matrícula: [Matrícula do Aluno 2]
     * Nome: [Nome Completo do Aluno 3], Matrícula: [Matrícula do Aluno 3]
     * Nome: [Nome Completo do Aluno 4], Matrícula: [Matrícula do Aluno 4]
     * Nome: [Nome Completo do Aluno 5], Matrícula: [Matrícula do Aluno 5] (Opcional)


================================================================================
 === 1. DESCRIÇÃO GERAL DO PROJETO ===
================================================================================

 Tema: Sistema de Gerenciamento de Cinema

 Este projeto implementa um sistema de gerenciamento para um Cinema, conforme
 as especificações do Trabalho Prático da disciplina .

 O programa gerencia três estruturas de dados principais:
    1. SESSÕES (Estrutura 1, Independente)
    2. USUÁRIOS (Estrutura 2, Independente)
    3. RESERVAS (Estrutura 3, Relacional)

 O sistema foi desenvolvido inteiramente na linguagem C e atende
 a todos os requisitos de funcionalidade, incluindo persistência de dados
 em arquivos binários , uso de alocação dinâmica de memória 
 e respeito às regras de integridade relacional .


================================================================================
 === 2. INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO ===
================================================================================

 Este é um requisito fundamental para a correção do trabalho .

 1. AMBIENTE DE CORREÇÃO:
    O programa foi desenvolvido e testado para ser compilado e executado no
    ambiente especificado:
    * IDE: CodeBlocks versão 25.03 
    * Sistema Operacional: MS-Windows 11 

 2. COMPILAÇÃO:
    Para compilar e executar o projeto, basta abrir o arquivo de projeto
    CodeBlocks (.cbp) incluído nesta pasta e utilizar a opção "Build and Run"
    (ou tecla F9).
    Todos os arquivos de cabeçalho (.h) e código-fonte (.c) estão
    corretamente vinculados no projeto.

 3. EXECUÇÃO E ARQUIVOS DE DADOS:
    No primeiro uso (ou se os arquivos forem apagados), o programa criará os
    arquivos binários automaticamente.
    Nas execuções subsequentes, o programa carregará os dados salvos
    anteriormente, garantindo a persistência .

    O programa gerencia os seguintes arquivos na pasta raiz:
    * sessoes.bin: Arquivo binário para os dados da Estrutura 1.
    * usuarios.bin: Arquivo binário para os dados da Estrutura 2.
    * reservas.bin: Arquivo binário para os dados da Estrutura 3.

    Os arquivos .bin pré-preenchidos e submetidos contêm, cada um,
    pelo menos 10 registros para fins de teste, conforme solicitado .


================================================================================
 === 3. FUNCIONALIDADES IMPLEMENTADAS ===
================================================================================

 O programa apresenta um menu principal que permite ao usuário
 acessar todas as funcionalidades exigidas:

 --- MÓDULO SESSÕES (Estrutura 1) ---
    [X] (a) Cadastrar, Alterar, Consultar e Remover (CRUD) SESSÕES .
    [X] (d) Listar todos os dados de todas as SESSÕES cadastradas .

 --- MÓDULO USUÁRIOS (Estrutura 2) ---
    [X] (b) Cadastrar, Alterar, Consultar e Remover (CRUD) USUÁRIOS .
    [X] (e) Listar todos os dados de todos os USUÁRIOS cadastrados .

 --- MÓDULO RESERVAS (Estrutura 3) ---
    [X] (c) Cadastrar, Alterar, Consultar e Remover (CRUD) RESERVAS .
    [X] (f) Listagem complexa de RESERVAS (3 características específicas) .
    [X] (g) Geração de 3 Relatórios distintos em arquivo texto (.txt) .

 --- GERENCIAMENTO DE MEMÓRIA E DADOS ---
    [X] (4) Alocação dinâmica de memória (malloc/realloc) para os vetores .
    [X] (4) Controle de realocação com 5 posições de folga .
    [X] (7) Verificação de chave única (ID para Sessão, CPF para Usuário) .
    [X] (7) Verificação de integridade relacional (S3 só existe se S1 e S2 existirem) .
    [X] (7) Bloqueio de exclusão (S1/S2 não podem ser removidos se em S3) .
    [X] (10) Código modularizado com uso extensivo de funções .


================================================================================
 === 4. OBSERVAÇÕES ADICIONAIS ===
================================================================================

 * INDENTAÇÃO: O código-fonte segue rigorosamente as normas de
     indentação para facilitar a leitura e correção .
 * FUNÇÕES DE BUSCA: Foram implementadas funções de busca para
     cada estrutura, que retornam o índice do elemento. Essas funções são
     a base para as operações de Alteração, Remoção e verificação de
     integridade, otimizando o código.
