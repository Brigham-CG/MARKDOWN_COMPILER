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
// (>‿◠)✌
 
<h1> estoy aburrido </h1>

<h2> y aun no acabo de hacer esto </h2>

<h3> lo mismo queja de arriba pero ahora en h3 </h3>

<p> si preguntan por ti, solo dire que te vi en mis suenos una noche 
y solo sueno desde entonces...</p>

<p> *esto esta en negrita $pero esto esta en cursiva$ _ y esto esta tachado _*</p>

<p> <(rojo) esto esta en rojo> <[arial] esto esta en arial> 
<{https://google.com} google ></p>
```