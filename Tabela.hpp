#ifndef ARVORE_DE_HUFFMAN
#define ARVORE_DE_HUFFMAN
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <list>

namespace tb {
    constexpr size_t NUM_PALAVRAS_CHAVE = 61;           
    constexpr size_t NUM_CARACTERES_ASCII = 128;
    extern std::string PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE]; 

    class Tabela{
        std::string nomeDaEntrada;
        struct elem{
            std::string caractere;
            size_t freq;
            elem(std::string caractere){
                this->caractere=caractere;
                this->freq=0;
            }
        };
        elem* elementos[NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE];
        void encherArrayDeCaracteres();
        void encherArrayDePalavras();
        public:
        Tabela(std::string);
        void montarTabela();
        void printTabela();
        void criarArquivoTabela();
        void criarArquivoTabelaBin();
        std::unordered_map<size_t, int> cacarMapaSubstrings(std::string &alvo);
        int pertenceNaSubstring(std::unordered_map<size_t, int>& mapa,size_t i);
        void ImprimirArquivoBin();
    };
}
#endif