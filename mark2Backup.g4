/*
backup antes de colocar los tokens de url, fuente, color
*/

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
                | subrayado;

negrita: I_NEGRITA texto F_NEGRITA;

cursiva: I_CURSIVA texto F_CURSIVA;

tachado: I_TACHADO texto F_TACHADO;

subrayado: I_SUBRAYADO texto F_SUBRAYADO;

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

SALTO_DE_LINEA: '\n';

FIN_DE_TEXTO: '$$';
PALABRA: 'hola ';



/*
FOR gramar and LL1 calculator
Exameple: 
#hola hola \n?hola hola \n*hola @[hola ](hola )\n$$

GRamar: 
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