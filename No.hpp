#ifndef NO_DE_HUFFMAN
#define NO_DE_HUFFMAN

#include <cstddef>
#include <string>

namespace no {      

    struct No {         //cada nó da arvore
        
        std::string caractere;      //caractere a ser contade
        size_t freq;                //frequencia do caractere
        std::string codigo;         //código gerado do caractere

        No* filhoEsq;       //como ela é binária, tem os dois filhos
        No* filhoDir;
        
        No(std::string caractere, size_t freq) {    //construtor padrão do nó
            filhoEsq = nullptr;
            filhoDir = nullptr;
            this->caractere = caractere;
            this->freq = freq;
        }
        
        ~No() {                 //destrutor do nó
            delete filhoDir;
            delete filhoEsq;
        }
    };

};

#endif