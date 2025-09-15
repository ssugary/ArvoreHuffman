#include "Huffman.hpp"

using namespace hf;


std::string hf::PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE] = {      //array constante das palavras chave de c++
    "for", "return", "include", "std", "if", "else", "switch",
    "case", "int", "float", "string", "char", "while", "bool"
};

std::vector<std::string> palavrasChaveEncontradas;          //vetor que guarda cada palavra chave que encontrar para evitar contar os caracteres dela.


void Huffman::encherArrayDeCaracteres(){

    for(size_t i{0}; i < NUM_CARACTERES_ASCII; i++){
        nos[i] = new no::No(std::string(1, static_cast<char>(i)), 0);   //apenas preenche o array para evitar nullptrs
    }   
    
}

void Huffman::encherArrayDePalavras() {                                 //apenas preenche o array para evitar nullptrs

    for (size_t i = 0; i < NUM_PALAVRAS_CHAVE; ++i) {
        nos[NUM_CARACTERES_ASCII + i] = new no::No(PALAVRAS_CHAVE_CPP[i], 0);
    }
}




Huffman::Huffman(std::string entrada, std::string saida) { //construtor padrão

    nomeDaEntrada = entrada;
    nomeDaSaida = saida;
    encherArrayDeCaracteres();
    encherArrayDePalavras();
}

Huffman::~Huffman(){                                       //destrutor padrão
    for(size_t i{0}; i < NUM_CARACTERES_ASCII; i++){
        delete nos[i];
    }
    for(size_t i{NUM_CARACTERES_ASCII}; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; i++){
        delete nos[i];
    }
}

void Huffman::lerPalavrasChave() {          //leitor de palavras chave
    arquivoDeEntrada.open(nomeDaEntrada, std::fstream::in);
    std::string palavra;

    while (arquivoDeEntrada >> palavra) {           //lê palavra por palavra
        for (size_t i = 0; i < NUM_PALAVRAS_CHAVE; ++i) {
            if (PALAVRAS_CHAVE_CPP[i] == palavra) {     //caso for uma palavra chave, aumenta a frequência dela e adiciona no vetor delas.
                nos[NUM_CARACTERES_ASCII + i]->freq++;
                palavrasChaveEncontradas.push_back(palavra);
                break;
            }
        }
    }

    arquivoDeEntrada.close();
}


void Huffman::montarTabela() {
    lerPalavrasChave();         //primeiro lê as palavras chave para evitar contagem repetida

    arquivoDeEntrada.open(nomeDaEntrada, std::fstream::in);
    std::string palavra;

    while (arquivoDeEntrada >> palavra) {   //lê palavra por palavra do arquivo
        bool ignorar = false;
        for (const std::string& p : palavrasChaveEncontradas) {
            if (p == palavra) {             //caso a palavra esteja no array de palavras chave, iremos pular ela.
                ignorar = true;
                break;
            }
        }

        if (ignorar) continue;

        for (char c : palavra) {        //caso ela passe, então lemos todos os caracteres dela e aumentamos a sua frequência
            unsigned char id = static_cast<unsigned char>(c);
            if (id < NUM_CARACTERES_ASCII) {
                nos[id]->freq++;
            }
        }
    }

    arquivoDeEntrada.close();

    for (size_t i = 0; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; ++i) {
        if (nos[i]->freq > 0) {         //apenas coloca cada nó (após contagem da frequencia) na priority_queue
            contador.priorityQueue.push(nos[i]);
        }
    }
}


void Huffman::printTabela(){            //apenas para teste: printa todos os nós com suas respectivas frequencias.
    while(!contador.priorityQueue.empty()){
        no::No* no = contador.priorityQueue.top();
        contador.priorityQueue.pop();
        std::cout << "( "<< no->caractere << ", " << no->freq << ") ";
        std::cout << std::endl;
    }
}