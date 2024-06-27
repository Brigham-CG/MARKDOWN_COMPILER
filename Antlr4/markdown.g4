// ###############################################
// ##########  Antlr4 gramar version #############
// ###############################################

grammar markdown;

documento: bloque;
bloque: parrafo bloque |
    SALTO_DE_LINEA bloque |
    tabla bloque |
    titulo bloque |
    subtitulo bloque |
    subsubtitulo bloque | ;

titulo: I_TITULO texto F_TITULO;
subtitulo: I_SUBTITULO texto  F_SUBTITULO;
subsubtitulo: I_SUBSUBTITULO texto F_SUBSUBTITULO;

parrafo: I_PARRAFO texto F_PARRAFO;




//tabla: I_TABLA SALTO_DE_LINEA cuerpo_tabla F_TABLA;

//cuerpo_tabla: titulo_tabla SALTO_DE_LINEA cuerpo_tabla | contenido_tabla SALTO_DE_LINEA cuerpo_tabla |;

tabla: I_TABLA cuerpo_tabla F_TABLA;

cuerpo_tabla: titulo_tabla cuerpo_tabla | contenido_tabla cuerpo_tabla |;




titulo_tabla: I_TABLA_TITULO estructura_tabla F_TABLA_TITULO;

contenido_tabla: I_TABLA_CONTENIDO estructura_tabla F_TABLA_CONTENIDO;

estructura_tabla: BARRA_TABLA texto BARRA_TABLA estructura_tabla | ;

texto: PALABRA texto | SALTO_DE_LINEA texto | texto_especial texto |;

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

I_TITULO: '<h1>';
F_TITULO: '</h1>';
I_SUBTITULO: '<h2>';
F_SUBTITULO: '</h2>';
I_SUBSUBTITULO: '<h3>';
F_SUBSUBTITULO: '</h3>';
I_PARRAFO: '<p>';
F_PARRAFO: '</p>';
I_TABLA: '<t1>';
F_TABLA: '</t1>';
I_TABLA_TITULO: '<tm>';
F_TABLA_TITULO: '</tm>';
I_TABLA_CONTENIDO: '<tn>';
F_TABLA_CONTENIDO: '</tn>';
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
BARRA_TABLA: '|';
SALTO_DE_LINEA:  '\n';

// ###############################################
// ##########  Example input Antlr4 ##############
// ###############################################

/*
<h1>hola hola hola hola hola hola </h1>
<h2>hola hola hola </h2>

<h3>hola hola hola hola </h3>

<p>hola hola hola hola hola 
hola hola hola hola hola hola hola hola 
hola hola hola hola 1*hola hola 2*</p>
<p>hola hola 1$hola 1*hola hola 
hola 2*1_hola hola 2_2$hola hola hola hola hola 
hola hola hola hola 1*hola hola 2*</p>
<p><(rojo)hola 1*hola 2*>
<[arial]hola hola 1$hola hola 2$>hola 
<{linka}hola hola hola hola hola hola hola >
</p>
*/

// ###############################################
// ##########  Forge Calculator Version ##########
// ###############################################
// [!] https://jsmachines.sourceforge.net/machines/ll1.html

// [+]: Gramar:
/*
d -> b

b -> 1p t 2p b
b -> \n b
b -> 1b ct 2b
b -> 1t t 2t b
b -> 1s t 2s b
b -> 1z t 2z b
b -> ''

ct -> 1m et 2m ct
ct -> 1n et 2n ct
ct -> ''

et -> 1| t 2| et
et -> ''

t -> hola t
t -> \n t
t -> t' t
t -> ''

t' -> 1* t 2*
t' -> 1$ t 2$
t' -> 1_ t 2_
t' -> < z >

z -> ( c ) t
z -> [ f ] t
z -> { u } t

c -> rojo
c -> azul
c -> amarillo

f -> arial
f -> times
f -> courier

u -> linka
u -> linkb
u -> linkc
*/

// [+]: Input:
// 1t hola hola hola 2t \n 1s hola hola hola 2s \n \n 1z hola hola hola 2z \n 1p hola hola hola \n hola hola hola \n hola hola hola 1* hola hola hola 2* 2p \n 1p hola 1$ hola 1* hola hola \n hola 2* 1_ hola hola 2_ 2$ hola hola \n hola hola 1* hola hola 2* 2p \n 1p < ( rojo ) hola 1* hola 2* > \n < [ arial ] hola 1$ hola 2$ > \n hola \n < { linka } hola hola hola > \n 2p \n  

// 1t hola hola 2t \n 1b 1m 1| hola 2| 1| hola 2| 2m 1n 1| hola 2| 1| hola 2| 2n 1n 1| hola 2| 1| hola 2| 2n 2b