// ===================================================================
// teste_lexer.pas
// Arquivo de teste para validação do analisador léxico (Eduardo)
// Cobre todos os tipos de token da especificação de micro-Pascal.
// ===================================================================

program TesteLexico;
var
  contador, Contador2, _valor : integer;
  media, pi : real;
  letra, digito, quebraLinha, tabulacao : char;

begin
  // ---------- Identificadores ----------
  contador := 0;
  Contador2 := 1;      // "Contador2" != "contador" (case-sensitive)
  _valor := 10;

  // ---------- Literais inteiros e reais ----------
  contador := 123;
  media := 3.14;
  pi := 3.14159;

  // ---------- Literais char ----------
  letra := 'a';
  digito := '9';
  quebraLinha := '\n';
  tabulacao := '\t';

  // ---------- Operadores relacionais ----------
  if contador < 10 then write('a');
  if contador > 10 then write('a');
  if contador <= 10 then write('a');
  if contador >= 10 then write('a');
  if contador = 10 then write('a');
  if contador <> 10 then write('a');

  // ---------- Operadores lógico-aritméticos ----------
  contador := contador + 1;
  contador := contador - 1;
  contador := contador * 2;
  media := media / 2.0;
  contador := contador div 2;
  if (contador > 0) and (contador < 100) then write('a');
  if (contador > 0) or (contador < 0) then write('a');
  if not (contador = 0) then write('a');

  // ---------- Atribuição ----------
  contador := 42;

  // ---------- Símbolos especiais ----------
  write(contador);

  // ---------- Palavras reservadas em contexto de comando ----------
  while contador < 5 do
  begin
    contador := contador + 1;
  end;

  repeat
    contador := contador - 1;
  until contador = 0;

  if contador = 0 then
    write('z')
  else
    write('n');

  // ---------- Comentário sozinho, sem código na linha ----------
  // esta linha inteira e um comentario e deve ser ignorada

end.

// ===================================================================
// A partir daqui, casos PROPOSITAIS de erro léxico.
// Comente o bloco acima e descomente os testes abaixo, um de cada vez,
// para validar as mensagens de erro isoladamente.
// ===================================================================

// program TesteErro1;
// begin
//   contador := 10 @ 5;   // '@' nao pertence a nenhum token -> "Erro lexico no caracter @"
// end.

// program TesteErro2;
// begin
//   letra := '#';          // '#' nao e letra nem digito -> erro dentro do char literal
// end.

// program TesteErro3;
// begin
//   letra := 'ab';         // char literal com mais de 1 caractere -> falta a aspa de fechamento
// end.
