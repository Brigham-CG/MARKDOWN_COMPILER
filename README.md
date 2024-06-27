# COMPILADOR MARKDOWN
Codigo para la creacion de un compilador de Markdown

## Fucionalidades:
- Scanner
- Parser

## Gramatica (Antlr4):
La gramatica se encuentra en el archivo markdown.g4 con un ejemplo de entrda para el programa 'antlr4'
Comandos para usar el programa:

```bash
antlr4 markdown.g4
javac *.java  
grun markdown documento -gui
```
Posterior a ello, pon cualquier input que desees evaluar con tu gramatica. Y por ultimo, presionar la convinacion de teclas: **Ctrl+D**

> Tambien puedes encontrar una gramatica especial para la calculadora online de source forge: https://jsmachines.sourceforge.net/machines/ll1.html

## Scaner y Parser
El archivo principal es el **main.cpp**. Para compilarlo y probar, ingrese los comandos:

```bash
make
./main.exe
```

Tambien puede modificar el archivo 'texto.markdown' para probar tus propios inputs.

Por ultimo, para "limpiar" los archivos, ejecutar:

```bash
make clean
```

El ejemplo que se esta usando es:
```txt
<h1> titulo grande </h1>
<h2> titulo mediano </h2>
<h3> titulo pequeño </h3>
<p> esto es un parrafo </p>
<p> *esto esta en negrita* $esto esta en italica$ _esto esta tachado _ </p>
<p>*$_ esto es una triple anidacion _$*</p>

<p> <(rojo)esto esta en rojo> <(amarillo)esto esta en amarillo> <(azul)esto esta en azul></p>

<p> <[arial]esto esta en arial>  <[times]esto esta en times> <[courier]esto esta en courier> <[helvetica]esto esta en helvetica> </p>

<p><{http://google.com} esto es un enlace a <(azul)G><(rojo)o><(amarillo)o><(azul)g><(amarillo)l><(rojo)e>></p>

<t1> 
    <tm> | TITULO | | TITULO | | TITULO | </tm>
    <tn> | texto  | | texto  | | texto  | </tn>
    <tn> | texto  | | texto  | | texto  | </tn>
</t1>
```
