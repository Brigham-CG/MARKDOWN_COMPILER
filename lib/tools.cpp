#include <regex>
#include <fstream>
#include <iostream>

using namespace std;

#ifndef TOOLS_H
#define TOOLS_H


string read_file(string file_path) {
    std::ifstream file(file_path);   

    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo: " << file_path << std::endl;
        return ""; 
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    file.close();
    
    return content;
}

bool isURLValid(const std::string& url) {
    // Expresión regular para una URL válida (http:// o https://)
    std::regex urlPattern(R"(^(https?://)[^\s/$.?#].[^\s]*$)");
    
    // Verifica si la URL coincide con el patrón
    return std::regex_match(url, urlPattern);
}


bool is_uppercase(const std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isupper(c);
    });
}

#endif // TOOLS_H