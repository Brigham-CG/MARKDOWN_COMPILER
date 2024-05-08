#include <iostream>

using namespace std;

#ifndef TOKEN_H
#define TOKEN_H

enum token_type {

    I_TITULO,  //'<h1>'
    F_TITULO, //'</h1>'

    I_SUBTITULO, //'<h2>'
    F_SUBTITULO, //'</h2>'

    I_SUBSUBTITULO, //'<h3>'
    F_SUBSUBTITULO, //'</h3>'

    I_PARRAFO,  //'<p>'
    F_PARRAFO, //'</p>'

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

    END_OF_FILE, //$$

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
        string get_string();
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

string Token::get_string()
{
    if(type == I_TITULO)
        return "1t";
    if(type == F_TITULO)
        return "2t";
    else if(type == I_SUBTITULO)
        return "1s";
    else if(type == F_SUBTITULO)
        return "2s";
    else if(type == I_SUBSUBTITULO)
        return "1z";
    else if(type == F_SUBSUBTITULO)
        return "2z";
    else if(type == I_PARRAFO)
        return "1p";
    else if(type == F_PARRAFO)
        return "2p";
    else if(type == WORD)
        return "wo";
    else if (type == SALTO_DE_LINEA)
        return "/n";
    else if (type == I_NEGRITA)
        return "1*";
    else if (type == F_NEGRITA)
        return "2*";
    else if (type == I_TACHADO)
        return "1_";
    else if (type == F_TACHADO)
        return "2_";
    else if (type == I_CURSIVA)
        return "1$";
    else if (type == F_CURSIVA)
        return "2$";
    else if (type == ROJO)
        return "ro";
    else if (type == AMARILLO)
        return "am";
    else if (type == AZUL)
        return "az";
    else if (type == I_OPCION)
        return "<o";
    else if (type == F_OPCION)
        return ">o";
    else if (type == I_COLOR)
        return "(c";
    else if (type == F_COLOR)
        return ")c";
    else if (type == I_FUENTE)
        return "[f";
    else if (type == F_FUENTE)
        return "]f";
    else if (type == ARIAL)
        return "ar";
    else if (type == TIMES)
        return "ti";
    else if (type == COURIER)
        return "co";
    else if (type == HELVETICA)
        return "he" ;
    else if (type == I_URL)
        return "{u";
    else if (type == F_URL)
        return "}u";
    else if (type == END_OF_FILE)
        return "$$";
    return "  ";
}

void Token::print() {

    std::cout << "TYPE: '";
    if(type == I_TITULO)
        std::cout << "I_TITULO' ";
    else if(type == F_TITULO)
        std::cout << "F_TITULO' ";
    else if(type == I_SUBTITULO)
        std::cout << "I_SUBTITULO' ";
    else if(type == F_SUBTITULO)
        std::cout << "F_SUBTITULO' ";
    else if(type == I_SUBSUBTITULO)
        std::cout << "I_SUBSUBTITULO' ";
    else if(type == F_SUBSUBTITULO)
        std::cout << "F_SUBSUBTITULO' ";
    else if(type == I_PARRAFO)
        std::cout << "I_PARRAFO' ";
    else if(type == F_PARRAFO)
        std::cout << "F_PARRAFO' ";
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
    else if (type == UNKNOW)
        std::cout << "UNKNOW' ";
    else if (type == END_OF_FILE)
        std::cout << "END_OF_FILE' ";


    //std::cout << "VALUE: '" << value <<"'\n";
    cout << "VALUE: '" << value << "' << LINE: " << lineIndex << "\n";
}

Token::~Token(){}

#endif // TOKEN_H