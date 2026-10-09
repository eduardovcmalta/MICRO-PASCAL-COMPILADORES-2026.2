#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/lexer.h"

/* ==================== Inicialização / Finalização ==================== */

void lexer_inicializar(Lexer *lexer, FILE *arquivo) {
    lexer->arquivo = arquivo;
    lexer->linha_atual = 1;
    lexer->caractere_atual = fgetc(arquivo);
}

void lexer_finalizar(Lexer *lexer) {
    (void)lexer;
}

/* ==================== Auxiliares internas ==================== */

static int avancar(Lexer *lexer) {
    int c = fgetc(lexer->arquivo);
    lexer->caractere_atual = c;
    return c;
}

static void pular_comentario(Lexer *lexer) {
    /* assume-se comentario estilo C++: // ate o fim da linha */
    while (lexer->caractere_atual != '\n' && lexer->caractere_atual != EOF) {
        avancar(lexer);
    }
}

static void pular_brancos(Lexer *lexer) {
    while (1) {
        if (lexer->caractere_atual == ' '  || lexer->caractere_atual == '\n' ||
            lexer->caractere_atual == '\t' || lexer->caractere_atual == '\r') {
            if (lexer->caractere_atual == '\n') {
                lexer->linha_atual++;
            }
            avancar(lexer);
        } else if (lexer->caractere_atual == '/') {
            long posicao = ftell(lexer->arquivo);
            int c = avancar(lexer);
            if (c == '/') {
                pular_comentario(lexer);
            } else {
                /* nao era comentario: restaura o ponteiro do arquivo e o caractere atual */
                fseek(lexer->arquivo, posicao, SEEK_SET);
                lexer->caractere_atual = '/';
                return;
            }
        } else {
            return;
        }
    }
}

/* ==================== Palavras reservadas ==================== */

static TipoToken verificar_palavra_reservada(const char *lexema) {
    if (strcmp(lexema, "program") == 0) return TOKEN_PROGRAM;
    if (strcmp(lexema, "if") == 0)      return TOKEN_IF;
    if (strcmp(lexema, "then") == 0)    return TOKEN_THEN;
    if (strcmp(lexema, "else") == 0)    return TOKEN_ELSE;
    if (strcmp(lexema, "while") == 0)   return TOKEN_WHILE;
    if (strcmp(lexema, "do") == 0)      return TOKEN_DO;
    if (strcmp(lexema, "repeat") == 0)  return TOKEN_REPEAT;
    if (strcmp(lexema, "until") == 0)   return TOKEN_UNTIL;
    if (strcmp(lexema, "integer") == 0) return TOKEN_INTEGER;
    if (strcmp(lexema, "real") == 0)    return TOKEN_REAL;
    if (strcmp(lexema, "char") == 0)    return TOKEN_CHAR;
    if (strcmp(lexema, "begin") == 0)   return TOKEN_BEGIN;
    if (strcmp(lexema, "end") == 0)     return TOKEN_END;
    if (strcmp(lexema, "write") == 0)   return TOKEN_WRITE;
    if (strcmp(lexema, "var") == 0)     return TOKEN_VAR;
    if (strcmp(lexema, "div") == 0)     return TOKEN_DIV_INT;
    if (strcmp(lexema, "and") == 0)     return TOKEN_AND;
    if (strcmp(lexema, "or") == 0)      return TOKEN_OR;
    if (strcmp(lexema, "not") == 0)     return TOKEN_NOT;

    return TOKEN_IDENTIFICADOR;
}

/* ==================== Identificadores / Palavras reservadas ==================== */

static Token ler_identificador(Lexer *lexer) {
    Token token;
    int i = 0;

    while (isalnum(lexer->caractere_atual) || lexer->caractere_atual == '_') {
        token.lexema[i++] = (char)lexer->caractere_atual;
        avancar(lexer);
    }
    token.lexema[i] = '\0';

    token.tipo = verificar_palavra_reservada(token.lexema);
    token.linha = lexer->linha_atual;
    return token;
}

/* ==================== Números (inteiro / real) ==================== */

static Token ler_numero(Lexer *lexer) {
    Token token;
    int i = 0;

    while (isdigit(lexer->caractere_atual)) {
        token.lexema[i++] = (char)lexer->caractere_atual;
        avancar(lexer);
    }

    if (lexer->caractere_atual == '.') {
        token.lexema[i++] = '.';
        avancar(lexer);
        while (isdigit(lexer->caractere_atual)) {
            token.lexema[i++] = (char)lexer->caractere_atual;
            avancar(lexer);
        }
        token.tipo = TOKEN_REAL_LITERAL;
    } else {
        token.tipo = TOKEN_INTEIRO_LITERAL;
    }

    token.lexema[i] = '\0';
    token.linha = lexer->linha_atual;
    return token;
}

/* ==================== Caractere literal ==================== */

static Token ler_char_literal(Lexer *lexer) {
    Token token;
    int i = 0;

    token.lexema[i++] = '\'';
    avancar(lexer);

    if (lexer->caractere_atual == '\\') {
        token.lexema[i++] = '\\';
        avancar(lexer);
        if (lexer->caractere_atual == 'n' || lexer->caractere_atual == 't') {
            token.lexema[i++] = (char)lexer->caractere_atual;
            avancar(lexer);
        } else {
            printf("Erro léxico no caracter %c\n", lexer->caractere_atual);
            token.tipo = TOKEN_ERRO;
            token.linha = lexer->linha_atual;
            avancar(lexer);
            return token;
        }
    } else if (isalnum(lexer->caractere_atual)) {
        token.lexema[i++] = (char)lexer->caractere_atual;
        avancar(lexer);
    } else {
        printf("Erro léxico no caracter %c\n", lexer->caractere_atual);
        token.tipo = TOKEN_ERRO;
        token.linha = lexer->linha_atual;
        avancar(lexer);
        return token;
    }

    if (lexer->caractere_atual != '\'') {
        printf("Erro léxico no caracter %c\n", lexer->caractere_atual);
        token.tipo = TOKEN_ERRO;
        token.linha = lexer->linha_atual;
        avancar(lexer);
        return token;
    }

    token.lexema[i++] = '\'';
    avancar(lexer);
    token.lexema[i] = '\0';

    token.tipo = TOKEN_CHAR_LITERAL;
    token.linha = lexer->linha_atual;
    return token;
}

/* ==================== Operadores / Símbolos especiais ==================== */

static Token ler_operador_ou_simbolo(Lexer *lexer) {
    Token token;
    token.linha = lexer->linha_atual;
    int c = lexer->caractere_atual;

    switch (c) {
        case '<':
            avancar(lexer);
            if (lexer->caractere_atual == '=') {
                strcpy(token.lexema, "<=");
                token.tipo = TOKEN_MENOR_IGUAL;
                avancar(lexer);
            } else if (lexer->caractere_atual == '>') {
                strcpy(token.lexema, "<>");
                token.tipo = TOKEN_DIFERENTE;
                avancar(lexer);
            } else {
                strcpy(token.lexema, "<");
                token.tipo = TOKEN_MENOR;
            }
            return token;

        case '>':
            avancar(lexer);
            if (lexer->caractere_atual == '=') {
                strcpy(token.lexema, ">=");
                token.tipo = TOKEN_MAIOR_IGUAL;
                avancar(lexer);
            } else {
                strcpy(token.lexema, ">");
                token.tipo = TOKEN_MAIOR;
            }
            return token;

        case ':':
            avancar(lexer);
            if (lexer->caractere_atual == '=') {
                strcpy(token.lexema, ":=");
                token.tipo = TOKEN_ATRIBUICAO;
                avancar(lexer);
            } else {
                strcpy(token.lexema, ":");
                token.tipo = TOKEN_DOISPONTOS;
            }
            return token;

        case '+': strcpy(token.lexema, "+"); token.tipo = TOKEN_MAIS;        avancar(lexer); return token;
        case '-': strcpy(token.lexema, "-"); token.tipo = TOKEN_MENOS;       avancar(lexer); return token;
        case '*': strcpy(token.lexema, "*"); token.tipo = TOKEN_MULT;        avancar(lexer); return token;
        case '/': strcpy(token.lexema, "/"); token.tipo = TOKEN_DIV_REAL;    avancar(lexer); return token;
        case '=': strcpy(token.lexema, "="); token.tipo = TOKEN_IGUAL;       avancar(lexer); return token;
        case '(': strcpy(token.lexema, "("); token.tipo = TOKEN_ABRE_PAREN;  avancar(lexer); return token;
        case ')': strcpy(token.lexema, ")"); token.tipo = TOKEN_FECHA_PAREN; avancar(lexer); return token;
        case ',': strcpy(token.lexema, ","); token.tipo = TOKEN_VIRGULA;     avancar(lexer); return token;
        case ';': strcpy(token.lexema, ";"); token.tipo = TOKEN_PONTOVIRG;   avancar(lexer); return token;
        case '.': strcpy(token.lexema, "."); token.tipo = TOKEN_PONTO;       avancar(lexer); return token;

        default:
            printf("Erro léxico no caracter %c\n", c);
            token.lexema[0] = (char)c;
            token.lexema[1] = '\0';
            token.tipo = TOKEN_ERRO;
            avancar(lexer);
            return token;
    }
}

/* ==================== Próximo token ==================== */

Token lexer_proximo_token(Lexer *lexer) {
    pular_brancos(lexer);

    if (lexer->caractere_atual == EOF) {
        Token token;
        token.tipo = TOKEN_EOF;
        token.lexema[0] = '\0';
        token.linha = lexer->linha_atual;
        return token;
    }

    if (isalpha(lexer->caractere_atual) || lexer->caractere_atual == '_') {
        return ler_identificador(lexer);
    }

    if (isdigit(lexer->caractere_atual)) {
        return ler_numero(lexer);
    }

    if (lexer->caractere_atual == '\'') {
        return ler_char_literal(lexer);
    }

    return ler_operador_ou_simbolo(lexer);
}