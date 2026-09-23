# MICRO-PASCAL-COMPILADORES-2026.2

Compilador para a linguagem **micro-Pascal**, desenvolvido como projeto da disciplina de **Construção de Compiladores**, ministrada pelo professor **Robson Lins**, na **Universidade Católica de Pernambuco (UNICAP)**.

Este repositório contém a primeira parte do projeto, correspondente às etapas de:
- **Análise Léxica (Lexer)**
- **Análise Sintática (Parser)**

As etapas seguintes (análise semântica e geração de código) serão desenvolvidas na segunda parte do projeto.

## 👥 Integrantes

- Eduardo Veloso Chaves Malta
- Ayrton Gomes Costa
- Guilherme Eduardo Araujo da Silva

## 📖 Sobre a linguagem micro-Pascal

Micro-Pascal é uma versão simplificada da linguagem Pascal, com estrutura de blocos aninhados (similar a C/Java). O compilador reconhece:

- Identificadores, palavras reservadas, operadores relacionais, lógico-aritméticos e de atribuição
- Literais inteiros, reais e de caractere
- Comandos de atribuição, decisão (`if/then/else`), iteração (`while`, `repeat/until`) e escrita (`write`)

### Exemplo de código em micro-Pascal

```pascal
program TestaParidade;
var
  n : integer;
begin
  n := 2 * 13 + 5;
  if n = (n div 2)*2 then
    write('p');
  else
    write('i');
end.
```

## 🛠️ Tecnologias utilizadas

- **C** — linguagem de implementação do compilador
- **Git** — controle de versão
- **GitHub** — hospedagem do repositório e colaboração
- **Make** — automação do processo de build

## 📁 Estrutura do projeto


```
micropascal-compiler/
├── src/
│   ├── main.c        # Ponto de entrada do programa
│   ├── lexer.c        # Implementação do analisador léxico
│   ├── parser.c        # Implementação do analisador sintático
├── include/
│   ├── lexer.h
│   ├── parser.h
│   └── token.h        # Definições de tokens compartilhadas
├── testes/
│   ├── exemplo1.pas
│   └── exemplo2.pas
├── Makefile
├── .gitignore
└── README.md
```


## ⚙️ Como compilar e executar

### Pré-requisitos

- GCC (ou outro compilador C compatível)
- Make (opcional, mas recomendado)

### Compilando com Make

```bash
make
```

### Compilando manualmente

```bash
gcc -Wall -Wextra -Iinclude src/*.c -o micropascal
```

### Executando

```bash
./micropascal testes/exemplo1.pas
```

## ✅ Funcionalidades implementadas

- [ ] Analisador léxico completo (reconhecimento de todos os tokens)
- [ ] Tratamento de erros léxicos (`Erro léxico no caracter [x]`)
- [ ] Analisador sintático (gramática de micro-Pascal)
- [ ] Tratamento de erros sintáticos (`Erro de sintaxe no token [lexema]`)
- [ ] Testes com exemplos de código válidos

## 🧪 Testes

Os arquivos de teste estão na pasta `testes/`, contendo programas válidos em micro-Pascal utilizados para validar o funcionamento do lexer e do parser.

## 📌 Observações

- A linguagem micro-Pascal é **case-sensitive** (sensível a maiúsculas e minúsculas).
- Caracteres considerados brancos (ignorados pelo lexer): espaço, `\n`, `\t` e `\r`.
- Todos os operadores são associativos à esquerda, seguindo a seguinte ordem de precedência (do maior para o menor):
  1. `*`, `/`, `div`
  2. `+`, `-`
  3. `=`, `<>`, `<`, `>`, `<=`, `>=`
  4. `or`, `and`

## 📄 Licença

Projeto acadêmico desenvolvido para fins educacionais na disciplina de Construção de Compiladores (UNICAP).
