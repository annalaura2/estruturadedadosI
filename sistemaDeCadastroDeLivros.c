#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Livro, que representa as informações de um livro
struct Livro {
    int codigo;
    char titulo[50];
    char autor[50];
    float preco;
};

// Função para incluir um novo livro no arquivo
void incluirLivro(FILE *arquivo) {
    // Cria uma nova instância da estrutura Livro
    struct Livro novoLivro;

    // Solicita ao usuário que digite as informações do livro
    printf("Digite o código do livro: ");
    scanf("%d", &novoLivro.codigo);

    printf("Digite o título do livro: ");
    scanf(" %[^\n]", novoLivro.titulo);

    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", novoLivro.autor);

    printf("Digite o preço do livro: ");
    scanf("%f", &novoLivro.preco);

    // Move o cursor para o final do arquivo
    fseek(arquivo, 0, SEEK_END);

    // Escreve as informações do novo livro no arquivo
    fwrite(&novoLivro, sizeof(struct Livro), 1, arquivo);

    // Informa ao usuário que o livro foi cadastrado com sucesso
    printf("Livro cadastrado com sucesso!\n");
}

// Função para alterar as informações de um livro existente no arquivo
void alterarLivro(FILE *arquivo, int codigoAlvo) {
    // Cria uma instância da estrutura Livro
    struct Livro livro;

    // Move o cursor para o início do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Lê cada registro do arquivo até encontrar o livro com o código desejado
    while (fread(&livro, sizeof(struct Livro), 1, arquivo) == 1) {
        // Verifica se o código do livro coincide com o código informado pelo usuário
        if (livro.codigo == codigoAlvo) {
            // Solicita ao usuário que digite as novas informações do livro
            printf("Digite o novo título do livro: ");
            scanf(" %[^\n]", livro.titulo);

            printf("Digite o novo autor do livro: ");
            scanf(" %[^\n]", livro.autor);

            printf("Digite o novo preço do livro: ");
            scanf("%f", &livro.preco);

            // Move o cursor para a posição de escrita
            fseek(arquivo, -sizeof(struct Livro), SEEK_CUR);

            // Escreve as alterações no arquivo
            fwrite(&livro, sizeof(struct Livro), 1, arquivo);

            // Informa ao usuário que o livro foi alterado com sucesso
            printf("Livro alterado com sucesso!\n");
            return;
        }
    }

    // Informa ao usuário que o livro não foi encontrado
    printf("Livro não encontrado.\n");
}

// Função para excluir um livro do arquivo
void excluirLivro(FILE *arquivo, int codigoAlvo) {
    // Cria um arquivo temporário para armazenar os registros excluindo o desejado
    FILE *temporario = fopen("temporario.dat", "w");
    if (temporario == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        exit(1);
    }

    // Cria uma instância da estrutura Livro
    struct Livro livro;

    // Move o cursor para o início do arquivo
    fseek(arquivo, 0, SEEK_SET);

    // Lê cada registro do arquivo
    while (fread(&livro, sizeof(struct Livro), 1, arquivo) == 1) {
        // Verifica se o código do livro não coincide com o código a ser excluído
        if (livro.codigo != codigoAlvo) {
            // Escreve o registro no arquivo temporário
            fwrite(&livro, sizeof(struct Livro), 1, temporario);
        }
    }

    // Fecha os arquivos
    fclose(arquivo);
    fclose(temporario);

    // Remove o arquivo original
    remove("livros.dat");

    // Renomeia o arquivo temporário para o nome original
    rename("temporario.dat", "livros.dat");

    // Informa ao usuário que o livro foi excluído com sucesso
    printf("Livro excluído com sucesso!\n");
}

// Função principal do programa
int main() {
    // Declaração do ponteiro de arquivo
    FILE *arquivo;

    // Abre o arquivo para leitura e escrita
    arquivo = fopen("livros.dat", "a+b");

    // Verifica se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int opcao, codigo;

    // Menu principal do programa
    do {
        printf("\n1 - Incluir livro\n2 - Alterar livro\n3 - Excluir livro\n0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a opção escolhida pelo usuário
        switch (opcao) {
            case 1:
                incluirLivro(arquivo);
                break;
            case 2:
                printf("Digite o código do livro a ser alterado: ");
                scanf("%d", &codigo);
                alterarLivro(arquivo, codigo);
                break;
            case 3:
                printf("Digite o código do livro a ser excluído: ");
                scanf("%d", &codigo);
                excluirLivro(arquivo, codigo);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}
/*Estrutura Livro:
struct Livro é uma estrutura que define as informações de um livro, incluindo código, título, autor e preço.

Função incluirLivro:
Esta função solicita ao usuário as informações de um novo livro e as armazena no final do arquivo.

Função alterarLivro:
Lê os registros do arquivo até encontrar o livro com o código especificado pelo usuário.
Solicita ao usuário novas informações para o livro e sobrescreve as informações antigas no arquivo.

Função excluirLivro:
Cria um arquivo temporário e copia todos os registros, exceto o livro com o código especificado pelo usuário.
Substitui o arquivo original pelo temporário.

Função main:
Abre o arquivo "livros.dat" para leitura e escrita.
Apresenta um menu para o usuário com opções para incluir, alterar, excluir livros ou sair do programa.
Executa a opção escolhida até que o usuário escolha sair (opção 0).
Fecha o arquivo antes de encerrar o programa para*/
