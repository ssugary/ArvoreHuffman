#include "Huffman.hpp"

using namespace hf;


std::string hf::PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE] = {      
    "for", "return", "include", "std", "if", "else", "switch",
    "case", "int", "float", "string", "char", "while", "bool",
    "ç","á","à","ã","â","ä","è","é","ê","ẽ","ë","í",
    "ì","ĩ","ó","ò","õ","ô","ö","ú","ù","ũ","û","ü",
    "À","Á","Ã","Â","Ä","É","È","Ẽ","Ê","Ë","Í","Ì",
    "Ï","Ó","Ò","Õ","Ô","Ö","Ú","Ù","Û","Ũ","Ü", "Ç"
};

std::vector<std::string> palavrasChaveEncontradas;          //vetor que guarda cada palavra chave que encontrar para evitar contar os caracteres dela.

void atualizar(std::string &alvo, size_t pos, size_t tamanho){
    for(size_t i = pos; i < pos + tamanho; i++){
        alvo[i] = 'x';
    }
}

std::unordered_map<size_t, int> Huffman::cacarMapaSubstrings(std::string &alvo){
    std::unordered_map<size_t, int> substrings_encontradas;
    std::string alvotemp = alvo;
    for(size_t i = NUM_CARACTERES_ASCII; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; i++){
        size_t pos = 0;
        while ((pos = alvotemp.find(nos[i]->caractere, pos)) != std::string::npos) {
            substrings_encontradas[pos] = i;
            atualizar(alvotemp, pos, nos[i]->caractere.size());
            pos += nos[i]->caractere.size();
        }
    }
    return substrings_encontradas;
}

int Huffman::pertenceNaSubstring(std::unordered_map<size_t, int>& mapa, size_t i){
    auto it = mapa.find(i);
    return (it != mapa.end()) ? it->second : -1;
}


void Huffman::encherArrayDeCaracteres(){

    for(size_t i{0}; i < NUM_CARACTERES_ASCII; i++){
        nos[i] = new no::No(std::string(1, static_cast<char>(i)), 0);   //apenas preenche o array para evitar nullptrs
    }   
    
}

void Huffman::encherArrayDePalavras() {                                 //apenas preenche o array para evitar nullptrs

    for (size_t i = 0; i < NUM_PALAVRAS_CHAVE; ++i) {
        nos[NUM_CARACTERES_ASCII + i] = new no::No(PALAVRAS_CHAVE_CPP[i], 0);
    }
    nos[NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE]=new no::No("eof",1);
}


Huffman::Huffman(std::string entrada, std::string entrada2) { //construtor padrão

    nomeDaEntrada = entrada;
    nomeDaEntrada2 = entrada2;
    encherArrayDeCaracteres();
    encherArrayDePalavras();
}


Huffman::~Huffman(){                                       //destrutor padrão
    for(size_t i{0}; i < NUM_CARACTERES_ASCII; i++){
       if (nos[i]) {
        delete nos[i];
        nos[i] = nullptr;
}

    }
    for(size_t i{NUM_CARACTERES_ASCII}; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; i++){
        if (nos[i]) {
            delete nos[i];
            nos[i] = nullptr;
}

    }
}
void Huffman::lerArquivoTabelaBin(){
    enum Vendo{
        tamanho,
        atual,
        freq,
        salto,
    };
    std::ifstream ifs(nomeDaEntrada2, std::ios::binary);
    size_t pos=0;
    size_t saltopos=0;
    size_t tamanhofeq=0;
    Vendo vendo=tamanho;
    std::list<bool>lido;
    std::list<bool>atualbin;
    unsigned char byte;
    while(ifs.read(reinterpret_cast<char*>(&byte), 1)){
        for(int i = 7; i >= 0; i--){
            bool bit = (byte >> i) & 1;
            lido.push_back(bit);
            if( i == 0 ){
                switch(vendo){
                    case tamanho:
                        for (bool bitt : lido) {
                            tamanhofeq = (tamanhofeq << 1) | bitt;
                        }
                        vendo=atual;
                        lido.clear();
                        break;
                    case atual:
                        for (bool bitt : lido) {
                            pos = (pos << 1) | bitt;
                        }
                        vendo=freq;
                        lido.clear();
                        break;
                    case freq:
                        if(lido.size()>=tamanhofeq){
                            for (bool bitt : lido) {
                                nos[pos]->freq = (nos[pos]->freq  << 1) | bitt;
                            }
                            saltopos=0;
                            vendo=salto;
                            lido.clear();
                        }
                        break;
                    case salto:
                        for (bool bitt : lido) {
                                saltopos = (saltopos << 1) | bitt;
                        }
                        pos+=saltopos;
                        vendo=freq;
                        lido.clear();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    for (size_t i = 0; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE+1; ++i) {
        if (nos[i]->freq > 0) {         //apenas coloca cada nó na priority_queueapós contagem da frequencia
            contador.priorityQueue.push(nos[i]);
        }
    }
    ifs.close();
}
no::No* Huffman::montarArvore(){ //com base na frequência monta a arvore
    cf::ContadorDeFrequencia copia; //cria uma cópia a fim de preserva a lista original
    copia.priorityQueue = contador.priorityQueue;
    while(copia.priorityQueue.size()>1){//pegamos de dois em dois elementos até forma o nó raiz por isso a condição de parada é quando chegar a 1
        no::No* no1= copia.priorityQueue.top(); // cria um ponteiro que copia o primeiro elemento
        copia.priorityQueue.pop();
        no::No* no2= copia.priorityQueue.top();
        copia.priorityQueue.pop();
        copia.priorityQueue.push(new no::No(no1,no2));//cria um novo elemento que é a combinação de outros dois e o insere na fila 
    }
    ArvoreDeHuffman=copia.priorityQueue.top();//o nó raiz é ele
    return ArvoreDeHuffman;
}
int Huffman::mostrarArvore(no::No* nodo){//mostra a arvore mas toda feia =(
    std::cout<<nodo->caractere<<" ";
    if(nodo->filhoEsq != nullptr && nodo->filhoDir != nullptr){
        return mostrarArvore(nodo->filhoEsq) + mostrarArvore(nodo->filhoDir);
    }
    else{
        return 0;
    }
 }

void Huffman::printTabela() {
    nos[10]->caractere = "\\n";
    for (size_t i = 0; i < NUM_PALAVRAS_CHAVE + NUM_CARACTERES_ASCII+1; i++) {
        if (!nos[i]->codigo.empty()) {
            std::cout << "( " << nos[i]->caractere << ", "
                      << nos[i]->freq << ", ";

            // Imprime cada bit do código
            for (bool bit : nos[i]->codigo) {
                std::cout << bit;
            }

            std::cout << " )" << std::endl;
        }
    }
    nos[10]->caractere = "\n";  // volta ao normal
}

 
void Huffman::fazerCodigo(no::No* no, std::vector<bool>& codigo){
    if (!no) return;
    if (!no->filhoEsq && !no->filhoDir) {
        no->codigo = codigo;
        return;
    }

    codigo.push_back(0);
    fazerCodigo(no->filhoEsq, codigo);
    codigo.pop_back(); // volta

    // Caminho para a direita
    codigo.push_back(1);
    fazerCodigo(no->filhoDir, codigo);
    codigo.pop_back();
}

void Huffman::codificar() {
    std::vector<bool> codigo;
    fazerCodigo(ArvoreDeHuffman, codigo);
}

void Huffman::compactar() {
    std::ifstream arquivol(nomeDaEntrada);
    
    auto retirar_extensao= [](std::string &nomeDaEntrada){
        auto numbin=[](int alvo){
            std::list<bool> bin;
            if(alvo==0){
                bin.push_front(0);
            }
            while(alvo>0){
                bin.push_front(alvo%2);
                alvo /=2;
            }
            for(size_t i=bin.size();i<8;i++){
                bin.push_front(0);
            }
            return bin;
        };
        std::list<std::list<bool>>extensao;
        while(nomeDaEntrada.back()!='.'){
            extensao.push_front(numbin((int)nomeDaEntrada.back()));
            nomeDaEntrada.pop_back();
        }
        extensao.push_front(numbin((extensao.size())));
        return extensao;
    };
    auto extensao=retirar_extensao(nomeDaEntrada);
    std::ofstream arquivow(nomeDaEntrada + "bin", std::ios::binary);
    std::string linha;

    std::vector<bool> codigo_quebra_linha;
    if (nos[10] && !nos[10]->codigo.empty()) {
        codigo_quebra_linha = nos[10]->codigo;
    }

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
    for(std::list<bool> caracterascii: extensao){
        for(bool bit: caracterascii){
            escrever_bit(bit);
        }
    }
    while (std::getline(arquivol, linha)) {
        //linha = removerAcentos(linha);
        auto substrings = cacarMapaSubstrings(linha);

        for (size_t i = 0; i < linha.size(); i++) {
            int idx = pertenceNaSubstring(substrings, i);
            if (idx >= 0) {
                for (bool bit : nos[idx]->codigo) {
                    escrever_bit(bit);
                }
                i += nos[idx]->caractere.size() - 1; // pula o tamanho da substring
            } else {
                unsigned char ch = linha[i];
                if (ch < NUM_CARACTERES_ASCII && nos[ch]) {
                    for (bool bit : nos[ch]->codigo) {
                        escrever_bit(bit);
                    }
                } else {
                    // caractere inválido, pode logar ou ignorar
                }
            }
        }

        // Escreve código para quebra de linha, se existir
        for (bool bit : codigo_quebra_linha) {
            escrever_bit(bit);
        }
    }
    for (bool bit : nos[NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE]->codigo) {
        escrever_bit(bit);
    }
    // Escreve o último byte, se houver bits restantes
    if (count > 0) {
        byte <<= (8 - count); // preenche com zeros à direita
        arquivow.put(byte);
    }

    arquivow.close();
    arquivol.close();
}

void Huffman::verExtensao(std::string &extensao){
    std::ifstream ifs(nomeDaEntrada, std::ios::binary);
    size_t tamanhoext=0;
    bool vendotamanhoext=true;
    unsigned char byte;
    while(ifs.read(reinterpret_cast<char*>(&byte), 1)){
        if(vendotamanhoext){
            for(int i = 7; i >= 0; i--){
                bool bit = (byte >> i) & 1;
                tamanhoext= (tamanhoext<< 1) | bit;
            }
            vendotamanhoext=false;
        }
        else if(tamanhoext>0){
            size_t temp = 0;
            for(int i = 7; i >= 0; i--){
                bool bit = (byte >> i) & 1;
                temp= (temp<< 1) | bit;
            }
            extensao.push_back((char)temp);
            tamanhoext--;
        }
        else{
            ifs.close();
            break;
        }
    }
    ifs.close();
}
void Huffman::descompactar(){
    std::string extensao;
    verExtensao(extensao);
    size_t tempextensao=extensao.size()+1;
    std::ifstream ifs(nomeDaEntrada, std::ios::binary);
    nomeDaEntrada.erase(nomeDaEntrada.size() - 4);
    std::ofstream ofs(nomeDaEntrada+"(1)."+extensao);
    
    no::No *aux = ArvoreDeHuffman;

    unsigned char byte;
    
    while(ifs.read(reinterpret_cast<char*>(&byte), 1)){
        if(tempextensao > 0){
            tempextensao--;
            continue;
        }
        else{
            for(int i = 7; i >= 0; i--){
                bool bit = (byte >> i) & 1;
                
                if(bit == 0){
                    aux = aux->filhoEsq;
                }
                else{
                    aux = aux->filhoDir;
                }


                if(!aux->filhoDir && !aux->filhoEsq){
                    if(aux->caractere == "\\n"){
                        ofs << "\n";
                    }
                    else if(aux->caractere =="eof"){
                        ifs.close();
                        ofs.close();
                        return;
                    }
                    else{
                        ofs << aux->caractere;
                    }
                
                    aux = ArvoreDeHuffman;
                }

            }
        }
    }
    ifs.close();
    ofs.close();

}



