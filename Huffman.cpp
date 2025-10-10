#include "Huffman.hpp"

using namespace hf;

std::string removerAcentos(const std::string& str) {
    std::string sem_acentos;
    for (char c : str) {
        // Elimina caracteres não-ASCII (acento, emoji, etc.)
        if ((unsigned char)c < 128) {
            sem_acentos += c;
        }
    }
    return sem_acentos;
}

std::string hf::PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE] = {      
    "for", "return", "include", "std", "if", "else", "switch",
    "case", "int", "float", "string", "char", "while", "bool",
    "ç","á","à","ã","â","ä","è","é","ê","ẽ","ë","í",
    "ì","ĩ","ó","ò","õ","ô","ö","ú","ù","ũ","û","ü",
    "À","Á","Ã","Â","Ä","É","È","Ẽ","Ê","Ë","Í","Ì",
    "Ï","Ó","Ò","Õ","Ô","Ö","Ú","Ù","Û","Ũ","Ü"
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



void Huffman::cacarNSubstrings(std::string &alvo, size_t i, std::vector<Huffman::substring> &substrings_encontradas){
    size_t temp = alvo.find(nos[i]->caractere);
    if(temp !=std::string::npos){
        substrings_encontradas.emplace_back(temp, i);
        atualizar(alvo, temp, nos[i]->caractere.size());
        cacarNSubstrings(alvo, i, substrings_encontradas);
    }

}


std::vector<Huffman::substring> Huffman::cacarSubstrings(std::string &alvo){
    std::vector<Huffman::substring> substrings_encontradas;
    std::string alvotemp = alvo;
    for(size_t i=NUM_CARACTERES_ASCII;i < NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE; i++){
        cacarNSubstrings(alvotemp, i, substrings_encontradas);
    }
    return substrings_encontradas;
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

/*Huffman::Huffman(std::string entrada) { //construtor padrão
    nomeDaEntrada = entrada;
    encherArrayDeCaracteres();
    encherArrayDePalavras();
}*/

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



/*void Huffman::montarTabela() {
    std::ifstream arquivo(nomeDaEntrada);
    std::string linha;
    size_t poslinha=0;
    while(std::getline(arquivo,linha)){
        linha = removerAcentos(linha);
        nos[10]->freq++;

         auto mapa=cacarMapaSubstrings(linha);
        for(size_t i=0;i<linha.size();i++){
            int teste=pertenceNaSubstring(mapa,i);
            if(teste >= 0){
                nos[teste]->freq++;
                i+=nos[teste]->caractere.size()-1;
            }       
            else{
                unsigned char ch = linha[i];
                if (ch < NUM_CARACTERES_ASCII && nos[ch]) {
                    nos[ch]->freq++;
                } else {
                    std::cerr << poslinha << " " << i << std::endl << linha[i] << " " <<"Caracter inválido ou não encontrado" << std::endl; 
                }
            }
        }
        poslinha++;
    }
    arquivo.close();
}
void Huffman::criarArquivoTabela(){
    std::ofstream arquivo("tabela.txt");
    for(size_t i=0;i<NUM_CARACTERES_ASCII+NUM_PALAVRAS_CHAVE;i++){
        if(nos[i]->freq > 0){
            arquivo << i << " "<<nos[i]->freq << " ";
        }
    }
    arquivo.close();
}
*/
void Huffman::lerArquivoTabela(){
    arquivoDeEntrada.open(nomeDaEntrada2, std::fstream::in);
    std::string palavra;
    size_t i = 0;
    bool index =true;
    while (arquivoDeEntrada >> palavra) { 
        if(index){
            i=std::stoi(palavra);
            index=false;
        }
        else{
            nos[i]->freq=std::stoi(palavra);
            index=true;
        }
    }
    for (size_t i = 0; i < NUM_CARACTERES_ASCII + NUM_PALAVRAS_CHAVE; ++i) {
        if (nos[i]->freq > 0) {         //apenas coloca cada nó (após contagem da frequencia) na priority_queue
            contador.priorityQueue.push(nos[i]);
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
// void Huffman::printTabela(){            //apenas para teste: printa todos os nós com suas respectivas frequencias.
//     while(!contador.priorityQueue.empty()){
//         no::No* no = contador.priorityQueue.top();
//         contador.priorityQueue.pop();
//         if(no->caractere == "\n"){
//         std::cout << "( "<< "\\n "<< ", " << no->freq << ", "<< no->codigo<< ") ";
//         std::cout << std::endl;
//         continue;
//         }
//         std::cout << "( "<< no->caractere << ", " << no->freq << ", "<< no->codigo<< ") ";
//         std::cout << std::endl;
//     }
// }
                        //mesma coisa da ultima, mas com complexidade O(n) ao invés de O(n log (n)).
// void Huffman::printTabela(){
//     nos[10]->caractere = "\\n";
//     for(size_t i{0}; i < NUM_PALAVRAS_CHAVE + NUM_CARACTERES_ASCII; i++){
//         if(!nos[i]->codigo.empty()){
//             std::cout << "( " << nos[i]->caractere << ", "
//                       << nos[i]->freq << ", "
//                       << nos[i]->codigo << " )" << std::endl;
//         }
//     }
//     nos[10]->caractere = "\n";
// }
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

// std::string Huffman::fazerCodigo(std::string alvo,no::No* busca,std::string codigo){//cria o código de 1 elemento apenas
//     if(busca == nullptr)return "";
//     if(alvo==busca->caractere){//achei o elemento então retorno seu código
//         return codigo;
//     }
//     else if(busca->filhoEsq == nullptr){//veja a chamada e recursiva e volte. Voltou? chamamos a função em todos os nóss, se caso chegarmos em uma folha e ela não é o alvo apenas retornamos uma string vazia para não influenciar no resultado final
//         return "";
//     }
//     else{//por fim, chegamos aqui e nada.Agora, vamos para nó a esquerda e para o nó a direita, também veja que eles já carregam uma informação sobre o caminho de onde vieram
//         return fazerCodigo(alvo,busca->filhoEsq, codigo+"0") + fazerCodigo(alvo,busca->filhoDir,codigo+"1");
//     }
// }
// void Huffman::codificar(){//cria o código de todos
//     cf::ContadorDeFrequencia copia;// copiamos para não alterar a original, ela pode ser útil mas tarde
//     copia.priorityQueue=contador.priorityQueue;
//     while(!copia.priorityQueue.empty()){//basicamente aplica a função anterior em todos os elementos
//         copia.priorityQueue.top()->codigo=fazerCodigo(copia.priorityQueue.top()->caractere,ArvoreDeHuffman,"");
//         copia.priorityQueue.pop();
//     }
// }
            //mesma coisa da ultima, só que agora é O(n) ao invés de O(n). 
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


// void Huffman::compactar(){
//     std::ifstream arquivol(nomeDaEntrada);
//     std::ofstream arquivow("algo.bin", std::ios::binary);
//     std::string linha;

//     std::vector<bool> codigo_quebra_linha;
//     if (nos[10] && !nos[10]->codigo.empty()){
//         codigo_quebra_linha = nos[10]->codigo;
//     }

//     while (std::getline(arquivol, linha)){
//         linha = removerAcentos(linha);
//         auto substrings=cacarSubstrings(linha);
//         for(size_t i=0;i<linha.size();i++){
//             int teste=pertenceNaSubstring(substrings,i);
//             if(teste >= 0){
//                 arquivow << nos[teste]->codigo;
//                 i+=nos[teste]->caractere.size()-1;
//             }
//             else{
//                 char ch = linha[i];
//                 if (nos[ch]) {
//                     arquivow << nos[ch]->codigo;
//                 } else {
//                     //std::cerr << "Caracter inválido ou não encontrado";
//                 }
//             }
//         }
//         if(!codigo_quebra_linha.empty()){
//             arquivow << codigo_quebra_linha;
//         }
        
//     }
//     arquivow.close();
//     arquivol.close();
// }
void Huffman::compactar() {
    std::ifstream arquivol(nomeDaEntrada);
    std::ofstream arquivow("algo.bin", std::ios::binary);
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


// void Huffman::descompactar(){
//     std::ifstream ifs(nomeDaEntrada);
//     std::ofstream ofs("original.txt");
//     std::string linha;
    
//     std::getline(ifs, linha);

//     no::No *aux = ArvoreDeHuffman;

//     for(char c : linha){
//         if(aux->filhoEsq == nullptr){
//             ofs << aux->caractere;
//             aux = ArvoreDeHuffman;
//         }

//         if(c == '0'){
//             aux = aux->filhoEsq;
//         }
//         if(c == '1'){
//             aux = aux->filhoDir;
//         }
//     }

//     if (aux->filhoEsq == nullptr) {
//     ofs << aux->caractere;
// }

//     ifs.close();
//     ofs.close();


// }

void Huffman::descompactar(){
    std::ifstream ifs(nomeDaEntrada, std::ios::binary);
    std::ofstream ofs("original.txt");
    
    no::No *aux = ArvoreDeHuffman;

    unsigned char byte;
    
    while(ifs.read(reinterpret_cast<char*>(&byte), 1)){
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
    ifs.close();
    ofs.close();


}



