#include <iostream>
#include "Huffman.hpp"

using namespace hf;

int main(int argc, char* argv[]){       //main apenas para teste
                                        //para compilar o código, faça o de sempre
    Huffman huff(argv[1], argv[2]);     //para rodar, use ./nomeEscolhido.out <arquivo_a_ser_lido> <qualquer_outro_arquivo_pois_fiquei_com_preguiça_de_tirar>

    huff.lerArquivoTabela();
    huff.montarArvore();
    huff.codificar();
    huff.printTabela();           // vai printar apenas cada caractere com sua frequência
    huff.compactar();
    return 0;
}