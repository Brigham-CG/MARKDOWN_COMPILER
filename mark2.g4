grammar markdown;

documento: bloque;

bloque: titulo | titulo bloque
        | subtitulo | subtitulo bloque
        | subsubtitulo | subsubtitulo bloque
        | texto 
        | texto bloque;

titulo: I_TITULO texto ;
subtitulo: I_SUBTITULO texto ;
subsubtitulo: I_SUBSUBTITULO texto ;

//texto: palata | palabra texto | SALTO_DE_LINEA;
//palabra: palabra_especial | palabra_normal;
//palabra_especial: negrita | cursiva | tachado | color | fuente;

texto: palabra | palabra texto
        | negrita | negrita texto
        | cursiva | cursiva texto
        | tachado | tachado texto
        | color | color texto 
        | fuente | fuente texto
        | url | url texto
        SALTO_DE_LINEA;

palabra: LETRA palabra | LETRA | ESPACIO;

negrita: I_NEGRITA text F_NEGRITA;

cursiva: I_CURSIVA textoEspecial F_CURSIVA;

tachado: I_TACHADO textoEspecial F_TACHADO;

color: I_OPCION I_COLOR nombre_color F_COLOR texo F_OPCION;

fuente: I_OPCION I_FUENTE nombre_fuente F_FUENTE texto F_OPCION;

url: I_OPCION I_URL word F_URL F_OPCION texto F_OPCION;

nombre_color: ROJO | AMARILLO | AZUL | RGB;
nombre_fuente: ARIAL | TIMES | COURIER | HELVETICA;

// TOKENS
I_TITULO: '#';
I_SUBTITULO: '##';
I_SUBSUBTITULO: '###';

S_NEGRITA: '*';
S_CURSIVA: '$';
S_TACHADO: '_';

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