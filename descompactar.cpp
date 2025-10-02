#include <iostream>
#include "Huffman.hpp"

using namespace hf;

int main(int argc, char* argv[]) {

    Huffman huff(argv[1], argv[2]);

    huff.lerArquivoTabela();
    huff.montarArvore();
    huff.descompactar();
    
    return 0;
}
