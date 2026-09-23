#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

/*
 * parser.c
 *
 * Implementação do analisador sintático do micro-Pascal.
 *
 * TODO:
 *   - Implementar <programa>, <secao_var>, <decl_var>, <tipo>
 *   - Implementar <bloco>, <lista_comandos>, <comando>
 *   - Implementar <atribuicao>, <iteracao>, <decisao>, <escrita>
 *   - Implementar <expressao> e <expr_basica> respeitando a precedência:
 *       1. *, /, div
 *       2. +, -
 *       3. =, <>, <, >, <=, >=
 *       4. or, and
 *     (todos associativos à esquerda; atenção à recursão à esquerda
 *      da gramática abstrata original, que precisa ser eliminada)
 *   - Emitir erro no formato: "Erro de sintaxe no token [lexema]"
 */

static void parser_avancar(Parser *parser) {
    parser->token_atual = lexer_proximo_token(parser->lexer);
}

void parser_inicializar(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
    parser_avancar(parser);
}

void parser_analisar_programa(Parser *parser) {
    /* TODO: implementar <programa> ::= program IDENTIFICADOR ; <secao_var> <bloco> . */
    (void)parser;
}
