#include "interface.hpp"


itf::interface::interface(){
    entrada1 = "";
    entrada2 = "";
    map =
            {
                {"-h", false}, {"comprimir", false}, {"descomprimir", false}
            };
}

void itf::interface::textoDeAjuda(){

    std::ifstream ifs("./TextoDeAjuda.txt");
    std::string linha;

    while(std::getline(ifs, linha)){
        std::cout << linha << std::endl;
    }
    ifs.close();
}

bool verificarArquivos(std::string entrada1, std::string entrada2){

    if(std::filesystem::exists(entrada1) && std::filesystem::exists(entrada2)){
        if(std::filesystem::is_regular_file(entrada1) && std::filesystem::is_regular_file(entrada2)){
            return true;
        }
    }
return false;
}

bool itf::interface::verify(int argc, char* argv[]){

    for(size_t i{1}; i < argc; i++){
        if(map.count(argv[i])){
            map[argv[i]] = true;
            continue;
        }
        else if(entrada1.empty()){
            entrada1 = argv[i];
        }
        else if(entrada2.empty()){
            entrada2 = argv[i];
        }
        else {
            return false;
        }
        
    }

    if(map["-h"]){
        ajuda = true;
        return false;
    }
    
    if(map["comprimir"] && map["descomprimir"]){
        return false;
    }

    return verificarArquivos(entrada1, entrada2);
}

int itf::interface::iniciar(){

    if(ajuda)              return 0;
    if(map["comprimir"])   return 1;
    if(map["descomprimir"])return 2;


    return 0;
}

std::string itf::interface::getEntrada1(){return entrada1;}
std::string itf::interface::getEntrada2(){return entrada2;}
