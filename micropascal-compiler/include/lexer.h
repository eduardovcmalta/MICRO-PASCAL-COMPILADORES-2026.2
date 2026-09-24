
#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

/*
 * lexer.h
 *
 * Interface do analisador léxico do micro-Pascal.
 */

typedef struct {
    FILE *arquivo;
    int linha_atual;
    int caractere_atual;
} Lexer;

/* Inicializa o lexer a partir de um arquivo já aberto */
void lexer_inicializar(Lexer *lexer, FILE *arquivo);

/* Retorna o próximo token do arquivo de entrada */
Token lexer_proximo_token(Lexer *lexer);

/* Libera/fecha recursos usados pelo lexer, se necessário */
void lexer_finalizar(Lexer *lexer);

#endif /* LEXER_H */
