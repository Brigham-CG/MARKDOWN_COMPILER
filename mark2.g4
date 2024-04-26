grammar mark2;

documento: bloque;

bloque: titulo | titulo bloque
        | subtitulo | subtitulo bloque
        | subsubtitulo | subsubtitulo bloque
        | texto | texto bloque;

titulo: I_TITULO ESPACIO texto ;
subtitulo: I_SUBTITULO ESPACIO texto ;
subsubtitulo: I_SUBSUBTITULO ESPACIO texto ;

texto:  palabra texto | palabra |
        palabra_especial texto | palabra_especial |
        SALTO_DE_LINEA;

palabra: LETRA palabra | LETRA | ESPACIO;

palabra_especial: negrita | 
                cursiva |      
                tachado | 
                color | 
                fuente | 
                url;

negrita: I_NEGRITA texto I_NEGRITA;

cursiva: I_CURSIVA texto I_CURSIVA;

tachado: I_TACHADO texto I_TACHADO;

color: I_OPCION I_COLOR nombre_color F_COLOR texto F_OPCION;

fuente: I_OPCION I_FUENTE nombre_fuente F_FUENTE texto F_OPCION;

url: I_OPCION I_URL nombre_url F_URL F_OPCION texto F_OPCION;

nombre_color: ROJO | AMARILLO | AZUL | RGB;
nombre_fuente: ARIAL | TIMES | COURIER | HELVETICA;
nombre_url: LINK1 | LINK2 | LINK3;

// TOKENS
I_TITULO: '#';
I_SUBTITULO: '##';
I_SUBSUBTITULO: '###';

I_NEGRITA: '*'; 
//F_NEGRITA: '*';

I_CURSIVA: '$'; 
//F_CURSIVA: '$';

I_TACHADO: '_'; 
//F_TACHADO: '_';

I_OPCION: '<';
F_OPCION: '>';

I_COLOR: '(';
F_COLOR: ')';

I_FUENTE: '[';
F_FUENTE: ']';

I_URL: '{';
F_URL: '}';

ESPACIO: ' ';
SALTO_DE_LINEA: '\n';

LETRA: [a-zA-Z0-9];

ROJO: 'rojo';
AMARILLO: 'amarillo';
AZUL: 'azul';
RGB: 'rgb';

ARIAL: 'arial';
TIMES: 'times';
COURIER: 'courier';
HELVETICA: 'helvetica';

LINK1: 'https://www.google.com';
LINK2: 'https://www.facebook.com';
LINK3: 'https://www.twitter.com';
