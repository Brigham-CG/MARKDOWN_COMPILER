grammar mark3;


documento: bloque;
bloque: linea bloque |
    '#' texto SALTO_DE_LINEA bloque |
    '?' texto SALTO_DE_LINEA bloque |
    '!' texto SALTO_DE_LINEA bloque |
     ;
    
linea: texto SALTO_DE_LINEA ;
texto: PALABRA texto | texto_especial texto |;

texto_especial: negrita | cursiva | tachado | opcion;

negrita: I_NEGRITA texto F_NEGRITA;
cursiva: I_CURSIVA texto F_CURSIVA;
tachado: I_TACHADO texto F_TACHADO;

opcion: I_OPCION tipo F_OPCION;

tipo: color | fuente | url;

color: I_COLOR nombre_color F_COLOR texto ;
fuente: I_FUENTE nombre_fuente F_FUENTE texto;
url: I_URL nombre_url F_URL texto;


nombre_color: ROJO | AZUL | AMARILLO; 
nombre_fuente: ARIAL | TIMES | COURIER;
nombre_url: LINK1 | LINK2 | LINK3;

I_NEGRITA: '1*'; 
F_NEGRITA: '2*';
I_CURSIVA: '1$'; 
F_CURSIVA: '2$';
I_TACHADO: '1_'; 
F_TACHADO: '2_';
I_OPCION: '<';
F_OPCION: '>';
I_COLOR: '(';
F_COLOR: ')';
I_FUENTE: '[';
F_FUENTE: ']';
I_URL: '{';
F_URL: '}';
ROJO: 'rojo';
AZUL: 'azul';
AMARILLO: 'amarillo';
ARIAL: 'arial';
TIMES: 'times';
COURIER: 'courier';
LINK1: 'linka';
LINK2: 'linkb';
LINK3: 'linkc';

PALABRA: 'hola ';
SALTO_DE_LINEA:  '\n';


// documento=bloque;
// bloque=linea,bloque|"#", texto,SALTODELINEA,bloque|;
// linea=texto,SALTODELINEA;
// texto= PALABRA,texto | textoespecial,texto |;
// textoespecial= negrita | cursiva | tachado;
// negrita= INEGRITA,texto,FNEGRITA;
// cursiva= ICURSIVA, texto, FCURSIVA;
// tachado= ITACHADO, texto,FTACHADO;
// PALABRA="hola ";
// SALTODELINEA="\n";
// INEGRITA="1*"; 
// FNEGRITA="2*";
// ICURSIVA= "1$"; 
// FCURSIVA= "2$";
// ITACHADO= "1_"; 
// FTACHADO= "2_";

documento = bloque;
bloque = linea, bloque
       | "#", texto, SALTODELINEA, bloque
       | "?", texto, SALTODELINEA, bloque
       | "!", texto, SALTODELINEA, bloque
       |;
linea = texto, SALTODELINEA;
texto = PALABRA, texto
       | textoespecial, texto
       |;
textoespecial = negrita
               | cursiva
               | tachado
               | opcion;
negrita = INEGRITA, texto, FNEGRITA;
cursiva = ICURSIVA, texto, FCURSIVA;
tachado = ITACHADO, texto, FTACHADO;

opcion= IOPCION, tipo, FOPCION;

tipo= color | fuente | url;

color = ICOLOR, nombrecolor, FCOLOR, texto;
fuente = IFUENTE, nombrefuente, FFUENTE, texto;
url = IURL, nombreurl, FURL, texto;

nombrecolor = ROJO
             | AZUL
             | AMARILLO;
nombrefuente = ARIAL
              | TIMES
              | COURIER;
nombreurl = LINK1
           | LINK2
           | LINK3;

PALABRA = "hola ";
SALTODELINEA = "\n";
INEGRITA = "1*";
FNEGRITA = "2*";
ICURSIVA = "1$";
FCURSIVA = "2$";
ITACHADO = "1_";
FTACHADO = "2_";
IOPCION = "<";
FOPCION = ">";
ICOLOR = "(";
FCOLOR = ")";
IFUENTE = "[";
FFUENTE = "]";
IURL = "{";
FURL = "}";
ROJO = "rojo";
AZUL = "azul";
AMARILLO = "amarillo";
ARIAL = "arial";
TIMES = "times";
COURIER = "courier";
LINK1 = "linka";
LINK2 = "linkb";
LINK3 = "linkc";