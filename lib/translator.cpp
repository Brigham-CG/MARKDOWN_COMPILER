#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include "tools.cpp"
#include "token.cpp"

using namespace std;


class Translator
{
    string base_output =  R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Compilado</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            line-height: 1.6;
            background-color: #f4f4f9;
            color: #333;
        }
        
        h1, h2, h3 {
            color: #0056b3;
            margin-bottom: 10px;
        }
        
        h1 {
            border-bottom: 2px solid #0056b3;
            padding-bottom: 10px;
        }
        
        h2 {
            border-bottom: 1px solid #0056b3;
            padding-bottom: 8px;
        }
        
        h3 {
            border-bottom: 1px dashed #0056b3;
            padding-bottom: 6px;
        }
        
        p {
            margin-bottom: 15px;
        }
        
        b, strong {
            font-weight: bold;
        }
        
        em {
            font-style: italic;
        }
        
        s {
            text-decoration: line-through;
        }
        
        a {
            color: #007bff;
            text-decoration: none;
        }
        
        a:hover {
            text-decoration: underline;
        }
        
        .red {
            color: red;
        }
        
        .yellow {
            color: yellow;
        }
        
        .blue {
            color: blue;
        }
        
        .arial {
            font-family: 'Arial';
        }
        
        .times {
            font-family: 'Times New Roman';
        }
        
        .courier {
            font-family: 'Courier New';
        }
        
        .helvetica {
            font-family: Helvetica;
        }
    </style>
</head>
<body>
)";
    map<token_type, string> table;
    string exchange_token(vector<Token> tokens, int &index, stack<token_type> &stack_f_opt);
    string process_tokens(vector<Token> inpute);
    void init_exchange_table();
    public:
      
        Translator(vector<Token> input_tokens, string nameFile);
};


Translator::Translator(vector<Token> input_tokens, string nameFile)
{   
    init_exchange_table();
    string output = process_tokens(input_tokens);
    if (save_output(output, nameFile))
    {
        cout << "[+] Archivo generado\n";
        return;
    }
    cout << "[-] Hubo errores al guardar el archivo\n";
}

string Translator::process_tokens(vector<Token> tokens)
{
    vector<string> translated_tokens;
    stack<token_type> stack_f_opt;
    for(int i = 0; i < tokens.size(); i++)
    {
        translated_tokens.push_back(exchange_token(tokens, i, stack_f_opt));
    }

    string output = base_output;
    for(int i = 0; i < translated_tokens.size(); i++)
    {
        output+=translated_tokens[i]+ " ";
    }

    output += "\n</body>\n</html>";

    return output;
}

string Translator::exchange_token(vector<Token> tokens, int &index, stack<token_type> &stack_f_opt)
{

    string token_content;

    if(tokens[index].type == I_OPCION)
        return "";
    else if(tokens[index].type == F_OPCION)
    {   
        token_type f_token = stack_f_opt.top();
        stack_f_opt.pop();
        if(f_token == F_FUENTE || f_token == F_COLOR)
            return "</span>";
        else if(f_token == F_URL)
            return "</a>";
    }
    else if(tokens[index].type == WORD)
    {
        return tokens[index].value;
    }
    else if(tokens[index].type == I_URL && tokens[index + 1].type == WORD)
    {   
        stack_f_opt.push(F_URL);
        token_content = table[I_URL];
        token_content.replace(token_content.find("content"), 7, tokens[index + 1].value);
        token_content += table[F_URL];
        index+=2;
        return token_content;
    }
    else if(tokens[index].type == I_COLOR)
    {
        stack_f_opt.push(F_COLOR);
        token_content = table[I_COLOR];
        token_content.replace(token_content.find("content"), 7, table[tokens[index + 1].type]);
        token_content += table[F_COLOR];
        index+=2;
        return token_content;
    }
    else if(tokens[index].type == I_FUENTE)
    {
        stack_f_opt.push(F_FUENTE);
        token_content = table[I_FUENTE];
        token_content.replace(token_content.find("content"), 7, table[tokens[index + 1].type]);
        token_content += table[F_FUENTE];
        index+=2;
        return token_content;
    }
    else
    {
        token_content = table[tokens[index].type];
    }
    
    return token_content;
}

void Translator::init_exchange_table()
{
    table[I_TITULO] = "<h1>";
    table[F_TITULO] = "</h1>";

    table[I_SUBTITULO] = "<h2>";
    table[F_SUBTITULO] = "</h2>";

    table[I_SUBSUBTITULO] = "<h3>";
    table[F_SUBSUBTITULO] = "</h3>";

    table[I_PARRAFO] = "<p>";
    table[F_PARRAFO] = "</p>";

    table[I_NEGRITA] = "<b>";
    table[F_NEGRITA] = "</b>";

    table[I_CURSIVA] = "<em>";
    table[F_CURSIVA] = "</em>";

    table[I_TACHADO] = "<s>";
    table[F_TACHADO] = "</s>";

    table[I_OPCION] = "<";
    table[F_OPCION] = ">";

    table[I_COLOR] = "<span style=\"color: content\"";
    table[F_COLOR] = ">";

    table[I_FUENTE] = "<span style=\"font-family: content\"";
    table[F_FUENTE] = ">";

    table[I_URL] = "<a href=\"content\"";
    table[F_URL] = ">";

    table[SALTO_DE_LINEA] = "<br>";

    table[ROJO] = "red";
    table[AMARILLO] = "yellow";
    table[AZUL] = "blue";

    table[ARIAL] = "'Arial'";
    table[TIMES] = "'Times New Roman'";
    table[COURIER] = "'Courier New'";
    table[HELVETICA] = "'Helvetica'";
}