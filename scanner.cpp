#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <regex>

using namespace std;

// ####################################### AUXILIAR FUNCTIONS ################################################

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


std::string reference_text = "abcdefghijklmnopqrstuvwxyz";
std::string reference_number = "1234567890";
std::string reference_special = "*\\_$<>()[]|";

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

    I_URL, //'{'
    F_URL, //'}'

    BAR_TABLE, //'|'

    SALTO_DE_LINEA, //'\n'    

    WORD, // //[a-zA-Z0-9]

    ROJO, //'rojo'
    AMARILLO, //'amarillo'
    AZUL, //'azul'
    RGB, //'rgb'

    ARIAL, //'arial'
    TIMES, //'times'
    COURIER, //'courier'
    HELVETICA, //'helvetica'

    UNKNOW, // ninguno de los demas

};

// ####################################### TOKEN CLASS ################################################

class Token
{
    public:
        token_type type;
        string value; 
        int lineIndex;

        Token(token_type i_type, string i_value);                   // Constructor
        Token(token_type i_type, string i_value, int i_lineIndex);  // Constructor
        void print();
        char get_char();
        ~Token();

};

Token::Token(token_type i_type, string i_value)
{
    type = i_type;
    value = i_value;
}

Token::Token(token_type i_type, string i_value, int i_lineIndex)
{
    type = i_type;
    value = i_value;
    lineIndex = i_lineIndex;
}

char Token::get_char()
{
    if(type == I_TITULO)
        return 'T';
    else if(type == I_SUBTITULO)
        return 'S';
    else if(type == I_SUBSUBTITULO)
        return 'Z';
    else if(type == WORD)
        return 'W';
    else if (type == SALTO_DE_LINEA)
        return 'N';
    else if (type == I_NEGRITA)
        return '1';
    else if (type == F_NEGRITA)
        return '2';
    else if (type == I_TACHADO)
        return '3';
    else if (type == F_TACHADO)
        return '4';
    else if (type == I_CURSIVA)
        return '5';
    else if (type == F_CURSIVA)
        return '6';
    else if (type == ROJO)
        return 'R';
    else if (type == AMARILLO)
        return 'Y';
    else if (type == AZUL)
        return 'B';
    else if (type == I_OPCION)
        return '<';
    else if (type == F_OPCION)
        return '>';
    else if (type == I_COLOR)
        return '(';
    else if (type == F_COLOR)
        return ')';
    else if (type == I_CURSIVA)
        return '[';
    else if (type == F_CURSIVA)
        return ']';
    else if (type == ARIAL)
        return 'A';
    else if (type == TIMES)
        return 'M';
    else if (type == COURIER)
        return 'C';
    else if (type == HELVETICA)
        return 'H' ;
    else if (type == I_URL)
        return '{';
    else if (type == F_URL)
        return '}';
    return ' ';
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
    else if (type == ROJO)
        std::cout << "ROJO' ";
    else if (type == AMARILLO)
        std::cout << "AMARILLO' ";
    else if (type == AZUL)
        std::cout << "AZUL' ";
    else if (type == RGB)
        std::cout << "RGB' ";
    else if (type == I_OPCION)
        std::cout << "I_OPCION' ";
    else if (type == F_OPCION)
        std::cout << "F_OPCION' ";
    else if (type == ARIAL)
        std::cout << "ARIAL' ";
    else if (type == TIMES)
        std::cout << "TIMES' ";
    else if (type == COURIER)
        std::cout << "COURIER' ";
    else if (type == HELVETICA)
        std::cout << "HELVETICA' ";
    else if (type == I_URL)
        std::cout << "I_URL' ";
    else if (type == F_URL)
        std::cout << "F_URL' ";
    else if (type == BAR_TABLE)
        std::cout << "BAR_TABLE' ";


    //std::cout << "VALUE: '" << value <<"'\n";
    cout << "VALUE: '" << value << "' << LINE: " << lineIndex << "\n";
}

Token::~Token(){}

// ####################################### SCANNER CLASS ################################################

class scanner {
    private:
        string text;
        vector<Token> tokens;
        char last_char;

        void process_text();
        void recognize_token(int &index, vector<Token> &stack);
        char get_char(int &index);
        char peek_char(int index);
        int getNumberOfLine(int index);
        bool findToken( token_type type, vector<Token> stack);

        void get_eol(char character, int &index);
        void skip_comment(char character, int &index);
        void get_titles(char character, int &index);
        void get_special(token_type type_init, token_type type_last, vector<Token> &stack, string character, int index);
        void get_bar_table(int index);
        typedef token_type (scanner::*selectFunction)(const string&, int);
        void get_init_option(token_type type_init, token_type type_last, string init_char, string last_char, vector<Token> &stack, int &index, selectFunction select_type);
        token_type select_color(const string& color, int index);
        token_type select_font(const string& font, int index);
        token_type url_detector(const string& url, int index);
        void get_close_option(vector<Token> &stack, int index);
        void get_word(char character, int &index);

        void collect_token(token_type type, string symbol, int index);

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
    
    //vector<token_type> stack;
    vector<Token> stack;

    while (index < end_index) {   
        recognize_token(index, stack);
    }

    if(!stack.empty()) { // Errores: Debemos identificar en que linea se encuentra el error
        for(int i = 0; i < stack.size(); i++){
            cout << endl << "[!] Error: "; stack[i].print() ;
        }
    }
}

void scanner::recognize_token(int &index, vector<Token> &stack) {
    char character = get_char(index);

    // * Saltar espacios en blanco
    if(character == ' ') {
        last_char = character;
        return;
    }

    // * Salto de línea
    else if(character == '\n') {
        get_eol(character, index);
    }

    // * Saltar comentarios
    else if(character == '/') {
        skip_comment(character, index);
    }
    
    // * Titulos - Subtitulos - Subsubtitulos
    else if(last_char == '\n' && character == '#') {
        get_titles(character, index);
    }
    
    // * Negrita 
    else if(character == '*') {
        get_special(I_NEGRITA,F_NEGRITA, stack, "*", index);
    }
    
    // * Tachado
    else if(character == '_') {
        get_special(I_TACHADO, F_TACHADO, stack, "_", index);
    }
    
    // * Cursiva
    else if(character == '$'){
        get_special(I_TACHADO, F_TACHADO, stack, "*", index);
    }
    
    // Color, Fuente, URL: 
    else if (character == '<') 
    {
        char next_char = peek_char(index);
        
        // * Color: <(color) word>
        if(next_char == '(') {
            get_init_option(I_COLOR, F_COLOR, "(", ")", stack, index, &scanner::select_color);  
        }

        // * Fuente: <[font] word>
        else if(next_char == '[') {
            get_init_option(I_FUENTE, F_FUENTE, "[", "]", stack, index, &scanner::select_font);
        }
        // * URL: <{url}(word)>
        else if(next_char == '{') 
        {
            get_init_option(I_URL, F_URL, "{", "}", stack, index, &scanner::url_detector);
        }
    }
    else if(character == '>') // * CLOSE OPTION
    {
        get_close_option(stack, index);
    }
    else if (character == '|') // * TABLE
    {
        get_bar_table(index);
    }
    else // * Word
    {
        get_word(character, index);
    }
}

void scanner::get_eol(char character, int &index)
{
    last_char = character;
    collect_token(SALTO_DE_LINEA, "\n", index);
}

void scanner::skip_comment(char character, int &index)
{
    char next_char = peek_char(index);
    
    if(next_char == '/') { // is_comment
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
        std::cout << "Debug Scan Comment skipped\n";
        last_char = '\n';
    }
    else{   // Its a word/text
        get_word(character, index);
    }
}

void scanner::get_titles(char character, int &index)
{
    char next_char = peek_char(index);
    
    if(next_char == '#') {                              // * Es un subtítulo o subsubtitulo
        index++;
        character = next_char;

        next_char= peek_char(index);
        
        if(next_char == '#') {                          // * Es un subsubtitulo
            index++;
            last_char = next_char;
            collect_token(I_SUBSUBTITULO, "###", index);
            return;
        }

        else {                                          // * Es un subtitulo
            last_char = character;

            collect_token(I_SUBTITULO, "##", index);    
            
            return;
        }
    }
    else {                                              // * Es un titulo
        last_char = '#';
        collect_token(I_TITULO, "#", index);
        return;
    }
}

void scanner::get_special(token_type type_init, token_type type_last, vector<Token> &stack, string character, int index)
{
    // * Buscamos si existe dentro del stack algun token de tipo I_TACHADO
    if(findToken(type_init, stack)){         // Si existe, lo eliminamos
        stack.erase(stack.begin() + stack.size() - 1);
        collect_token(type_last, character, index);
    }
    else{                                   // Si no existe, lo agregamos
        stack.push_back(Token(type_init, character, getNumberOfLine(index)));
        collect_token(type_init, character, index);
    }
}

void scanner::get_bar_table(int index)
{
    collect_token(BAR_TABLE, "|", index);
}

void scanner::get_init_option(
    token_type type_init, token_type type_last,
    string init_char, string last_char,
    vector<Token> &stack, int &index,
    selectFunction select_type)
{
     // -> Añadimos token de INICIO DE OPCION
    collect_token(I_OPCION, "<", index);   
    
    index++;
    stack.push_back(Token(I_OPCION, "<", getNumberOfLine(index)));

    // -> Añadimos token de INICIO DE COLOR
    Token token_i_c(type_init, init_char, getNumberOfLine(index));
    tokens.push_back(token_i_c);

    // Collect color word
    string select;
    select += collect_word(index);

    token_type t_type = (this->*select_type) (select, index);

    collect_token(t_type, select, index);
    
    // -> Añadimos token de FIN DE COLOR
    string character;
    character += get_char(index);
    if(character == last_char)
    {
        Token token_f_c(type_last, last_char, getNumberOfLine(index));
        tokens.push_back(token_f_c);
    }
    else
    {
        cout << "[?] Error: No se cerro en la linea: " << getNumberOfLine(index) << endl;
    }
}

token_type scanner::select_color(const string& color, int index)
{
    token_type t_type;

    if(color == "rojo")
        t_type = ROJO;
    else if(color == "amarillo")
        t_type = AMARILLO;
    else if(color == "azul")
        t_type = AZUL;
    else if(color == "rgb")
        t_type = RGB;
    else{
        cout << "[?] Error: Color no reconocido en la linea: " << getNumberOfLine(index) << endl;
        t_type = UNKNOW;
    }
    return t_type;
}

token_type scanner::select_font(const string& font, int index)
{
    token_type t_type;

    if(font == "arial")
        t_type = ARIAL;
    else if(font == "times")
        t_type = TIMES;
    else if(font == "courier")
        t_type = COURIER;
    else if(font == "helvetica")
        t_type = HELVETICA;
    else
    {
        cout << "[?] Error: Fuente no reconocida en la linea: " << getNumberOfLine(index) << endl;
        t_type = UNKNOW; 
    }
    return t_type;
}

token_type scanner::url_detector(const string& url, int index)
{

    token_type t_type = WORD;

    if(!isURLValid(url))
    {
        t_type = UNKNOW;
        cout << "[?] Error: URL no valida en la linea: " << getNumberOfLine(index) << endl;                
    }
    return t_type;
}

void scanner::get_close_option(vector<Token> &stack, int index)
{
    if(findToken(I_OPCION, stack))
    {
        stack.erase(stack.begin() + stack.size() - 1);
        collect_token(F_OPCION, ">", index);
    }
    else
    {
        cout << "[?] Error: No se abrio una opcion en la linea: " << getNumberOfLine(index) << endl;
    }
}

void scanner::get_word(char character, int &index)
{
    string word;
    word += character;
    word += collect_word(index);

    collect_token(WORD, word,index);
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
        if(character == ' ' || character == '\0' || character == '\n' ||
            character == '*' || character == '$' || character == '_' ||
            character == '<' || character == '>' ||
            character == '(' || character == ')' ||
            character == '[' || character == ']' ||
            character == '{' || character == '}' || 
            character == '|' )
        {
            break;
        }
        word+=character;
        last_char = character;
        index++;
    }
    return word;
}

int scanner::getNumberOfLine(int index){
    int line = 1;
    for(int i = 0; i < index; i++){
        if(text[i] == '\n'){
            line++;
        }
    }
    return line;
}

bool scanner::findToken( token_type type, vector<Token> stack){
    for(int i = 0; i < stack.size(); i++){
        if(stack[i].type == type){
            return true;
        }
    }
    return false;
}

void scanner::collect_token(token_type type, string symbol, int index)
{
    Token token(type, symbol, getNumberOfLine(index));
    tokens.push_back(token);
    cout << "Debug Scan Token collected - ";
    token.print();   
}

scanner::~scanner(){}


// ########################################## PARSER ########################################

struct ProductionRule {
    char nonTerminal;
    string production;
};


class Parser
{
    private:
        void initializeParsingTable();
        unordered_map<char, unordered_map<char, ProductionRule>> parsingTable;
    public:
        Parser(vector<Token> input_tokens);
        bool parsing_ll1(vector<Token> tokens);
        bool is_valid_terminal(char character);
};

Parser::Parser(vector<Token> input_tokens)
{   
    initializeParsingTable();

    if(parsing_ll1(input_tokens))
        cout<<"[+] El codigo fuente fue correctamente parseado!"<<endl;
    else
        cout<<"[-] El codigo fuente es incorrecto!"<<endl;
}

bool Parser::is_valid_terminal(char character) {
    // Lista de terminales válidos según la función get_char() de la clase Token
    const string validTerminals = "TSZW123456RYBN<>()[]AMCH{}";

    // Verifica si el carácter está presente en la lista de terminales válidos
    return validTerminals.find(character) != string::npos;
}

void Parser::initializeParsingTable()
{
    // table here
}

bool Parser::parsing_ll1(vector<Token> input_tokens)
{
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('d'); 

    size_t pos = 0;
    char currentSymbol = parseStack.top();
    char inputSymbol = input_tokens[pos].get_char();

    while (!parseStack.empty()) {
        currentSymbol = parseStack.top();
        inputSymbol = input_tokens[pos].get_char();

        if (currentSymbol == inputSymbol && currentSymbol == '$') {
            // Fin del análisis
            return true;
        } else if (currentSymbol == inputSymbol) {
            // avanzar en la entrada y la pila
            parseStack.pop();
            pos++;
        } else if (is_valid_terminal(currentSymbol) && parsingTable[currentSymbol].find(inputSymbol) != parsingTable[currentSymbol].end()) {
            parseStack.pop();
            string production = parsingTable[currentSymbol][inputSymbol].production;
            for (int i = production.size() - 1; i >= 0; --i) {
                if (production[i] != ' ') {
                    parseStack.push(production[i]);
                }
            }
        } else {
            // Error de sintaxis
            return false;
        }
    }
    return false;
}

// ########################################## MAIN FUNCTION ##############################################
int main() {
    scanner scan("texto.txt");
    vector<Token> tokens = scan.get_tokens();

    Parser pars(tokens);
}