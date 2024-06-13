#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <unordered_set>
#include <stack>
#include "token.cpp"
#include "tools.cpp"
#include "manageError.cpp"

#ifndef PARSER_CPP 
#define PARSER_CPP

using namespace std;

struct ProductionRule {
    string nonTerminal;
    string production;
};


class Parser
{
    private:
        void initializeParsingTable();
        unordered_map<string, unordered_map<string, ProductionRule>> parsingTable;
    public:
        Parser(vector<Token> input_tokens);
        void parsing_ll1(vector<Token> tokens);
        bool is_valid_terminal(string character);
        ManagerError errorManager;
};

Parser::Parser(vector<Token> input_tokens)
{   
    initializeParsingTable();

    parsing_ll1(input_tokens);

    cout << endl << "------------------- Results -------------------\n";
    if (errorManager.has_errors()) {
        cout << "[!] El código fuente contiene errores de sintaxis!" << endl;
        errorManager.what_is_missing();
        errorManager.print_errors();
    }
    else{
        cout << "[+] El código fuente fue correctamente parseado!" << endl;
    
    }
}

bool Parser::is_valid_terminal(std::string str) {
    static const std::unordered_set<std::string> valid_tokens = {
        "1t", "2t", "1s", "2s", "1z", "2z", "1p", "2p", "wo", "/n", "1*", "2*", "1_", "2_", "1$", "2$",
        "ro", "am", "az", "<o", ">o", "(c", ")c", "[f", "]f", "ar", "ti", "co", "he", "{u", "}u", "$$"
    };
    
    return valid_tokens.find(str) != valid_tokens.end();
}

void Parser::initializeParsingTable()
{
    parsingTable["DO"]["1p"] = {"DO", "BL"};            // [Documento][I_PARAFO] = Documento -> Bloque
    parsingTable["DO"]["1t"] = {"DO", "BL"};            // [Documento][I_TITULO] = Documento -> Bloque
    parsingTable["DO"]["1s"] = {"DO", "BL"};            // [Documento][I_SUBTITULO] = Documento -> Bloque
    parsingTable["DO"]["1z"] = {"DO", "BL"};            // [Documento][I_SUBSUBTITULO] = Documento -> Bloque
    parsingTable["DO"]["/n"] = {"DO", "BL"};            // [Documento][SALTO_DE_LINEA] = Documento -> Bloque
    parsingTable["DO"]["$$"] = {"DO", "BL"};            // [Documento][END_OF_FILE] = Documento -> Bloque

    parsingTable["BL"]["1p"] = {"BL", "1pTE2pBL"};      // [Bloque][I_PARAFO] = Bloque -> I_PARAFO TExto F_PARAFO Bloque
    parsingTable["BL"]["1t"] = {"BL", "1tTE2tBL"};      // [Bloque][I_TITULO] = Bloque -> I_TITULO TExto F_TITULO Bloque
    parsingTable["BL"]["1s"] = {"BL", "1sTE2sBL"};      // [Bloque][I_SUBTITULO] = Bloque -> I_SUBTITULO TExto F_SUBTITULO Bloque
    parsingTable["BL"]["1z"] = {"BL", "1zTE2zBL"};      // [Bloque][I_SUBSUBTITULO] = Bloque -> I_SUBSUBTITULO TExto F_SUBSUBTITULO Bloque
    parsingTable["BL"]["/n"] = {"BL", "/nBL"};          // [Bloque][SALTO_DE_LINEA] = Bloque -> SALTO_DE_LINEA Bloque
    parsingTable["BL"]["$$"] = {"BL", "  "};            // [Bloque][END_OF_FILE] = Bloque -> EPSILON

    parsingTable["TE"]["2p"] = {"TE", "  "};            // [Texto][F_PARAFO] = Texto -> EPSILON
    parsingTable["TE"]["2t"] = {"TE", "  "};            // [Texto][F_TITULO] = Texto -> EPSILON
    parsingTable["TE"]["2s"] = {"TE", "  "};            // [Texto][F_SUBTITULO] = Texto -> EPSILON
    parsingTable["TE"]["2z"] = {"TE", "  "};            // [Texto][F_SUBSUBTITULO] = Texto -> EPSILON
    parsingTable["TE"]["/n"] = {"TE", "/nTE"};          // [Texto][SALTO_DE_LINEA] = Texto -> SALTO_DE_LINEA Texto
    parsingTable["TE"]["wo"] = {"TE", "woTE"};          // [Texto][WORD] = Texto -> word Texto
    parsingTable["TE"]["1*"] = {"TE", "TSTE"};          // [Texto][I_NEGRITA] = Texto -> TextoPrima Texto
    parsingTable["TE"]["2*"] = {"TE", "  "};            // [Texto][F_NEGRITA] = Texto -> EPSILON
    parsingTable["TE"]["1$"] = {"TE", "TSTE"};          // [Texto][I_CURSIVA] = Texto -> TextoPrima Texto
    parsingTable["TE"]["2$"] = {"TE", "  "};            // [Texto][F_CURSIVA] = Texto -> EPSILON
    parsingTable["TE"]["1_"] = {"TE", "TSTE"};          // [Texto][I_TACHADO] = Texto -> TextoPrima Texto
    parsingTable["TE"]["2_"] = {"TE", "  "};            // [Texto][F_TACHADO] = Texto -> EPSILON
    parsingTable["TE"]["<o"] = {"TE", "TSTE"};          // [Texto][I_OPCION] = Texto -> TextoPrima Texto
    parsingTable["TE"][">o"] = {"TE", "  "};            // [Texto][F_OPCION] = Texto -> EPSILON

    parsingTable["TS"]["1*"] = {"TS", "1*TE2*"};        // [TextoPrima][I_NEGRITA] = TextoPrima -> I_NEGRITA Texto F_NEGRITA
    parsingTable["TS"]["1$"] = {"TS", "1$TE2$"};        // [TextoPrima][I_CURSIVA] = TextoPrima -> I_CURSIVA Texto F_CURSIVA
    parsingTable["TS"]["1_"] = {"TS", "1_TE2_"};        // [TextoPrima][I_TACHADO] = TextoPrima -> I_TACHADO Texto F_TACHADO
    parsingTable["TS"]["<o"] = {"TS", "<oOP>o"};        // [TextoPrima][I_OPCION] = TextoPrima -> I_OPCION Opcion F_OPCION

    parsingTable["OP"]["(c"] = {"OP", "(cCO)cTE"};      // [Opcion][I_COLOR] = Opcion -> I_COLOR Color F_COLOR Texto
    parsingTable["OP"]["[f"] = {"OP", "[fFU]fTE"};      // [Opcion][I_FUENTE] = Opcion -> I_FUENTE Fuente F_FUENTE Texto
    parsingTable["OP"]["{u"] = {"OP", "{uwo}uTE"};      // [Opcion][I_URL] = Opcion -> I_URL URL F_URL Texto

    parsingTable["CO"]["ro"] = {"CO", "ro"};            // [Color][ROJO] = Color -> ROJO           
    parsingTable["CO"]["az"] = {"CO", "az"};            // [Color][AZUL] = Color -> AZUL
    parsingTable["CO"]["am"] = {"CO", "am"};            // [Color][AMARILLO] = Color -> AMARILLO

    parsingTable["FU"]["ar"] = {"FU", "ar"};            // [Fuente][ARIAL] = Fuente -> ARIAL
    parsingTable["FU"]["ti"] = {"FU", "ti"};            // [Fuente][TIMES] = Fuente -> TIMES
    parsingTable["FU"]["co"] = {"FU", "co"};            // [Fuente][COURIER] = Fuente -> COURIER
    parsingTable["FU"]["he"] = {"FU", "he"};            // [Fuente][HELVETICA] = Fuente -> HELVETICA

    //parsingTable["UR"]["la"] = {"UR", "la"};            // [URL][linka] = URL -> linka
    //parsingTable["UR"]["lb"] = {"UR", "lb"};            // [URL][linkb] = URL -> linkb
    //parsingTable["UR"]["lc"] = {"UR", "lc"};            // [URL][linkc] = URL -> linkc
}

void print_tokens(vector<Token> input_tokens)
{
    for(int i = 0; i < input_tokens.size(); i++)
    {
        input_tokens[i].print();
    }
}

void Parser::parsing_ll1(vector<Token> input_tokens)
{
    input_tokens.push_back(Token(END_OF_FILE, "$$", 1));
    // print_tokens(input_tokens);
    stack<string> parseStack;
    parseStack.push("$$");
    parseStack.push("DO"); 

    size_t pos = 0;
    string currentSymbol = parseStack.top();
    string inputSymbol = input_tokens[pos].get_string();

    while (!parseStack.empty()) {

        currentSymbol = parseStack.top();
        inputSymbol = input_tokens[pos].get_string();

        std::cout << "CURRENT: '" << currentSymbol << "' INPUT: '" << inputSymbol << "'\n";

        if (currentSymbol == inputSymbol && currentSymbol == "$$") {
            // Fin del análisis
            return;
        } else if (currentSymbol == inputSymbol) {
            // avanzar en la entrada y la pila
            parseStack.pop();
            pos++;
        } else if (is_uppercase(currentSymbol) && parsingTable[currentSymbol].find(inputSymbol) != parsingTable[currentSymbol].end()) {

            parseStack.pop();
            string production = parsingTable[currentSymbol][inputSymbol].production;

            std::cout << "production: " << production << endl;
            for (int i = production.size()-2; i >= 0; i-=2)
            {
                string production_test = production.substr(i, 2); 

                if (production_test != "  ")
                {
                    parseStack.push(production_test);
                }
            }
        } else {
            cout << endl << "[!] Error de sintaxis - Recorriendo el stack 1 elemento" ;
            string error = currentSymbol;
            string context = "Error de sintaxis en la linea " + to_string(input_tokens[pos].lineIndex) + ": ...'" + input_tokens[pos - 1].value + "->...'";

            // Recuperación de errores (Current es Terminal)
            if(is_valid_terminal(currentSymbol)){
                
                parseStack.pop();

                cout << "(Terminal)" << endl << endl;
                // string error = currentSymbol;
                // string context = "Error de sintaxis en la linea " + to_string(input_tokens[pos].lineIndex) + ": ";
                errorManager.add_error(error, context);
            }
            // Recuperación de errores (Current es No Terminal)
            else{
                
                cout << "(No Terminal)" << endl << endl;

                if(errorManager.findFollow(currentSymbol, inputSymbol))
                    parseStack.pop();
                else
                {
                    
                    if (pos == input_tokens.size() - 1)
                    {
                        errorManager.add_error(error, context);
                        return;
                    }
                    do{
                        pos++;
                        inputSymbol = input_tokens[pos].get_string(); // next character of input
                        // std::cout << "finding: " << inputSymbol << " " << pos << " " << input_tokens.size() << std::endl;
                    }while(pos < input_tokens.size() - 1 && !errorManager.findFollow(currentSymbol, inputSymbol));
                }

                errorManager.add_error(error, context);

            }
        }
    }

    return;
}

#endif // PARSER_CPP