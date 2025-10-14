#ifndef INTERFACE
#define INTERFACE

#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <string>

namespace itf {

    class interface {
        std::map<std::string, bool> map;
        std::string entrada1;
        std::string entrada2;

        public:
            interface();
            bool ajuda{false};   
            void textoDeAjuda();
            bool verify(int argc, char* argv[]);
            int iniciar();
            std::string getEntrada1();
            std::string getEntrada2();
    };


};

#endif