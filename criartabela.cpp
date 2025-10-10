#include <iostream>
#include "Tabela.hpp"

using namespace tb;

int main(int argc, char* argv[]){       //main apenas para teste
                                        //para compilar o código, faça o de sempre
    Tabela tabela(argv[1]);     //para rodar, use ./nomeEscolhido.out <arquivo_a_ser_lido> 

    tabela.montarTabela();
    tabela.criarArquivoTabelaBin();
    //tabela.printTabela();
    //tabela.criarArquivoTabela();
    tabela.printTabela();
    //tabela.ImprimirArquivoBin();
    return 0;
}