grammar mark2;

documento: bloque;

//Bloque
bloque: texto bloquePrima
        | titulo bloquePrima
        | subtitulo
        | subsubtitulo;

bloquePrima: texto bloquePrima | titulo bloquePrima | FIN_DE_LINEA;

titulo: I_TITULO texto ;
subtitulo: I_SUBTITULO texto ;
subsubtitulo: I_SUBSUBTITULO texto ;

texto:  PALABRA textoPrima;

textoPrima: PALABRA textoPrima | SALTO_DE_LINEA;

// TOKENS
I_TITULO: '#';
I_SUBTITULO: '##';
I_SUBSUBTITULO: '###';

SALTO_DE_LINEA: '\n';

FIN_DE_LINEA: '$$';
PALABRA: 'hola ';