# Projeto de Compiladores 2024/2025

### Compilador para a linguagem deiGo

### 7 de outubro de 2024

Este projeto consiste no desenvolvimento de um compilador para a linguagemdeiGo, que é um subconjunto da linguagem Go (https:/ golang.org/ref/spec) de acordo com a especificação de maio de 2018 disponibilizada no material de apoio.

Na linguagem deiGo é possível usar variáveis e literais dos tipos string, bool, int e float32 (estes dois últimos com sinal). A linguagem deiGo inclui expressões aritméticas e lógicas, instruções de atribuição, operadores relacionais, e instruções de controlo (if-else e for). Inclui também funções com os tipos de dados já referidos e ainda o tipo especial []string, sendo a
passagem de parâmetros sempre feita por valor. 

A função main() invocada no início de cada programa é declarada na package main e não recebe argumentos nem retorna qualquer valor. O programa 

```
package main; 

func main() {};

```
é dos mais pequenos possíveis na linguagem deiGo. Os programas podem ler e escrever carateres na consola com as funções pré-definidas strconv.Atoi(os.Args[...]) e fmt.Println(...), respetivamente. 

O significado de um programa na linguagemdeiGoserá o mesmo que na linguagem Go, assumindo a pré-definição das funçõesstrconv.Atoi(...) e fmt.Println(...), bem como da variável os.Args[...]. Por fim, são aceites comentários nas formas/* ... */e// ... que deverão ser ignorados. Assim, por exemplo, o programa que se segue calcula o fatorial de um número passado como argumento:

```
package main;
```
```
func factorial(n int) int {
if n == 0 {
return 1;
};
return n * factorial(n-1);
};
```
```
func main() {
var argument int;
argument ,_ = strconv.Atoi(os.Args [1]);
fmt.Println(factorial(argument ));
};
```
Este programa declara uma variável argumentdo tipointe atribui-lhe o valor inteiro do argumento passado ao programa, usando a função Atoi para realizar a conversão (esta função retorna um par de valores e o segundo valor é descartado). De seguida, calcula o fatorial desse valor e invoca a função Println para escrever o resultado na consola.


## 1 Analisador lexical – Meta 1

Nesta primeira meta deve ser programado um analisador lexical para a linguagem deiGo. A programação deve ser feita em linguagem C utilizando a ferramenta _lex_. Os “tokens” a ser considerados pelo compilador são apresentados de seguida e deverão estar de acordo com a especificação da linguagem Go, disponível em https://golang.org/ref/spec#Lexical_elements e
no material de apoio da disciplina.

### 1.1 Tokens da linguagem deiGo

IDENTIFIER: sequências alfanuméricas começadas por uma letra, onde o símbolo “_” conta como uma letra. Letras maiúsculas e minúsculas são consideradas letras diferentes.

STRLIT: uma sequência de carateres (excepto “carriage return”, “newline”, ou aspas duplas) e/ou “sequências de escape” entre aspas duplas. Apenas as sequências de escape \f, \n, \r, \t, \\ e \" são especificadas pela linguagem. Sequências de escape não especificadas devem dar origem a erros lexicais, como se detalha mais adiante.

NATURAL: uma sequência de dígitos que representa uma constante inteira. Existe a opção de adicionar um prefixo para especificar outra base que não a decimal: 0 para octal, 0x ou 0X para hexadecimal. Nesta última, as letras (a-f) e (A-F) correspondem aos valores entre 10 e 15.

DECIMAL: uma parte inteira seguida de um ponto, opcionalmente seguido de uma parte fracionária e/ou de um expoente; ou um ponto seguido de uma parte fracionária, opcionalmente seguida de um expoente; ou uma parte inteira seguida de um expoente. O expoente consiste numa das letras “e” ou “E” seguida de um número opcionalmente precedido de um dos sinais “+” ou “-”. Tanto a parte inteira como a parte fracionária e o número do expoente consistem em sequências de dígitos decimais.

#### SEMICOLON = “;”
#### COMMA = “,”
#### BLANKID = “_”
#### ASSIGN = “=”
#### STAR = “*”
#### DIV = “/”
#### MINUS = “-”
#### PLUS = “+
#### EQ = “==”
#### GE = “>=”
#### GT = “>”
#### LBRACE = “{”
#### LE = “<=”
#### LPAR = “(”
#### LSQ = “[”
#### LT = “<”
#### MOD = “%”
#### NE = “!=”
#### NOT = “!”
#### AND = “&&”
#### OR = “||”
#### RBRACE = “}”
#### RPAR = “)”
#### RSQ = “]”
#### PACKAGE = “package”
#### RETURN = “return”
#### ELSE = “else”
#### FOR = “for”
#### IF = “if”
#### VAR = “var”
#### INT = “int”
#### FLOAT32 = “float32”
#### BOOL = “bool”
#### STRING = “string”
#### PRINT = “fmt.Println”
#### PARSEINT = “strconv.Atoi”
#### FUNC = “func”
#### CMDARGS = “os.Args”

RESERVED: todas as palavras reservadas da linguagem Go não utilizadas emdeiGobem como o operador de incremento (“++”) e o operador de decremento (“−−”).

O analisador deve aceitar (e ignorar) como separador de tokens o espaço em branco (espaços, tabs e mudanças de linha), bem como comentários dos tipos// ...e/* ... */. Deve ainda detetar a existência de quaisquer erros lexicais no ficheiro de entrada, tal como se especifica mais adiante.

### 1.2 Programação do analisador

O analisador deverá chamar-segocompiler, ler o ficheiro a processar através do _stdin_ e, quando invocado com a opção-l, deve emitir os tokens e as mensagens de erro para o _stdout_ e termi- nar. Na ausência de qualquer opção, deve escrever no _stdout_ apenas as mensagens de erro. Por exemplo, caso o ficheirofactorial.dgocontenha o programa de exemplo dado anteriormente, que calcula o fatorial de números, a invocação:

```
./gocompiler -l < factorial.dgo
```
deverá imprimir a correspondente sequência de tokens no ecrã. Neste caso:

```
PACKAGE
IDENTIFIER(main)
SEMICOLON
FUNC
IDENTIFIER(factorial)
LPAR
IDENTIFIER(n)
INT
RPAR
INT
LBRACE
...
```
O output completo está disponível em: https://git.dei.uc.pt/rbarbosa/Comp/blob/master/go/meta1/factorial.out

Sempre que uma categoria lexical contenha mais do que um único símbolo, o token encontrado deve ser impresso entre parêntesis logo a seguir à categoria do token, tal como exemplificado na Figura para IDENTIFIER. Por outras palavras, as categorias IDENTIFIER, STRLIT, NATURAL, DECIMAL e RESERVED requerem que o valor encontrado seja impresso a seguir ao nome da categoria lexical.

Em deiGo, o “;” é utilizado como terminador em muitas situações. No entanto, a linguagem permite que grande parte destes “;” sejam omitidos. Para isso, quando o programa está a ser analisado lexicalmente é emitido, de forma automática, um token SEMICOLON sempre que o último token de uma linha seja:

- um literal NATURAL, DECIMAL ou STRLIT
- um IDENTIFIER
- o símbolo RETURN
- ou um dos operadores de pontuação RPAR, RSQ ou RBRACE

### 1.3 Tratamento de erros

Caso o ficheiro contenha erros lexicais, o programa deverá imprimir exatamente uma das se- guintes mensagens no _stdout_ , consoante o caso:

```
Line <num linha>, column <num coluna>: illegal character (<c>)\n
Line <num linha>, column <num coluna>: invalid octal constant (<c>)\n
Line <num linha>, column <num coluna>: unterminated comment\n
Line <num linha>, column <num coluna>: unterminated string literal\n
Line <num linha>, column <num coluna>: invalid escape sequence (<c>)\n
```

onde "<num linha>" e "<num coluna>" devem ser substituídos pelos valores correspondentes ao _início_ do token que originou o erro, e "<c>" deve ser substituído por esse token. O analisador deve recuperar da ocorrência de erros lexicais a partir do _fim_ desse token. Tanto as linhas como as colunas são numeradas a partir de 1.