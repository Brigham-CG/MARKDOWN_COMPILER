#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <unordered_set>
#include <stack>
#include "token.cpp"
#include "tools.cpp"

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
        bool parsing_ll1(vector<Token> tokens);
        bool is_valid_terminal(string character);
};

Parser::Parser(vector<Token> input_tokens)
{   
    initializeParsingTable();

    if(parsing_ll1(input_tokens))
        cout<<"[+] El codigo fuente fue correctamente parseado!"<<endl;
    else
        cout<<"[-] El codigo fuente es incorrecto!"<<endl;
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
    parsingTable["DO"]["1p"] = {"DO", "BL"};
    parsingTable["DO"]["1t"] = {"DO", "BL"};
    parsingTable["DO"]["1s"] = {"DO", "BL"};
    parsingTable["DO"]["1z"] = {"DO", "BL"};
    parsingTable["DO"]["/n"] = {"DO", "BL"};
    parsingTable["DO"]["$$"] = {"DO", "BL"};

    parsingTable["BL"]["1p"] = {"BL", "1pTE2pBL"};
    parsingTable["BL"]["1t"] = {"BL", "1tTE2tBL"};
    parsingTable["BL"]["1s"] = {"BL", "1sTE2sBL"};
    parsingTable["BL"]["1z"] = {"BL", "1zTE2zBL"};
    parsingTable["BL"]["/n"] = {"BL", "/nBL"};
    parsingTable["BL"]["$$"] = {"BL", "  "};

    parsingTable["TE"]["2p"] = {"TE", "  "};
    parsingTable["TE"]["2t"] = {"TE", "  "};
    parsingTable["TE"]["2s"] = {"TE", "  "};
    parsingTable["TE"]["2z"] = {"TE", "  "};
    parsingTable["TE"]["/n"] = {"TE", "/nTE"};
    parsingTable["TE"]["wo"] = {"TE", "woTE"};
    parsingTable["TE"]["1*"] = {"TE", "TSTE"};
    parsingTable["TE"]["2*"] = {"TE", "  "};
    parsingTable["TE"]["1+"] = {"TE", "TSTE"};
    parsingTable["TE"]["2+"] = {"TE", "  "};
    parsingTable["TE"]["1_"] = {"TE", "TSTE"};
    parsingTable["TE"]["2_"] = {"TE", "  "};
    parsingTable["TE"]["<o"] = {"TE", "TSTE"};
    parsingTable["TE"][">o"] = {"TE", "  "};

    parsingTable["TS"]["1*"] = {"TS", "1*TE2*"};
    parsingTable["TS"]["1+"] = {"TS", "1+TE2+"};
    parsingTable["TS"]["1_"] = {"TS", "1_TE2_"};
    parsingTable["TS"]["<o"] = {"TS", "<oOP>o"};

    parsingTable["OP"]["(c"] = {"OP", "(cCO)cTE"};
    parsingTable["OP"]["[f"] = {"OP", "[fFU]fTE"};
    parsingTable["OP"]["{u"] = {"OP", "{uwo}uTE"};

    parsingTable["CO"]["ro"] = {"CO", "ro"};
    parsingTable["CO"]["az"] = {"CO", "az"};

    parsingTable["FU"]["ar"] = {"FU", "ar"};
    parsingTable["FU"]["ti"] = {"FU", "ti"};
    parsingTable["FU"]["co"] = {"FU", "co"};
    parsingTable["FU"]["he"] = {"FU", "he"};    
}

void print_tokens(vector<Token> input_tokens)
{
    for(int i = 0; i < input_tokens.size(); i++)
    {
        input_tokens[i].print();
    }
}

bool Parser::parsing_ll1(vector<Token> input_tokens)
{
    input_tokens.push_back(Token(END_OF_FILE, "$$", 0));
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
            return true;
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
            // Error de sintaxis
            return false;
        }
    }
    return false;
}

#endif // PARSER_CPP