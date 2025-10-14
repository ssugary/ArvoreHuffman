#include "Tabela.hpp"

using namespace tb;

std::string tb::PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE] = {      
    "for", "return", "include", "std", "if", "else", "switch",
    "case", "int", "float", "string", "char", "while", "bool",
    "ç","á","à","ã","â","ä","è","é","ê","ẽ","ë","í",
    "ì","ĩ","ó","ò","õ","ô","ö","ú","ù","ũ","û","ü",
    "À","Á","Ã","Â","Ä","É","È","Ẽ","Ê","Ë","Í","Ì",
    "Ï","Ó","Ò","Õ","Ô","Ö","Ú","Ù","Û","Ũ","Ü"
};

Tabela::Tabela(std::string nomeDaEntrada){
    this->nomeDaEntrada=nomeDaEntrada;
    encherArrayDeCaracteres();
    encherArrayDePalavras();
}
Tabela::~Tabela() {
    for(size_t i{0}; i < NUM_PALAVRAS_CHAVE + NUM_CARACTERES_ASCII; i++){
        if(elementos[i]){

        delete elementos[i];
        elementos[i] = nullptr;

        }
    }
}

void Tabela::encherArrayDeCaracteres(){

    for(size_t i{0}; i < NUM_CARACTERES_ASCII; i++){
        elementos[i] = new elem(std::string(1,static_cast<char>(i)));
    }   
    
}

void Tabela::encherArrayDePalavras() {                                

    for (size_t i = 0; i < NUM_PALAVRAS_CHAVE; ++i) {
        elementos[NUM_CARACTERES_ASCII + i] = new elem(PALAVRAS_CHAVE_CPP[i]);
    }
}
void Tabela::montarTabela() {
    std::ifstream arquivo(nomeDaEntrada);
    std::string linha;
    size_t poslinha=0;
    while(std::getline(arquivo,linha)){
        //linha = removerAcentos(linha);
        elementos[10]->freq++;

        auto mapa=cacarMapaSubstrings(linha);
        for(size_t i=0;i<linha.size();i++){
            int teste=pertenceNaSubstring(mapa,i);
            if(teste >= 0){
                elementos[teste]->freq++;
                i+=elementos[teste]->caractere.size()-1;
            }       
            else{
                unsigned char ch = linha[i];
                if (ch < NUM_CARACTERES_ASCII && elementos[ch]) {
                    elementos[ch]->freq++;
                } else {
                    std::cerr << poslinha << " " << i << std::endl << linha[i] << " " <<"Caracter inválido ou não encontrado" << std::endl; 
                }
            }
        }
        poslinha++;
    }
    arquivo.close();
}
void Tabela::printTabela() {
    elementos[10]->caractere = "\\n";
    for (size_t i = 0; i < NUM_PALAVRAS_CHAVE + NUM_CARACTERES_ASCII; i++) {
        if (elementos[i]->freq > 0) {
            std::cout << "( " << elementos[i]->caractere << ", "<< elementos[i]->freq << ", ";
            std::cout << " )" << std::endl;
        }
    }
    elementos[10]->caractere = "\n";  // volta ao normal
}
void atualizar(std::string &alvo, size_t pos, size_t tamanho){
    for(size_t i = pos; i < pos + tamanho; i++){
        alvo[i] = 'x';
    }
}

std::unordered_map<size_t, int> Tabela::cacarMapaSubstrings(std::string &alvo){
    std::unordered_map<size_t, int> substrings_encontradas;
    std::string alvotemp = alvo;
    for(size_t i = NUM_CARACTERES_ASCII; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; i++){
        size_t pos = 0;
        while ((pos = alvotemp.find(elementos[i]->caractere, pos)) != std::string::npos) {
            substrings_encontradas[pos] = i;
            atualizar(alvotemp, pos, elementos[i]->caractere.size());
            pos += elementos[i]->caractere.size();
        }
    }
    return substrings_encontradas;
}

int Tabela::pertenceNaSubstring(std::unordered_map<size_t, int>& mapa, size_t i){
    auto it = mapa.find(i);
    return (it != mapa.end()) ? it->second : -1;
}

void Tabela::criarArquivoTabela(){
    std::ofstream arquivo("tabela.txt");
    for(size_t i=0;i<NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE;i++){
        if(elementos[i]->freq > 0){
            arquivo << i << " "<<elementos[i]->freq << " ";
        }
    }
    arquivo.close();
}
std::list<bool> numbin(int alvo){
    std::list<bool> bin;
    if(alvo==0){
        bin.push_front(0);
        return bin;
    }
    while(alvo>0){
        bin.push_front(alvo%2);
        alvo /=2;
    }
    
    return bin;
}
void Tabela::criarArquivoTabelaBin(){
    std::ofstream arquivow("tabela.bin", std::ios::binary);
    auto acharmaior = [](elem *alvo[]){
        size_t maior=0;
        for(size_t i=0;i < NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE; i++){
            if(alvo[i]->freq>maior){
                maior=alvo[i]->freq;
            }
        }
        int maiorbin=numbin(maior).size();
        if(maiorbin % 8 != 0){
            maiorbin+= 8-maiorbin%8;
        }
        return maiorbin;
    };
    size_t padrao = acharmaior(elementos);
    unsigned char byte = 0;
    int count = 0;
    auto escrever_bit = [&](bool bit) {
        byte = (byte << 1) | bit;
        count++;
        if (count == 8) {
            arquivow.put(byte);
            byte = 0;
            count = 0;
        }
    };
    auto numbinpadrao = [](size_t alvo,size_t padrao){
        std::list<bool> bin= numbin(alvo);
        if(bin.size() == padrao){
            return bin;
        }
        else{
            while(bin.size()!=padrao){
                bin.push_front(0);
            }
            return bin;
        }
    };
    for (bool bit : numbinpadrao(padrao,8)){
        escrever_bit(bit);
    }
    size_t salto=1;
    bool primeiro=true;
    for(size_t i=0; i<NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE;i++){
        if(elementos[i]->freq > 0 && primeiro){
            for (bool bit : numbinpadrao(i,8)) {
                escrever_bit(bit);
            }
            for (bool bit : numbinpadrao(elementos[i]->freq,padrao)) {
                escrever_bit(bit);
            }
            primeiro= false;
        }     
        else if(elementos[i]->freq > 0 && !primeiro){
            for (bool bit : numbinpadrao(salto,8)) {
                escrever_bit(bit);
            }
            for (bool bit : numbinpadrao(elementos[i]->freq,padrao)) {
                escrever_bit(bit);
            }
            salto=1;
        }
        else if(elementos[i]->freq == 0 && !primeiro){
            salto++;
        }
    }
    arquivow.close();
}
void Tabela::ImprimirArquivoBin(){
    std::ifstream ifs("tabela.bin", std::ios::binary);
    unsigned char byte;
    while(ifs.read(reinterpret_cast<char*>(&byte), 1)){
        for(int i = 7; i >= 0; i--){
            bool bit = (byte >> i) & 1;
        if(bit){
            std::cout<<"1";
        }
        else{
            std::cout<<"0";
        }
        }
        std::cout<<"/";
    }
}