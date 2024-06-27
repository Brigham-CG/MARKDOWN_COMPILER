#include <iostream>
#include <vector>

#include "lib/scanner.cpp"
#include "lib/parser.cpp"
#include "lib/token.cpp"
#include "lib/translator.cpp"

using namespace std;

// ########################################## MAIN FUNCTION ##############################################
int main() {
    cout << "-------------- SCANNER -------------\n"; 
    scanner scan("texto.markdown");
    vector<Token> tokens = scan.get_tokens();

    // Print tokens
    //cout << "\n\n----------- TOKENS ----------\n";
    //cout << endl << "> [DEBUG] Tokens Obtained:" << endl;
    //print_tokens(tokens);
    //cout << "> [DEBUG] END Tokens Obtained:" << endl;

    cout << "\n\n----------- PARSER ----------\n"; 

    Parser pars(tokens, "file.html");

    // cout << "\n\n----------- TRANSLATOR ----------\n";

    // Translator translator(tokens, "file.html");

}