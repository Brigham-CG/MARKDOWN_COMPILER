#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <map>

using namespace std;

// ####################################### AUXILIAR FUNCTIONS ################################################

string read_file(string file_path)
{
    std::ifstream file(file_path);   

    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo: " << file_path << std::endl;
        return ""; 
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    file.close();
    
    return content;
}

std::string reference_text = "abcdefghijklmnopqrstuvwxyz";
std::string reference_number = "1234567890";
std::string reference_special = "*\\_$";

enum token_type {

    I_TITULO,  //'#'
    I_SUBTITULO, //'##'
    I_SUBSUBTITULO, //'###'

    I_NEGRITA, //'*'
    F_NEGRITA, //'*'

    I_CURSIVA, //'$'
    F_CURSIVA, //'$'

    I_TACHADO, //'_'
    F_TACHADO, //'_'

    I_OPCION, //'<'
    F_OPCION, //'>'

    I_COLOR, //'(
    F_COLOR, //')'

    I_FUENTE, //'['
    F_FUENTE, //']'

    ESPACIO, //' '
    SALTO_DE_LINEA, //'\n'    

    LETRA, //[a-zA-Z0-9]
    WORD, // //[a-zA-Z0-9]

    ROJO, //'rojo'
    AMARILLO, //'amarillo'
    AZUL, //'azul'
    RGB, //'rgb'
};

// ####################################### TOKEN CLASS ################################################

class Token
{
    private:
        token_type type;
        string value; 

    public:
        Token(token_type i_type, string i_value);
        void print();
        ~Token();

};

Token::Token(token_type i_type, string i_value)
{
    type = i_type;
    value = i_value;
}

void Token::print() {
    std::cout << "TYPE: '";
    if(type == I_TITULO)
        std::cout << "I_TITULO' ";
    else if(type == I_SUBTITULO)
        std::cout << "I_SUBTITULO' ";
    else if(type == I_SUBSUBTITULO)
        std::cout << "I_SUBSUBTITULO' ";
    else if(type == WORD)
        std::cout << "WORD' ";
    else if (type == SALTO_DE_LINEA)
        std::cout << "SALTO_DE_LINEA' ";
    else if (type == I_NEGRITA)
        std::cout << "I_NEGRITA' ";
    else if (type == F_NEGRITA)
        std::cout << "F_NEGRITA' ";
    else if (type == I_TACHADO)
        std::cout << "I_TACHADO' ";
    else if (type == F_TACHADO)
        std::cout << "F_TACHADO' ";
    else if (type == I_CURSIVA)
        std::cout << "I_CURSIVA' ";
    else if (type == F_CURSIVA)
        std::cout << "F_CURSIVA' ";

    std::cout << "VALUE: '" << value <<"'\n";
}

Token::~Token(){}

// ####################################### SCANNER CLASS ################################################

class scanner
{
    private:
        string text;
        vector<Token> tokens;
        char last_char;

        void process_text();
        void recognize_token(int &index, vector<token_type> &stack);
        char get_char(int &index);
        char peek_char(int index);

        bool is_comment(int &index);
        void skip_comment(int &index);

        string collect_word(int &index);

    public:
        scanner(string fileName);                   // Constructor
        ~scanner();

        vector<Token> get_tokens();                 // Get tokens

};

scanner::scanner(string fileName) {
    text = read_file(fileName);
    last_char = '\n';
}

void scanner::process_text() {   

    cout << endl << "[+] Text size: " << text.size() << endl << endl;

    int index = 0;                      // Puntero al caracter actual
    int end_index = text.size();        // Puntero al final del texto
    vector<token_type> stack;

    while (index < end_index) {   
        recognize_token(index, stack);
    }

    if(!stack.empty()) {
        //error
        std::cout << "error\n";
    }
}

void scanner::recognize_token(int &index, vector<token_type> &stack)
{
    char character = get_char(index);

    // * Espacios en blanco
    if(character == ' ') {
        last_char = character;
        return;
    }

    // * Salto de línea
    else if(character == '\n') {

        last_char = character;
        
        Token token(SALTO_DE_LINEA, "\n");
        tokens.push_back(token);
        cout << "Debug Scan Token collected - ";
        token.print();
    }

    // * Comentarios
    else if(character == '/') {
        char next_char = peek_char(index);
        
        if(next_char == '/') { // is_comment
            skip_comment(index);
            std::cout << "Debug Scan Comment skipped\n";
            last_char = '\n';
        }
        else{   // Its a word/text
            string word;
            word  += character;
            word += collect_word(index);

            Token token(WORD, word);
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
    }
    
    // * Titulos - Subtitulos - Subsubtitulos
    else if(last_char == '\n' && character == '#') {
        char next_char = peek_char(index);
        
        if(next_char == '#') {                              // * Es un subtítulo o subsubtitulo
            index++;
            character = next_char;

            next_char= peek_char(index);
            
            if(next_char == '#') {                          // * Es un subsubtitulo
                index++;
                last_char = next_char;

                Token token(I_SUBSUBTITULO, "###");
                tokens.push_back(token);
                cout << "Debug Scan Token collected - ";
                token.print();
                
                return;
            }

            else {                                          // * Es un subtitulo
                last_char = character;

                Token token(I_SUBTITULO, "##");
                tokens.push_back(token);
                cout << "Debug Scan Token collected - ";
                token.print();
                return;
            }
        }

        else {                                              // * Es un titulo
            last_char = '#';
            
            Token token(I_TITULO, "#");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
            return;
        }
    }
    
    // * Negrita 
    else if(character == '*') {
        auto it = std::find(stack.begin(), stack.end(), I_NEGRITA);
        if(it != stack.end()) // fin
        {
            stack.erase(it);
            Token token(F_NEGRITA, "*");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
        else // inicio
        {
            stack.push_back(I_NEGRITA);
            Token token(I_NEGRITA, "*");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
        
    }
    
    else if(character == '_') // tachado
    {
        auto it = std::find(stack.begin(), stack.end(), I_TACHADO);
        if(it != stack.end()) // fin
        {
            stack.erase(it);
            Token token(F_TACHADO, "_");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
        else // inicio
        {
            stack.push_back(I_TACHADO);
            Token token(I_TACHADO, "_");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
    }
    
    else if(character == '$') // tachado
    {
        auto it = std::find(stack.begin(), stack.end(), I_CURSIVA);
        if(it != stack.end()) // fin
        {
            stack.erase(it);
            Token token(F_CURSIVA, "$");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
        else // inicio
        {
            stack.push_back(I_CURSIVA);
            Token token(I_CURSIVA, "$");
            tokens.push_back(token);
            cout << "Debug Scan Token collected - ";
            token.print();
        }
    }
    
    else // word
    {
        string word;
        word += character;
        word += collect_word(index);
        Token token(WORD, word);
        tokens.push_back(token);
        cout << "Debug Scan Token collected - ";
        token.print();
    }
}

vector<Token> scanner::get_tokens() {
    process_text();
    return tokens;
}

// Get char: Devuelve el caracter en la posición index y avanza el puntero
char scanner::get_char(int &index){
    index++;
    return text[index-1];
}

// Peek char: Devuelve el caracter en la posición index
char scanner::peek_char(int index){   
    return text[index];
}

void scanner::skip_comment(int &index)
{
    char character;
    do{
        character = get_char(index);
    } while(character != '\0' && character != '\n');

    // if(character == '\n')
    // {
    //     if(peek_char(index) != '\0')
    //     {
    //         Token token(SALTO_DE_LINEA, "\n");
    //         tokens.push_back(token);
    //     }
    // }
}

string scanner::collect_word(int &index)
{
    char character;

    string word;

    while(true)
    {
        character = peek_char(index);

        if(character == '\\') // especials
        {
            index++;
            char next_char = peek_char(index);
            auto found = reference_special.find(character);

            if(found != std::string::npos)
            {
                index++;
                word += next_char;
                last_char = next_char;
                continue;
            }
            else
            {
                // error
            }
        }
        if(character == ' ' || character == '\0' || character == '\n' || character == '*')
        {
            break;
        }
        word+=character;
        last_char = character;
        index++;
    }
    return word;
}

scanner::~scanner(){}

// ########################################## MAIN FUNCTION ##############################################3
int main() {
    scanner scan("texto.txt");
    scan.get_tokens();
}