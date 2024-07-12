# Documentação do trabalho de LFA

## Leitura do Arquivo
1 - O Arquivo de entrada precisa conter primeiro os tokens seguido pelas gramaticas, sendo elas separadas por uma linha em branco (Necessariamente)

2 - Os tokens preferivelmente precisam estar com letras misculas

3 - Os estados da gramatica precisam preferivelmente estar com letras maiusculas, enquanto os simbolos de letras em minusculo

Ao final da leitura do arquivo, a saida irá retornar algo parecido com:
```ruby
  # Exemplo de entrada
  se
  nao
  sei
  foi

  S::=0A|1A
  A::=0A|1A|£
  S::=bS|xS|fS|b|x|f

  # Retorno com base na entrada
  {:tokens=>["se", "nao", "sei", "foi"], :grammars=>[["S::=0A|1A", "A::=0A|1A|£"], ["S::=bS|xS|fS|b|x|f"]]}
```
onde os tokens será um array de strings e as gramaticas uma matriz, separado em cada gramatica, para o funcionamento adequado da separação das gramaticas é necessario ter o simbolo S::= para a identificação de uma nova gramatica

# Passo a passo

```
Tokens
["se", "nao", "sei", "foi"]
{
  "se": [
    {"s": 0},
    {"e": 1},
  ],
  "nao": [
    {"n": 0},
    {"a": 2},
    {"o": 3},
  ],
  "sei": [
    {"s": 0},
    {"e": 4},
    {"i": 5},
  ],
  "foi": [
    {"f": 0},
    {"o": 6},
    {"i": 7},
  ],
}

Gramaticas
[["S::=0A|1A", "A::=0A|1A|£"], ["S::=bS|xS|fS|b|x|f"]]
{
  "[S::=0A|1A, A::=0A|1A|£]": [
    {"S": 0},
    {"A": 1}
  ],
  "S::=bS|xS|fS|b|x|f": [
    {"S": 0}
  ]
}
```

1 - Abrir o arquivo

2 - Ler as informações e salvar em uma estrutura para manipulação

3 - Manipular informações para gerar automato finito apartir dos
tokens

4 - Manipular informações para gerar automato finito apartir das gramaticas

5 - Imprimir automato finito não deterministico

6 - Criar regras para determinização

7 - Minimização do automato finito deterministico