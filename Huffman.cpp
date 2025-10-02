#include "Huffman.hpp"

using namespace hf;


std::string hf::PALAVRAS_CHAVE_CPP[NUM_PALAVRAS_CHAVE] = {      //array constante das palavras chave de c++
    "for", "return", "include", "std", "if", "else", "switch",
    "case", "int", "float", "string", "char", "while", "bool"
};

std::vector<std::string> palavrasChaveEncontradas;          //vetor que guarda cada palavra chave que encontrar para evitar contar os caracteres dela.

int Huffman::pertenceNaSubstring(std::vector<Huffman::substring> &substrings, size_t &i){
    for(substring alvo :substrings){
        if(alvo.pos == i){
            return alvo.palavraint;
        }
    }
    return -1;
}

void atualizar(std::string &alvo, size_t pos, size_t tamanho){
    for(size_t i = pos; i < pos + tamanho; i++){
        alvo[i] = 'x';
    }
}

void Huffman::cacarNSubstrings(std::string &alvo, size_t i, std::vector<Huffman::substring> &substrings_encontradas){
    if(alvo.find(nos[i]->caractere) !=std::string::npos){
        size_t temp = alvo.find(nos[i]->caractere);
        auto encontrada= new Huffman::substring(temp,i);
        substrings_encontradas.push_back(*encontrada);
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
}

Huffman::Huffman(std::string entrada, std::string entrada2) { //construtor padrão

    nomeDaEntrada = entrada;
    nomeDaEntrada2 = entrada2;
    encherArrayDeCaracteres();
    encherArrayDePalavras();
}

Huffman::Huffman(std::string entrada) { //construtor padrão
    nomeDaEntrada = entrada;
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



void Huffman::montarTabela() {
    std::ifstream arquivo(nomeDaEntrada);
    std::string linha;
    size_t poslinha=0;
    while(std::getline(arquivo,linha)){

        nos[10]->freq++;

         auto substrings=cacarSubstrings(linha);
        for(size_t i=0;i<linha.size();i++){
            int teste=pertenceNaSubstring(substrings,i);
            if(teste >= 0){
                nos[teste]->freq++;
                i+=nos[teste]->caractere.size()-1;
            }       
            else{
                unsigned char ch = linha[i];
                if (nos[ch] && ch < NUM_CARACTERES_ASCII) {
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
no::No* Huffman::montarArvore(){ //com base na frequência monta a arvore
    cf::ContadorDeFrequencia copia; //cria uma cópia a fim de preserva a lista original
    copia.priorityQueue = contador.priorityQueue;
    while(copia.priorityQueue.size()>1){//pegamos de dois em dois elementos até forma o nó raiz por isso a condição de parada é quando chegar a 1
        no::No* no1=new no::No(copia.priorityQueue.top()); // cria um ponteiro que copia o primeiro elemento
        copia.priorityQueue.pop();
        no::No* no2=new no::No(copia.priorityQueue.top());
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
void Huffman::printTabela(){            //apenas para teste: printa todos os nós com suas respectivas frequencias.
    while(!contador.priorityQueue.empty()){
        no::No* no = contador.priorityQueue.top();
        contador.priorityQueue.pop();
        if(no->caractere == "\n"){
        std::cout << "( "<< "\\n "<< ", " << no->freq << ", "<< no->codigo<< ") ";
        std::cout << std::endl;
        continue;
        }
        std::cout << "( "<< no->caractere << ", " << no->freq << ", "<< no->codigo<< ") ";
        std::cout << std::endl;
    }
}

std::string Huffman::fazerCodigo(std::string alvo,no::No* busca,std::string codigo){//cria o código de 1 elemento apenas
    if(busca == nullptr)return "";
    if(alvo==busca->caractere){//achei o elemento então retorno seu código
        return codigo;
    }
    else if(busca->filhoEsq == nullptr){//veja a chamada e recursiva e volte. Voltou? chamamos a função em todos os nóss, se caso chegarmos em uma folha e ela não é o alvo apenas retornamos uma string vazia para não influenciar no resultado final
        return "";
    }
    else{//por fim, chegamos aqui e nada.Agora, vamos para nó a esquerda e para o nó a direita, também veja que eles já carregam uma informação sobre o caminho de onde vieram
        return fazerCodigo(alvo,busca->filhoEsq, codigo+"0") + fazerCodigo(alvo,busca->filhoDir,codigo+"1");
    }
}
void Huffman::codificar(){//cria o código de todos
    cf::ContadorDeFrequencia copia;// copiamos para não alterar a original, ela pode ser útil mas tarde
    copia.priorityQueue=contador.priorityQueue;
    while(!copia.priorityQueue.empty()){//basicamente aplica a função anterior em todos os elementos
        copia.priorityQueue.top()->codigo=fazerCodigo(copia.priorityQueue.top()->caractere,ArvoreDeHuffman,"");
        copia.priorityQueue.pop();
    }
}
void Huffman::compactar(){
    std::ifstream arquivol(nomeDaEntrada);
    std::ofstream arquivow("algo.bin");
    std::string linha;

    std::string codigo_quebra_linha = "";
    if (nos[10] && !nos[10]->codigo.empty()){
        codigo_quebra_linha = nos[10]->codigo;
    }

    while (std::getline(arquivol, linha)){
        auto substrings=cacarSubstrings(linha);
        for(size_t i=0;i<linha.size();i++){
            int teste=pertenceNaSubstring(substrings,i);
            if(teste >= 0){
                arquivow << nos[teste]->codigo;
                i+=nos[teste]->caractere.size()-1;
            }
            else{
                char ch = linha[i];
                if (nos[ch]) {
                    arquivow << nos[ch]->codigo;
                } else {
                    //std::cerr << "Caracter inválido ou não encontrado";
                }
            }
        }
        if(!codigo_quebra_linha.empty()){
            arquivow << codigo_quebra_linha;
        }
        
    }
    arquivow.close();
    arquivol.close();
}


void Huffman::descompactar(){
    std::ifstream ifs(nomeDaEntrada);
    std::ofstream ofs("original.txt");
    std::string linha;
    
    std::getline(ifs, linha);

    no::No *aux = ArvoreDeHuffman;

    for(char c : linha){
        if(aux->filhoEsq == nullptr){
            ofs << aux->caractere;
            aux = ArvoreDeHuffman;
        }

        if(c == '0'){
            aux = aux->filhoEsq;
        }
        if(c == '1'){
            aux = aux->filhoDir;
        }
    }

    ifs.close();
    ofs.close();


}


