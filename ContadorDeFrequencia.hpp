#ifndef CONTADOR_DE_FREQUENCIA
#define CONTADOR_DE_FREQUENCIA

#include <string>
#include <vector>
#include <queue>

#include "No.hpp"


namespace cf {
    class ContadorDeFrequencia {

        private:

            struct CompararFrequencia {    
                bool operator()(const no::No* a, const no::No* b){    //para a comparação das frequências na priority_queue.
                    return a->freq > b->freq;
                }
            };

        public:
                //priority_queue para organizar cada nó
            std::priority_queue<no::No*, std::vector<no::No*>, CompararFrequencia> priorityQueue;
            

    };
};

#endif