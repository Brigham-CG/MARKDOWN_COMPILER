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


