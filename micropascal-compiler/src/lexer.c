#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"

/*
 * main.c
 *
 * Ponto de entrada do compilador micro-Pascal.
 * Uso: ./micropascal <arquivo_fonte>
 *
 * Resultado:
 *   - sem erros: imprime "Analise concluida com sucesso!" e retorna 0
 *   - com erro lexico ou sintatico: a mensagem de erro e impressa e o
 *     programa termina com codigo 1
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_fonte>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    Lexer lexer;
    lexer_inicializar(&lexer, arquivo);

    Parser parser;
    parser_inicializar(&parser, &lexer);

    parser_analisar_programa(&parser);

    lexer_finalizar(&lexer);
    fclose(arquivo);

    printf("Analise concluida com sucesso! Nenhum erro encontrado.\n");
    return EXIT_SUCCESS;
}