#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"

/*
 * main.c
 *
 * Ponto de entrada do compilador micro-Pascal.
 * Recebe o codigo fonte exclusivamente atraves da entrada do usuario (terminal/stdin).
 */

static FILE *obter_entrada_usuario(void) {
    FILE *temp = tmpfile();
    if (temp == NULL) {
        temp = fopen(".temp_input.pas", "w+");
    }
    if (temp == NULL) {
        fprintf(stderr, "Erro ao criar buffer para a entrada do usuario.\n");
        return NULL;
    }

    printf("Digite o codigo micro-Pascal (finalize com 'end.' ou Ctrl+D no Linux / Ctrl+Z no Windows):\n");

    char buffer[1024];
    int leu_algo = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        leu_algo = 1;
        fputs(buffer, temp);

        /* Se a linha contiver o encerramento do programa 'end.', finaliza a entrada */
        if (strstr(buffer, "end.") != NULL || strstr(buffer, "end .") != NULL) {
            break;
        }
    }

    if (!leu_algo) {
        fprintf(stderr, "Erro: nenhum codigo foi informado.\n");
        fclose(temp);
        return NULL;
    }

    rewind(temp);
    return temp;
}

int main(void) {
    FILE *arquivo = obter_entrada_usuario();
    if (arquivo == NULL) {
        return EXIT_FAILURE;
    }

    Lexer lexer;
    lexer_inicializar(&lexer, arquivo);

    Parser parser;
    parser_inicializar(&parser, &lexer);

    parser_analisar_programa(&parser);

    lexer_finalizar(&lexer);
    fclose(arquivo);
    remove(".temp_input.pas");

    printf("\nAnalise sintatica concluida com sucesso!\n");
    return EXIT_SUCCESS;
}