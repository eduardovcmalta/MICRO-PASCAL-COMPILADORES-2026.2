#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/lexer.h"

/*
 * lexer.c
 *
 * Implementação do analisador léxico do micro-Pascal.
 *
 * TODO:
 *   - Reconhecer identificadores e palavras reservadas
 *   - Reconhecer operadores relacionais (<, >, <=, >=, =, <>)
 *   - Reconhecer operadores lógico-aritméticos (+, -, *, /, div, and, or, not)
 *   - Reconhecer operador de atribuição (:=)
 *   - Reconhecer símbolos especiais ( ) , ; . :
 *   - Reconhecer literais inteiros, reais e de caractere
 *   - Ignorar espaços, \n, \t, \r
 *   - Emitir erro no formato: "Erro léxico no caracter [x]"
 */

void lexer_inicializar(Lexer *lexer, FILE *arquivo) {
    lexer->arquivo = arquivo;
    lexer->linha_atual = 1;
    lexer->caractere_atual = fgetc(arquivo);
}

Token lexer_proximo_token(Lexer *lexer) {
    Token token;
    token.tipo = TOKEN_EOF;
    token.lexema[0] = '\0';
    token.linha = lexer->linha_atual;

    /* TODO: implementar reconhecimento dos tokens */

    return token;
}

void lexer_finalizar(Lexer *lexer) {
    /* TODO: liberar recursos, se necessário */
    (void)lexer;
}
