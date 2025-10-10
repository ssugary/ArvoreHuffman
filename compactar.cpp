#include <iostream>
#include "Huffman.hpp"
#include "interface.hpp"

using namespace hf;
using namespace itf;

int main(int argc, char* argv[]){

    interface inter = interface();
    if(!inter.verify(argc, argv)){
        if(inter.ajuda){
            inter.textoDeAjuda();
            return 0;
        }
        std::cerr << "Erro na verificação dos argumentos. Use \"-h\" para receber ajuda!" << std::endl;
        return 0;
    }

    Huffman huff(inter.getEntrada1(), inter.getEntrada2());

    switch(inter.iniciar()){
        case 0:
            inter.textoDeAjuda();
        break;
        case 1:
            //huff.lerArquivoTabela();
            huff.lerArquivoTabelaBin();
            huff.montarArvore();
            huff.codificar();
            huff.printTabela();
            huff.compactar();
        break;
        case 2:
            //huff.lerArquivoTabela();
            huff.lerArquivoTabelaBin();
            huff.montarArvore();
            //huff.printTabela();
            huff.descompactar();

        break;
    }

    return 0;
}


