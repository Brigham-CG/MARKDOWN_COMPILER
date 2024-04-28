grammar mark2;
// *hola @
documento: bloque FIN_DE_TEXTO;

bloque: texto bloque
        | titulo bloque
        | subtitulo bloque
        | subsubtitulo bloque
        | ;

titulo: I_TITULO texto ;
subtitulo: I_SUBTITULO texto ;
subsubtitulo: I_SUBSUBTITULO texto ;

texto:  PALABRA textoPrima
        | texto_especial 
        | SALTO_DE_LINEA ;

textoPrima: PALABRA textoPrima 
        | texto
        | ;

texto_especial: negrita
                | cursiva 
                | tachado 
                | subrayado
                | color
                | fuente
                | url ;

negrita: I_NEGRITA texto F_NEGRITA;

cursiva: I_CURSIVA texto F_CURSIVA;

tachado: I_TACHADO texto F_TACHADO;

subrayado: I_SUBRAYADO texto F_SUBRAYADO;

color: I_OPCION I_COLOR nombre_color F_COLOR texto F_OPCION;

fuente: I_OPCION I_FUENTE nombre_fuente F_FUENTE texto F_OPCION;

url: I_OPCION I_URL nombre_url F_URL texto F_OPCION;

nombre_color: ROJO | AZUL | AMARILLO; 
nombre_fuente: ARIAL | TIMES | COURIER;
nombre_url: LINK1 | LINK2 | LINK3;

// TOKENS
I_TITULO: '#';
I_SUBTITULO: '##';
I_SUBSUBTITULO: '###';

I_NEGRITA: '*'; 
F_NEGRITA: '@';

I_CURSIVA: '('; 
F_CURSIVA: ')';

I_TACHADO: '['; 
F_TACHADO: ']';

I_SUBRAYADO: '{';
F_SUBRAYADO: '}';

I_OPCION: '<';
F_OPCION: '>';

I_COLOR: '1';
F_COLOR: '2';

I_FUENTE: '3';
F_FUENTE: '4';

I_URL: '5';
F_URL: '6';

SALTO_DE_LINEA: '\n';

FIN_DE_TEXTO: '$$';
PALABRA: 'hola ';
ROJO: 'rojo';
AZUL: 'azul';
AMARILLO: 'amarillo';
ARIAL: 'arial';
TIMES: 'times';
COURIER: 'courier';
LINK1: 'linka';
LINK2: 'linkb';
LINK3: 'linkc';

/*
FOR gramar and LL1 calculator
Exameple: 
#hola hola \n?hola hola \n*hola @[hola ](hola )\n$$

GRamar: (FALTA COLOCAR LOS TOKENS DE LOS COLORES, FUENTES Y URLS)
documento=bloque,FINDETEXTO;
bloque=texto,bloque | titulo,bloque | subtitulo,bloque | subsubtitulo,bloque | ;
titulo=ITITULO,texto; 
subtitulo=ISUBTITULO,texto; 
subsubtitulo=ISUBSUBTITULO,texto; 
texto=PALABRA,textoprima | textoespecial |  SALTODELINEA; 
textoprima=PALABRA,textoprima | texto | ;
textoespecial=negrita|cursiva|tachado;
negrita=INEGRITA,texto,FNEGRITA;
cursiva=ICURSIVA,texto,FCURSIVA;
tachado=ITACHADO,texto,FTACHADO;
ITITULO= "#"; 
ISUBTITULO="?"; 
ISUBSUBTITULO="!"; 
INEGRITA="*"; 
FNEGRITA="@";
ICURSIVA="("; 
FCURSIVA=")";
ITACHADO="["; 
FTACHADO="]";
SALTODELINEA="\n"; 
FINDETEXTO="$$"; 
PALABRA="hola ";
*/