# Projeto Password Generator

<!--toc:start-->

- [1. Introdução](#1-introdução)
- [2. Funcionamento](#2-funcionamento)
  - [2.1 Considerações sobre o tamanho da senha](#21-considerações-sobre-o-tamanho-da-senha)
  - [2.2 Considerações sobre a escolha de vários caracteres de um mesmo grupo](#22-considerações-sobre-a-escolha-de-vários-caracteres-de-um-mesmo-grupo)
- [3. Entrada e Interface](#3-entrada-e-interface)
  - [3.1 Qualidade da senha](#31-qualidade-da-senha)
  - [3.2 Tratamento de erros](#32-tratamento-de-erros)
- [4. Modelagem do problema](#4-modelagem-do-problema)  
<!--toc:end-->

## 1. Introdução

Neste projeto de programação, desenvolvemos dois programas que simulam o algoritmo de Huffman, onde cada programa atua como um contador de frequência e como compressor/descompressor.

O programa oferece uma interface no estilo CLI (Command Line Interface), e foi desenvolvido em C++17.

Utilizamos as seguintes bibliotecas padrão da linguagem:

    std::algorithm
    std::cstddef
    std::filesystem
    std::fstream
    std::iostream
    std::list
    std::map
    std::queue
    std::string
    std::unordered_map
    std::vector

O nosso projeto tem como diferenciais as seguintes funções:

    leitura de palavras-chave de linguagens como caracteres
    criação da tabela de frequências como um arquivo binário


Também separamos nossos programas nas seguintes partes:
| Arquivos                 | Função                                                                              |
| ------------------------ | ----------------------------------------------------------------------------------- |
| criartabela.cpp          | Arquivo principal que cria a tabela de frequência.                                  |
| compactar.cpp            | Arquivo principal que comprime e descomprime arquivos compactados.                  |
| Huffman.cpp e .hpp       | Arquivo que implementa a lógica de compressão e descompressão.                      |
| Tabela.cpp e .hpp        | Arquivo que implementa a lógica da criação da tabela de frequência.                 |
| Interface.cpp e .hpp     | Arquivo que analisa e trata erros de entrada.                                       |
| No.hpp                   | Arquivo que implementa cada nó da árvore.                                           |
| ContadorDeFrequencia.hpp | Arquivo de classe que cria uma fila de prioridade baseada na frequência de cada nó  |
| TextoDeAjuda.txt         | Arquivo que mostra instruções de como cada programa funciona.                       |

## 2. Funcionamento

O programa `passgen` recebe como entrada do usuário o tamanho da senha desejada junto com uma indicação de quais
**grupos** de caracteres o gerador deve escolher.
O gerador escolhe, pelo menos, um caractere de forma aleatória de cada grupo indicado.

Os grupos de caracteres são os seguintes:

| Grupo                       | Elementos       |
| --------------------------- | --------------- |
| letras minúsculas (_lower_) | a-z             |
| letras maiúsculas (_upper_) | A-Z             |
| dígitos (_digits_)          | 0-9             |
| _logograms_                 | # $ % & @ ^ ` ~ |
| pontuação (_punctuation_)   | . , ; :         |
| aspas (_quotes_)            | " '             |
| barras (_slashes_)          | \ / \| \_ -     |
| matemáticos (_math_)        | < > \* + ! ? =  |
| parênteses (_braces_)       | } { ] [ ) (     |

### 2.1 Considerações sobre o tamanho da senha

O tamanho _default_ de uma senha é 7, caso o usuário não indique um tamanho manualmente.

O programa deve procurar escolher, pelo menos, um caractere de cada grupo indicado.
Em outras palavras, todos os grupos indicados pelo usuário **devem** contribuir com algum caractere para a senha final.

Se o tamanho da senha solicitado for **maior** do que a quantidade de grupos indicados, o gerador deve escolher mais de
um caractere por grupo.
Por outro lado, se o tamanho da senha solicitado for **menor** do que a quantidade de grupos indicada, o tamanho da senha
deverá ser alterado de maneira a escolher pelo menos um caractere de cada grupo.

### 2.2 Considerações sobre a escolha de vários caracteres de um mesmo grupo

Suponha que o programa precisa selecionar `n` caracteres de um grupo com, digamos, tamanho `m`, com `m>n`.
Seu programa **deve** garantir que os `n` caracteres escolhidos sejam distintos.

Por exemplo, se `n=3` e o grupo escolhido fosse o de "_parênteses_" (`--braces`), com tamanho `m=6`;
uma seleção aceitável de caracteres deste grupo seria `{ [ ]`, enquanto que `{ { )` não seria aceitável visto que `{` aparece 2 vezes neste subconjunto.

Por outro lado, se `n>m` é natural que ocorra repetições na seleção de caracteres deste grupo.
Mas mesmo neste caso, procure reduzir ao máximo a quantidade de repetições.
Considerando o exemplo anterior com `n=9`, um exemplo aceitável seria `) { ] ( [ { ( } [`, enquanto que `{ ) { { { { ] ) )` seria inaceitável, visto que o `{` é repetido múltiplas vezes (desnecessariamente).

## 3. Entrada e Interface

A seguir temos alguns exemplos de execução do `passgen` com algumas opções.

```
$ ./passgen --len 10 --lower --upper
Welcome to passgen v 1.0, © DIMAp 2025

>>> The generated password is:
LbgvcaQTPE
```

A execução acima gera uma senha de 10 caracteres, utilizando apenas letras minúsculas e maiúsculas.

```
$ ./passgen --len 20 --lower --upper --digits --logograms --punctuation --quotes --slashes --math --braces
Welcome to passgen v 1.0, © DIMAp 2025

>>> The generated password is:
\sv"!>`.C{0[1':(/L@?
```

A execução acima gera uma senha de 20 caracteres, misturando vários grupos de caracteres disponíveis.

```
$ ./passgen --len 15 --all-groups -t
Welcome to passgen v 1.0, © DIMAp 2025

>>> The generated password is:
?@.l&,|U/{+{"3'

>>> Password strength: Excellent
```

A execução anterior gera uma senha de 15 caracteres com todos os grupos presentes e exibe a qualidade da senha.

> [!tip]
> A opção `-s` imprime na saída padrão uma classificação da qualidade da senha.

```
$ ./passgen -h
Welcome to passgen v 1.0, © DIMAp 2025

This program generates passwords of specific length
based on the selection of groups of characters.

Usage: passgen [<options>]
  --len n        Size of the password (default is 7).
  -l, --lower        Add letter in [a-z].
  -u, --upper        Add letter in [A-Z].
  -d, --digits       Add letter in [0-9].
  -o, --logograms    Add letter in [#$%&@^`~].
  -p, --punctuation  Add letter in [.,;:].
  -q, --quotes       Add letter in ["'].
  -s, --slashes      Add letter in [\/|_-].
  -m, --math         Add letter in [*+!?=].
  -b, --braces       Add letter in [{}[]()].
  -a, --all-groups   Add letter from all the above groups.
  -t, --strength     Show password strength classification.
  -h, --help         Show this help screen.
```

Na execução acima o programa exibe a tela de ajuda, que também pode ser gerada com a opção `--help`

> [!important]
> Se o usuário não fornecer um grupo de caracteres o programa deve selecionar caracteres do grupo de letras minúsculas apenas.

### 3.1 Qualidade da senha

Você deve desenvolver uma forma própria de avaliar a qualidade da senha gerada, classificando-a
em pelo menos 5 categorias.
Segue abaixo uma possível sugestão de como classificar a senha:

- _Very Weak_: senhas extremamente fáceis, geralmente com 1 à 3 caracteres de comprimento.
- _Weak_: senhas fáceis, com poucos caracteres (até 5), uso de apenas 1 grupo, uso de palavras do dicionário ou sequências bem conhecidas, etc.
- _Medium_: senhas razoáveis, 5 ou mais caracteres com mais de 2-3 grupos selecionados; algumas repetições.
- _Strong_: senhas fortes, 10 ou mais caracteres, sem repetição, 4 ou mais grupos selecionados.
- _Very Strong_: senhas muito fortes, 15 ou mais caracteres, sem repetição, 6 ou mais grupos selecionados.
- _Excellent_: senhas extremamente fortes, 25 ou mais caracteres, com poucas repetições, todos os grupos ativos.

Cada dupla está livre para modificar esta classificação da forma que achar mais adequado, desde que seja um critério razoável.

> [!tip]
> Faça uma investigação sobre o assunto para saber como classificar a qualidade de uma senha. Em particular, investigue a definição do conceito de **entropia** em senhas.

### 3.2 Tratamento de erros

Seu programa deve tratar erros de entrada do usuário, indicando uma mensagem indicativa do problema, seguido da tela de ajuda padrão.

São exemplos (não exaustivos) de erros de entrada:

- Usar uma opção inválida.
- Usar a opção `--len` mas esquecer de indicar um inteiro (argumento da opção).
- Indicar um comprimento inválido, como por exemplo zero ou um número negativo.
- Indicar quando o usuário usou o `-` mas não incluiu a letra correta.

> [!important]
> Seu programa deve receber os argumentos em qualquer ordem.

## 4. Modelagem do problema

Seguem algumas dicas e sugestões de modelagem do problema, bem como algumas boas práticas de programação.

1. Crie um `struct` chamado de `RunningOptions` onde você deve salvar o resultado do processamento do [**argumentos de linha de comando**](https://www.learncpp.com/cpp-tutorial/command-line-arguments/) fornecidos ao programa.
2. Implemente um conjunto de funções ou uma classe que simule o comportamento de um [dado aleatório de `n` faces](https://www.dados-online.pt/).
   Tal componente pode ser muito útil, visto que selecionar elementos de um conjunto de caracteres pode ser interpretado como a rolagem de um dado aleatório com `n` faces, onde `n` é o número de componentes do conjunto.
3. Ao coletar os caracteres de cada grupo, guarde-os em uma _string_ do tamanho da senha e, por fim, aplique a operação
   _shuffle_ (embaralhamento) para garantir que os caracteres vindo de cada grupo serão misturados dentro da senha.
4. Procure criar funções pequenas e simples, que desempenham apenas uma única tarefa.
5. Use enumeração para representar os 9 grupos de caracteres. Isso torna seu código mais legível.
6. A utilização da estrutura de dados **dicionário** (ex. _hash table_ ou _map_) pode facilitar alguns aspectos da implementação.
7. Procure utilizar as funções da biblioteca [`<algoritm>`](https://en.cppreference.com/w/cpp/algorithm) do C++ sempre que possível.

## 5. Avaliação

Seu programa deve ser escrito em um bom estilo de programação.
Isto inclui (mas não fica limitado a) o uso de nomes significativos
para identificadores e funções, um cabeçalho de comentário no início
de cada arquivo, cabeçalho no formato Doxygen para cada função/método criado,
uso apropriado de linhas em branco e identação para ajudar na visualização
do código, comentários significativos nas linhas de código, etc.

<!-- Para a implementação deste projeto **é obrigatório** a utilização de pelo menos uma classe. -->

O programa completo deverá ser entregue sem erros de compilação, testado e totalmente
documentado.
O projeto é composto de **90 pontos** e será avaliado sob os seguintes critérios:-

| Item                                             | Pontos |
| ------------------------------------------------ | :----: |
| Interface de acordo com o especificado           |   20   |
| Seleciona caracteres dos grupos adequadamente    |   15   |
| Apresenta a tela de ajuda quando solicitado      |   5    |
| Trata os erros de entrada corretamente           |   12   |
| Avalia a qualidade da senha com 5 categorias     |   10   |
| Implementa os 9 grupos de caracteres solicitados |   18   |
| Utiliza corretamente a aleatoriedade             |   10   |

A pontuação acima não é definitiva e imutável.
Ela serve apenas como um guia de como o trabalho será avaliado em linhas gerais.
É possível a realização de ajustes nas pontuações indicadas visando adequar a pontuação
ao nível de dificuldade dos itens solicitados.

Os itens abaixo correspondem à descontos, ou seja, pontos que podem ser retirados
da pontuação total obtida com os itens anteriores:-

| Item                                                             | Value (points) |
| ---------------------------------------------------------------- | :------------: |
| Presença de erros de compilação                                  |    até -10     |
| Falta de documentação das funções e/ou classes no estilo Doxygen |    até -10     |
| Vazamento de memória                                             |      -10       |
| Não preencher o arquivo [`author.md`](./author.md)               |      -10       |
| O programa quebra ou falha durante a execução                    |       -5       |

O arquivo [`author.md`](docs/author.md) deve conter uma breve descrição do projeto e como compilar o projeto.
Também deve descrever eventuais limitações do projeto e dificuldades de aprendizagem enfrentadas.
Não esqueça de incluir os nomes dos componentes da dupla!

### 5.1 Extras

Os programas que **estiverem funcionando corretamente e completamente**, podem tentar obter ponto extra
implementando alguns dos elementos adicionais sugeridos a seguir:

1. Calcular a entropia das senhas geradas.
2. Usar uma biblioteca externa para calcular qualidade da senha.
3. Salvar em um arquivo criptografado informações como _local_ + _usuário_ + _senha_. Claro, é necessário pensar em uma maneira de recuperar as informações salvas.
4. Utilizar classes na modelagem do seu programa.
5. Criar um arquivo de configuração externa no formato [.ini](https://en.wikipedia.org/wiki/INI_file), de maneira a facilitar a configuração do gerador de senhas de forma persistente entre execuções.

Se você tiver alguma outra ideia interessante de extensão do projeto, compartilhe no servidor Discord.

## 6. Boas práticas de programação

Recomenda-se fortemente o uso das seguintes ferramentas:-

- Doxygen: para a documentação de código e das classes;
- Git: para o controle de versões e desenvolvimento colaborativo;
- Valgrind: para verificação de vazamento de memória;
- gdb: para depuração do código; e
- CMake/Makefile: para gerenciar o processo de compilação do projeto.

## 7. Autoria e Política de Colaboração

O trabalho pode ser realizado **individualmente** ou em **dupla**,
sendo que no último caso é importante, dentro do possível,
dividir as tarefas igualmente entre os componentes.
A divisão de tarefas deve ficar evidente através do histórico de _commit_ do
repositório git correspondente.

Após a entrega, qualquer equipe pode ser convocada para uma entrevista.
O objetivo da entrevista é duplo: confirmar a autoria do trabalho e
determinar a contribuição real de cada componente em relação ao trabalho.
Durante a entrevista os membros da equipe devem ser capazes de explicar,
com desenvoltura, qualquer trecho do trabalho, mesmo que o código tenha
sido desenvolvido pelo outro membro da equipe.
Portanto, é possível que, após a entrevista, ocorra redução da nota geral do trabalho ou
ajustes nas notas individuais, de maneira a refletir a verdadeira contribuição
de cada membro, conforme determinado na entrevista.

O trabalho em cooperação entre alunos da turma é estimulado.
É aceitável a discussão de ideias e estratégias.
Note, contudo, que esta interação **não** deve ser entendida como permissão
para utilização de código ou parte de código de outras equipes,
o que pode caracterizar a situação de plágio.
Em resumo, tenha o cuidado de escrever seus próprios programas.

Trabalhos plagiados ou realizados com IA generativa (ou qualquer variação) receberão nota **zero** automaticamente,
independente de quem seja o verdadeiro autor dos trabalhos infratores.
Fazer uso de qualquer assistência sem reconhecer os créditos apropriados
é considerado **plágio**.
Quando submeter seu trabalho, forneça a citação e reconhecimentos necessários.
Isso pode ser feito pontualmente nos comentários no início do código, ou,
de maneira mais abrangente, no arquivo texto `autor.md`.
Além disso, no caso de receber assistência, certifique-se de que ela lhe
é dada de maneira genérica, ou seja, de forma que não envolva alguém ou um serviço
tendo que escrever código por você.

## 8. Entrega

Você deve submeter seu trabalho de duas formas:
via GitHub Classroom (GHC) e via tarefa do SIGAA.

No SIGAA inclua apenas o link para o repositório no GHC.
No GHC você deve _subir_ seu projeto até antes do prazo final da tarefa.

Caso você opte por não usar o GHC por algum motivo, envie pelo SIGAA
um arquivo compactado com todo código fonte completo do seu projeto.

Em qualquer uma das duas opções descritas, lembre-se de remover todos
os arquivo executáveis do seu projeto (a pasta `build`) antes
de submeter seu trabalho.

> [!important]
> No caso de trabalhos implementados em duplas **os dois componente** devem
> submeter o trabalho via SIGAA. O aluno que não enviar o trabalho pelo
> SIGAA ficará sem nota!