#include <iostream>
#include <vector>

#include "markdown/scanner.cpp"
#include "markdown/parser.cpp"
#include "markdown/token.cpp"

using namespace std;

// ########################################## MAIN FUNCTION ##############################################
int main() {
    cout << "-----------SCANNER----------\n\n"; 
    scanner scan("texto.markdown");
    vector<Token> tokens = scan.get_tokens();

    cout << "\n\n-----------PARSER----------\n\n"; 

    Parser pars(tokens);
}
