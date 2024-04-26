# MARKDOWN_COMPILER
A markdown compiler with scanner, parser, etc.

# Link of LL1 parser calculator
> https://planetcalc.com/5600/

## Gramar:
documento=bloque;
bloque=texto,bloquePrima|titulo,bloquePrima|subtitulo|subsubtitulo;
bloquePrima=texto,bloquePrima|titulo,bloquePrima|FINDELINEA;
titulo=ITITULO,texto;
subtitulo=ISUBTITULO,texto;
subsubtitulo=ISUBSUBTITULO,texto;
texto=PALABRA,textoPrima;
textoPrima=PALABRA,textoPrima|SALTODELINEA;
ITITULO= "#";
ISUBTITULO="##";
ISUBSUBTITULO="###";
SALTODELINEA="\n";
FINDELINEA="$$";
PALABRA="hola ";

## Input:
hola hola hola \n#hola hola \nhola \n$$
