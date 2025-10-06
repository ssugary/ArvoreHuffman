#ifndef ARVORE_DE_HUFFMAN
#define ARVORE_DE_HUFFMAN

#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "ContadorDeFrequencia.hpp"
#include "No.hpp"



namespace hf {

    constexpr size_t NUM_PALAVRAS_CHAVE = 14;           //constantes que definem o tamanho do array de nós.
    constexpr size_t NUM_CARACTERES_ASCII = 128;

    extern std::string PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE];  //array das palavras chave do c++


    class Huffman {
        struct substring{
        size_t pos;
        size_t palavraint;
        substring(size_t pos, size_t palavraint){
            this->pos=pos;
            this->palavraint=palavraint;
        }
        };
        int pertenceNaSubstring(std::unordered_map<size_t, int>& mapa,size_t i);
        std::vector<substring> cacarSubstrings(std::string&);
        no::No* nos[NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE]; //array de todos os nós e possiveis caracteres + possiveis palavras chave
        cf::ContadorDeFrequencia contador;  //priority_queue para organizar os nós.
        no::No* ArvoreDeHuffman;
        std::fstream arquivoDeEntrada; //arquivo de saida está inutilizavel ainda, mas o de entrada é o que a gente vai ler
        std::string nomeDaEntrada; //nome do arquivo de entrada
        std::string nomeDaEntrada2; //nome do arquivo de saída
        void encherArrayDeCaracteres(); // "construtores" do array de nós
        void encherArrayDePalavras();
        std::unordered_map<size_t, int> cacarMapaSubstrings(std::string &alvo);
        public:
    
        Huffman(std::string, std::string); //construtor da classe
        Huffman(std::string); //construtor da classe
        ~Huffman();                         // destrutor da classe
        void montarTabela();                //função que pega os caracteres + palavras chave do arquivo de leitura e joga na priority_queue
        void criarArquivoTabela();
        void lerArquivoTabela();
        void printTabela();                 //apenas para testes: printa todos os nós em ordem de prioridade
        no::No* montarArvore();
        int mostrarArvore(no::No* nodo);
        //std::string fazerCodigo(std::string alvo, no::No* busca,std::string codigo);
        //void fazerCodigo(no::No* no, std::string& codigo);
        void fazerCodigo(no::No* no, std::vector<bool>& codigo);
        void codificar();
        void compactar();
        void cacarNSubstrings(std::string &substring, size_t n, std::vector<Huffman::substring> &substrings_encontradas);
        void descompactar();
    };


};

#endif