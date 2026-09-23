#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"

/*
 * parser.h
 *
 * Interface do analisador sintático do micro-Pascal.
 * O parser consome os tokens produzidos pelo lexer e verifica
 * se o programa de entrada respeita a gramática da linguagem.
 */

typedef struct {
    Lexer *lexer;
    Token token_atual;
} Parser;

/* Inicializa o parser associando-o a um lexer já inicializado */
void parser_inicializar(Parser *parser, Lexer *lexer);

/* Inicia a análise sintática a partir do símbolo inicial <programa> */
void parser_analisar_programa(Parser *parser);

#endif /* PARSER_H */
