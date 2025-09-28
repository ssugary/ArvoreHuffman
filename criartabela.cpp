#include <iostream>
#include "Huffman.hpp"

using namespace hf;

int main(int argc, char* argv[]){       //main apenas para teste
                                        //para compilar o código, faça o de sempre
    Huffman huff(argv[1]);     //para rodar, use ./nomeEscolhido.out <arquivo_a_ser_lido> 

    huff.montarTabela();
    huff.criarArquivoTabela();
    return 0;
}