#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <unordered_set>
#include "token.cpp"
#include "tools.cpp"

#ifndef SCANNER_CPP
#define SCANNER_CPP

using namespace std;

// ####################################### AUXILIAR FUNCTIONS ################################################

std::string reference_text = "abcdefghijklmnopqrstuvwxyz";
std::string reference_number = "1234567890";
std::string reference_special = "*\\_$<>()[]|";

// ####################################### SCANNER CLASS ################################################

class scanner {
    private:
        string text;
        vector<Token> tokens;

        void process_text();
        void recognize_token(int &index, vector<Token> &stack);
        char get_char(int &index);
        char peek_char(int index);
        int getNumberOfLine(int index);
        bool findToken( token_type type, vector<Token> stack);

        void get_eol(char character, int &index);
        void skip_comment(char character, int &index);
        void get_titles(char character, int &index);
        void get_paragraph(char character, int &index);
        void get_special(token_type type_init, token_type type_last, vector<Token> &stack, string character, int index);
        void get_bar_table(int index);
        typedef token_type (scanner::*selectFunction)(const string&, int);
        void get_init_option(token_type type_init, token_type type_last, string init_char, string last_char, vector<Token> &stack, int &index, selectFunction select_type);
        token_type select_color(const string& color, int index);
        token_type select_font(const string& font, int index);
        token_type url_detector(const string& url, int index);
        void get_close_option(vector<Token> &stack, int index);
        void get_word(char character, int &index);
        void get_close(char character, int &index);

        void collect_token(token_type type, string symbol, int index);

        string collect_word(int &index);

    public:
        scanner(string fileName);                   // Constructor
        vector<Token> get_tokens();                 // Get tokens
};

// Constructor: Lee el archivo y guarda el texto en la variable text
scanner::scanner(string fileName) {
    text = read_file(fileName);
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
        get_special(I_CURSIVA, F_CURSIVA, stack, "$", index);
    }
    // * Opciones (Titulos, Subtitulos, Subsubtitulos, Color, Fuente, URL)
    else if (character == '<') 
    {
        char next_char = peek_char(index);
        
        // * Titulos - Subtitulos - Subsubtitulos
        if(next_char == 'h'){
            get_titles(character, index);
        }
        // * Parrafo
        else if(next_char == 'p'){
            get_paragraph(character, index);
        }
        else if(next_char == '/')
        {
            get_close(character, index);
        }
        else
        {
            // -> Añadimos token de INICIO DE OPCION
            collect_token(I_OPCION, "<", index);   
            
            stack.push_back(Token(I_OPCION, "<", getNumberOfLine(index)));

            // * Color: <(color) word>
            if(next_char == '(') {
                get_init_option(I_COLOR, F_COLOR, "(", ")", stack, index, &scanner::select_color);  
            }
            // * Fuente: <[font] word>
            else if(next_char == '[') {
                get_init_option(I_FUENTE, F_FUENTE, "[", "]", stack, index, &scanner::select_font);
            }
            // * URL: <{url}(word)>
            else if(next_char == '{') {
                get_init_option(I_URL, F_URL, "{", "}", stack, index, &scanner::url_detector);
            }

        }
        // * Cerrar OPCION (</)
    }
    // * Opciones CERRAR
    else if(character == '>')
    {
        get_close_option(stack, index);
    }
    // * Tabla
    else if (character == '|')
    {
        get_bar_table(index);
    }
    // * Palabra
    else
    {
        get_word(character, index);
    }
}

// Metodo: Token - SALTO DE LINEA
void scanner::get_eol(char character, int &index)
{
    collect_token(SALTO_DE_LINEA, "\n", index);
}

// Metodo: Saltar comentarios
void scanner::skip_comment(char character, int &index)
{
    char next_char = peek_char(index);
    
    if(next_char == '/') { // is_comment
        do{
            character = get_char(index);
        } while(character != '\0' && character != '\n'); // Saltar hasta el final de la línea (\n)
        
        std::cout << "Debug Scan Comment skipped\n";
    }
    else{   // Its a word/text
        get_word(character, index);
    }
}

// Metodo: Token Titulos - (I_TITULO, I_SUBTITULO, I_SUBSUBTITULO)
void scanner::get_titles(char character, int &index)
{
    index++;
    character = get_char(index);
    
    token_type t_type; 
    string c_type;
    c_type = character;
    if(character == '1')// * Es un subtítulo o subsubtitulo
        t_type = I_TITULO;
    else if(character == '2')// * Es un subsubtitulo
        t_type = I_SUBTITULO;
    else if(character == '3')// * Es un subsubtitulo
        t_type = I_SUBSUBTITULO;
    else // error
    {
        collect_token(UNKNOW, "<h", index);
        return;
    } 

    character = get_char(index);
    
    if(character == '>')
        collect_token(t_type, "<h"+c_type+">", index);
}

// Metodo: Token Parrafo - (I_PARRAFO)
void scanner::get_paragraph(char character, int &index)
{
    index++;
    character = get_char(index);    
    
    if(character == '>')
        collect_token(I_PARRAFO, "<p>", index);
    else{
        //error
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

void scanner::get_close(char character, int &index)
{
    index++;
    character = get_char(index);
    
    if(character == 'p') 
    {
        character = get_char(index);
        if(character == '>')
            collect_token(F_PARRAFO, "</p>", index);
    }
    else if(character == 'h')
    {
        character = get_char(index);

        string c_type;

        token_type t_type;
        if(character == '1')
        {
            t_type = F_TITULO;
        }
        else if(character == '2')
        {
            t_type = F_SUBTITULO;
        }
        else if(character == '3')
        {
            t_type = F_SUBSUBTITULO;
        }
        else {
            //error
        }
        c_type = character;

        character = get_char(index);

        if(character != '>')
        {
            cout << "[!] Error de cerrado en la linea: " << endl;
            // error
            return;
        }

        // Print index"
        cout << "Index: " << index << " - " << getNumberOfLine(index) << endl;

        collect_token(t_type, "</h"+c_type+">", index);
    }
    else{
        //error
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
    //  // -> Añadimos token de INICIO DE OPCION
    // collect_token(I_OPCION, "<", index);   
    
    // index++;
    // stack.push_back(Token(I_OPCION, "<", getNumberOfLine(index)));

    index++;
    // -> Añadimos token de INICIO DE COLOR
    Token token_i_c(type_init, init_char, getNumberOfLine(index));
    tokens.push_back(token_i_c);

    // Collect token option
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

// Metodo: Devuelve los tokens
vector<Token> scanner::get_tokens() {
    process_text();
    return tokens;
}

// Metodo: Devuelve el caracter en la posición index y avanza el puntero
char scanner::get_char(int &index){
    index++;
    return text[index-1];
}

// Metodo: Devuelve el caracter en la posición index
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

#endif // SCANNER_CPP