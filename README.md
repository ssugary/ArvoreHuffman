# Projeto de Simulação do Algoritmo de Huffman

<!--toc:start-->

- [1. Introdução](#1-introdução)
- [2. Funcionamento](#2-Inicialização-do-Programa)
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

|    Bibliotecas        |
|    ---------------    |
|    std::algorithm     |
|    std::cstddef       |
|    std::filesystem    |
|    std::fstream       |
|    std::iostream      |
|    std::list          |
|    std::map           |
|    std::queue         |
|    std::string        |
|    std::unordered_map |
|    std::vector        |

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

## 2. Inicialização do Programa

Antes de iniciar, aqui temos a lista de comandos:

    // comando exclusivo do Compressor. Utilize para comprimir um arquivo de texto.
    $ comprimir <Arquivo_A_Ser_Comprimido> <Tabela_Do_Arquivo_Comprimido> 

    // comando exclusivo do Compressor. Utilize para descomprimir um arquivo comprimido.
    $ descomprimir <Arquivo_Comprimido> <Tabela_de_Compressão>

> [!tip]
> A opção `-h imprime na saída padrão uma tela de ajuda


### 2.1 Compilar o código:

Para compilar o código, recomendamos utilizar o próprio g++, abaixo temos alguns exemplos:

    // Comando para compilar o Criador da tabela:

    $ c++ criartabela.cpp Tabela.cpp -o criartabela


    // Comando para compilar o Compressor/Descompressor:

    $ c++ compressor.cpp Huffman.cpp interface.cpp -o comprimir


### 2.2 Rodar o Criador da tabela:

Para rodar esse código, compile o criador de tabela (seguindo o passo 1), depois, utilize o seguinte comando:

    $ ./criarTabela <caminho_do_arquivo_a_ser_lido>

Após isso, o código irá gerar um arquivo "tabela.bin", onde ela terá o conteúdo comprimido do arquivo fornecido.

### 2.3 Rodar o Compressor:

Para rodar esse código, compile o compressor (seguindo o passo 1), depois, utilize o seguinte comando:

    $ ./comprimir comprimir <Arquivo_a_ser_comprimido> <Tabela_do_arquivo_comprimido>

Esse comando irá retornar uma lista de 3-uplas com o formato (caractere, frequência, códigoHuffman), além de gerar um
arquivo .bin com o arquivo comprimido.

### 2.4 Rodar o Descompressor:

Para rodar esse código, compile o compressor (seguindo o passo 1), depois, utilize o seguinte comando:

    $ ./comprimir descomprimir <Arquivo_comprimido> <Tabela_de_Compressão>

Esse comando irá descomprimir o arquivo de acordo com a tabela de compressão fornecida.


## 3. Explicação

Neste tópico iremos descrever cada arquivo, com a complexidade de cada uma das funções que os compõem.

### 3.1 ContadorDeFrequencia

Esse arquivo cria a nossa fila de prioridade, mas, separamos em uma classe separada por questão de boas práticas

Nela, apenas temos uma struct `CompararFrequencia` e uma fila de prioridade que irá comparar com base nessa struct.

#### 3.1.1 CompararFrequencia

Essa struct serve para falar o que devemos comparar dentro da fila de prioridade.

Nesse caso, iremos comparar as frequências.

### 3.2 No

Esse arquivo cria os nós da árvore binária que formará a Árvore de Huffman.

#### 3.2.1 Variaveis

Cada nó tem as seguintes variáveis:

| Variável       | Função                                 |
| -------------- | -------------------------------------- |
| caractere      | Palavra/Caractere do nó                |
| freq           | Frequência da palavra/caractere        |
| codigo         | Código binário da palavra/caractere    |
| filhoEsq       | Nó filho esquerdo do nó                |
| filhoDir       | Nó filho direito do nó                 |


#### 3.2.2 Construtores/Destrutores

Também temos os construtores e destrutores, onde todos tem complexidade 0(1).

A seguir temos o uso de cada construtor:

| Construtor     | Função                                 |
| -------------- | -------------------------------------- |
| (codigo, freq) | Criar uma folha do zero                |
| (no*)          | Copiar um nó sem alterar o original    |
| (no1* no2*)    | Criar um nó novo com os dois filhos    |

### 3.3 Interface

Esse arquivo tem o objetivo de servir como uma interface visual para o programa de compressão/descompressão.

#### 3.3.1 Variáveis

Temos as seguintes variáveis:    

| Variável       | Função                                                                |
| -------------- | --------------------------------------------------------------------- |
| map            | mapa do tipo String x Boolean que mapeia uma palavra com um estado    |
| entrada1       | String que guarda o nome da primeira entrada                          |
| entrada2       | String que guarda o nome da segunda entrada                           |
| ajuda          | Booleano que diz se o programa deve imprimir a tela de ajuda          |

#### 3.3.2 Funções

Temos os seguintes métodos com suas respectivas complexidades:

| Método            | Função                                              | Complexidade |
| ----------------- | --------------------------------------------------- | ------------ |
| Construtor        | Inicializador padrão                                | Θ(1)         |
| textoDeAjuda      | Imprime a mensagem de ajuda                         | Θ(1)         |
| verify            | Verifica se as entradas são válidas                 | O(n * l) Ω(n)|
| iniciar           | Retorna se o programa vai comprimir ou descomprimir | Θ(1)         |
| verificarArquivos | Verifica se os arquivos são válidos                 | Θ(1)         |
| getters           | Retorna o nome de cada entrada                      | Θ(1)         |


Onde `n` é a quantidade de argumentos na entrada e `l` é o tamanho médio das strings.

#### 3.3.3 Explicações das Complexidades

O motivo da maioria ter complexidade Θ(1) é trivial (já que temos quantidades limitadas de iterações).

Na função `Verify`, note que temos um loop `for`, onde cada iteração faz copias de strings com custo médio de Θ(l),
como o loop faz `argc` iterações (chamaremos de `n`), então a complexidade terá O(n * l).

Considerando que o melhor caso ocorre quando as entradas tem tamanho 1, então o melhor caso teria Ω(n).

### 3.4 Tabela

O arquivo implementa o algoritmo de criação da tabela de Huffman.

#### 3.4.1 Constantes

Definimos 3 constantes para facilitar a criação de nós, sendo elas:

| Constantes                | Função                                              | 
| ------------------------- | --------------------------------------------------- |
| NUM_PALAVRAS_CHAVE        | Quantidade de palavras-chave definidas              |
| NUM_CARACTERES_ASCII      | Quantidade de caracteres em ASCII                   |
| PALAVRAS_CHAVE_CPP        | Array de strings que guardam todas as palavras-chave| 

#### 3.4.2 Variáveis

Definimos as seguintes variáveis:

| Variáveis            | Função                                                          | 
| -------------------- | --------------------------------------------------------------- |
| nomeDaEntrada        | String que guarda o nome do arquivo que gerará a tabela         |
| elementos            | Array que guarda todos os elementos que aparecem no arquivo     |

Também temos a struct `elem`, onde ela guarda as informações de cada elemento (caractere/palavra e frequência).

#### 3.4.3 Métodos


| Método                  | Função                                                                      | Complexidade   |
| ----------------------- | --------------------------------------------------------------------------- | -------------- |
| Construtor              | Inicializa o nome da entrada e chama os métodos de preenchimento            | Θ(1)           |
| Destrutor               | Libera a memória alocada para todos os elementos                            | Θ(1)           |
| encherArrayDeCaracteres | Preenche o vetor de elementos com todos os caracteres ASCII                 | Θ(1)           |
| encherArrayDePalavras   | Preenche o vetor de elementos com todas as palavras-chave                   | Θ(1)           |
| montarTabela            | Lê o arquivo e contabiliza as frequências de cada caractere e palavra-chave | O(l * m * n)   |
| printTabela             | Imprime todos os elementos com frequência > 0                               | Θ(1)           |
| atualizar               | Substitui parte de uma string por ‘x’                                       | Θ(1)           |
| cacarMapaSubstrings     | Procura substrings (palavras-chave) dentro de uma string                    | O(m)           |
| pertenceNaSubstring     | Verifica se uma posição pertence a uma substring no mapa                    | Θ(1)           |
| numbin                  | Converte um número inteiro em uma lista binária                             | Θ(log a)       |
| criarArquivoTabelaBin   | Gera o arquivo binário de tabela de frequências                             | Θ(log f)       |
| ImprimirArquivoBin      | Lê e imprime o conteúdo binário do arquivo                                  | Θ(b)           |

Onde:
    n = Tamanho médio de cada linha
    m = Tamanho médio de cada palavra-chave
    l = Número de linhas do arquivo
    b = Tamanho do arquivo binário em bits
    a = Valor do número passado

#### 3.4.4 Explicação da Complexidade

A maioria dos métodos possui complexidade Θ(1), pois realizam apenas operações simples, como inicializações, atribuições, liberações de memória ou percursos sobre estruturas de tamanho fixo (como o conjunto de caracteres ASCII e as palavras-chave definidas).

As funções numbin e criarArquivoTabelaBin apresentam complexidade Θ(log n), já que estão sempre dividindo as iterações na metade.

Os métodos pertenceNaSubstring e atualizar também são Θ(1), pois executam apenas verificações ou substituições diretas.

O método montarTabela apresenta O(l × m × n), pois para cada uma das l linhas do arquivo é necessário percorrer n caracteres e verificar a ocorrência de até m palavras-chave.

O método cacarMapaSubstrings tem complexidade O(m), refletindo a busca de todas as palavras-chave dentro de uma única string.

O método ImprimirArquivoBin apresenta complexidade Θ(b), sendo diretamente proporcional ao número total de bits presentes no arquivo binário lido.

### 3.5 Huffman

#### 3.5.1 Constantes
#### 3.5.2 Variaveis
#### 3.5.3 Metodos

| Método                  | Função                                                                   | Complexidade          |
| ----------------------- | ------------------------------------------------------------------------ | --------------------- |
| Construtor              | Inicializa o objeto Huffman, preenchendo arrays de caracteres e palavras | Θ(1)                  |
| Destrutor               | Libera memória alocada para os nós                                       | Θ(1)                  |
| encherArrayDeCaracteres | Cria os nós para os 256 caracteres ASCII                                 | Θ(1)                  |
| encherArrayDePalavras   | Cria os nós para as palavras-chave                                       | Θ(1)                  |
| cacarMapaSubstrings     | Localiza palavras-chave dentro de uma string                             | O(n * m) Ω(n)         |
| pertenceNaSubstring     | Verifica se uma posição pertence a uma substring mapeada                 | Θ(1)                  |
| lerArquivoTabelaBin     | Lê o arquivo binário da tabela de frequências                            | Θ(n)                  |
| montarArvore            | Constrói a árvore de Huffman com base nas frequências                    | Θ(n log n)            |
| mostrarArvore           | Percorre a árvore recursivamente e imprime                               | Θ(n)                  |
| printTabela             | Imprime os códigos binários de cada caractere                            | Θ(1)                  |
| fazerCodigo             | Gera os códigos binários recursivamente                                  | Θ(n * v)              |
| codificar               | Chama `fazerCodigo` para toda a árvore                                   | Θ(n * v)              |
| compactar               | Compacta o arquivo texto em binário usando a árvore                      | O(n · m) Ω(n)         |
| verExtensao             | Lê a extensão original do arquivo compactado                             | Θ(1)                  |
| descompactar            | Recria o arquivo original a partir do binário                            | Θ(n)                  |

Onde:

    n = tamanho do texto de entrada
    m = tamanho médio das palavras-chave
    v = tamanho médio dos códigos



#### 3.5.4 Explicação da Complexidade
A maioria dos métodos da classe apresenta complexidade Θ(1), incluindo o construtor, destrutor, e os métodos de inicialização dos vetores e leitura de extensão. Essas funções realizam apenas operações diretas e de tamanho fixo, como a criação de nós, leitura de pequenos trechos de dados e acesso via mapas.

Os métodos `lerArquivoTabelaBin`, `mostrarArvore` e `descompactar` possuem complexidade Θ(n), pois percorrem sequencialmente todos os nós da árvore ou todos os bits de um arquivo, executando uma operação constante para cada elemento lido.

A construção da árvore de Huffman (montarArvore) apresenta complexidade Θ(n log n), refletindo o uso de uma fila de prioridade (priority_queue) para combinar os nós em ordem crescente de frequência.

As funções fazerCodigo e codificar possuem complexidade Θ(n · v), onde v representa a profundidade média da árvore. Isso ocorre porque cada nó precisa ser visitado e ter seu código binário gerado com base na travessia até a raiz.

Os métodos cacarMapaSubstrings e compactar exibem comportamento O(n · m) no pior caso, já que para cada caractere (n) pode ser necessário comparar até m palavras-chave. No melhor caso, quando as buscas terminam rapidamente, a complexidade é Ω(n).


### 3.6 Criartabela
#### 3.6.1 Explicação da Complexidade

Como para criar a tabela utilizamos as funções `montarTabela`, `criarArquivoTabelaBin` e `printTabela`, então a complexidade será apenas a soma delas, ou seja, O(l * n * m + log(f) + 1), ou, aproximadamente, Θ(l * n * m).

### 3.7 Compactar
#### 3.7.1 Explicação da Complexidade da compressão
Como para comprimir utilizamos as funções `lerArquivoTabelaBin()`, `montarArvore()`, `printTabela`,`codificar` e `compactar` então a complexidade será apenas a soma delas, ou seja, O(n + n log n + 1 + n * v + n * m ), ou, aproximadamente, O(n * (log n + v + m)).

#### 3.7.2 Explicação da Complexidade da descompressão
Como para descomprimir utilizamos as funções `lerArquivoTabelaBin()`, `montarArvore()` e `descompactar`, então a complexidade será apenas a soma delas, ou seja, O(n + n log n + n), ou, aproximadamente O(n log n).

### 3.8 Comparando com outros compactadores
#### Nosso Compactador
| Arquivo                     | Tamanho Original| Tamanho Comprimido |Taxa de Compressão |
| --------------------------- | --------------- |--------------------|-------------------|
| Huffman.cpp                 |      12,20 kb   |       7,00 kb      |      0.57         |
| Tabela.cpp                  |      6,40  kb   |       4,10 kb      |      0.64         |
| Interface.cpp               |      1,60  kb   |       1,03 kb      |      0.64         |
| TextoDeAjuda.txt            |      2,30  kb   |       1,49 kb      |      0.64         |

#### Formato .zip
| Arquivo                     | Tamanho Original| Tamanho Comprimido |Taxa de Compressão |
| --------------------------- | --------------- |--------------------|-------------------|
| Huffman.cpp                 |      12,20 kb   |       3,50 kb      |      0.28         |
| Tabela.cpp                  |      6,40  kb   |       2,10 kb      |      0.32         |
| Interface.cpp               |      1,60  kb   |       0.74 kb      |      0.46         |
| TextoDeAjuda.txt            |      2,30  kb   |       1,10 kb      |      0.47         |

#### Formato .7zip
| Arquivo                     | Tamanho Original| Tamanho Comprimido |Taxa de Compressão |
| --------------------------- | --------------- |--------------------|-------------------|
| Huffman.cpp                 |      12,20 kb   |       3,30 kb      |      0.27         |
| Tabela.cpp                  |      6,40  kb   |       2,00 kb      |      0.31         |
| Interface.cpp               |      1,60  kb   |       0,79 kb      |      0.49         |
| TextoDeAjuda.txt            |      2,30  kb   |       1,10 kb      |      0.47         |
