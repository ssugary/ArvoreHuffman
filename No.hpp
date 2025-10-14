#ifndef NO_DE_HUFFMAN
#define NO_DE_HUFFMAN

#include <cstddef>
#include <string>
#include <vector>

namespace no {      

    struct No {         //cada nó da arvore
        
        std::string caractere;      //caractere a ser contade
        size_t freq;                //frequencia do caractere
        std::vector<bool> codigo;
        No* filhoEsq;       //como ela é binária, tem os dois filhos
        No* filhoDir;
        
        No(std::string caractere, size_t freq) {    //construtor padrão do nó
            filhoEsq = nullptr;
            filhoDir = nullptr;
            this->caractere = caractere;
            this->freq = freq;
        }
        No(No* no) {    //construtor para criar combinações
            filhoEsq = no->filhoEsq;
            filhoDir = no->filhoDir;
            caractere = no->caractere;
            freq = no->freq;
        }
        No(No* no1, No* no2) {    //construtor para criar combinações
            filhoEsq = no1;
            filhoDir = no2;
            caractere = no1->caractere + "+" + no2->caractere;
            freq = no1->freq + no2->freq;
        }
        ~No() {                 //destrutor do nó
            delete filhoDir;
            delete filhoEsq;
        }

    
    };

};

#endif