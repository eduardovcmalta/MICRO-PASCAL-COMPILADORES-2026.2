#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

static parser_avancar(Parser *parser);
static void parser_erro(Parser *parser);
static void parser_esperra(Parser *parser, TipoToken tipo);

static void parser_secao_var(Parser *parser);
static void parser_decl_var(Parser *parser);
static void parser_tipo(Parser *parser);
static void parser_bloco(Parser *parser);
static void parser_lista_comandos(Parser *parser);
static void parser_comando(Parser *parser);
static void parser_atribuicao(Parser *parser);
static void parser_iteracao(Parser *parser);
static void parser_decisao(Parser *parser);
static void parser_escrita(Parser *parser);

static void parser_expressao(Parser *parser);
static void parser_relacional(Parser *parser);
static void parser_soma(Parser *parser);
static void parser_termo(Parser *parser);
static void parser_fator(Parser *parser);

static void parser_avancar(Parser *parser) {
    parser ->token_atual = lexer_proximo_token (parser->lexer);
}

static void parser_erro(Parser *parser){
    fprintf(stderr, "Erro de sintaxe no token %s\n", parser->token_atual.lexema);
    exit(1);
}

static void parser_esperar(Parser *parser, TipoToken tipo) {
    if (parser->token_atual.tipo == tipo){
        parser_avancar(parser);
    } else {
        parser_erro(parser);
    }
}

void parser_analisar_programa(Parser *parser ){
    parser_esperar(parser, TOKEN_PROGRAM);
    parser_esperar(parser, TOKEN_IDENTIFICADOR);
    parser_esperar(parser, TOKEN_PONTO_VIRGULA);
    parser_secao_var(parser);
    parser_bloco(parser);
    parser_esperar(parser, TOKEN_PONTO);
}

static void parser_secao_var(Parser *parser) {
    parser_esperar(parser, TOKEN_VAR);
    while (parser->token_atual.tipo == TOKEN_IDENTIFICADOR){
        parser_decl_var(parser);
    }
}

