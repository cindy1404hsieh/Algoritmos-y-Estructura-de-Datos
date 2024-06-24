# Algoritmos-y-Estructura-de-Datos Pandolfo
# Sala de Escape Pokemon - Juego
![image](https://github.com/cindy1404hsieh/Algoritmos-y-Estructura-de-Datos/assets/90338162/ae61db39-c690-4bcc-a7fa-59456f453839)


# TP1
## Descripción
Durante este trabajo, se desarrolló un programa que simula una sala de escape temática de Pokémon. El objetivo principal del juego es permitir que el usuario interactúe con varios objetos dentro de la sala para poder escapar. Se implementó la lógica del juego utilizando archivos que describen los objetos presentes en la sala y las posibles interacciones entre ellos.


## Reglas del Juego
El juego consta de una sala de escape que contiene diversos objetos como lapiceras, pokebolas, anillos y cucharas, entre otros. Estos objetos son fundamentales para lograr escapar de la sala. Las reglas principales del juego son:

Cada objeto y sus interacciones están descritos en archivos de texto.
El archivo de objetos tiene la estructura NOMBRE_OBJETO;DESCRIPCION;FLAG, donde el flag puede ser true o false.
El archivo de interacciones tiene la estructura NOMBRE_OBJETO;VERBO;NOMBRE_OBJETO2;ACCION. Si NOMBRE_OBJETO2 es un espacio en blanco, la interacción no requiere un segundo objeto.
Los tipos de acción posibles son:
- d: descubrir objetos
- r: reemplazar objetos
- e: eliminar objetos
- m: mostrar un mensaje

## Conceptos Evaluados
- Lectura y manejo de archivos: Se implementaron funciones para leer y procesar archivos de texto.  
- Manejo de memoria dinámica: Se usaron adecuadamente las funciones malloc y free para gestionar la memoria.  
- Estructuras de datos: Se emplearon estructuras para representar objetos e interacciones.  
- Modularización del código: Se dividió el código en múltiples archivos y funciones para mejorar la organización y legibilidad.  
- Validación de interacciones: Se comprobó la validez de las interacciones entre objetos.  
- Liberación de recursos: Se aseguró la liberación de toda la memoria dinámica utilizada.  

## Compilación

Para compilar el juego, utiliza el siguiente comando:
```
gcc escape_pokemon.c -o escape_pokemon -Wall -Wextra -std=c99
```
``` 
./escape_pokemon objetos.txt interacciones.txt
```

# TP2

## Descripción
Durante este trabajo, se desarrolló una extensión del juego "Sala de Escape Pokémon", que presenta una interfaz basada en texto. El jugador puede ingresar comandos para dirigir las acciones del protagonista dentro de la sala de escape. Este trabajo reutiliza gran parte de la implementación del TP1 y añade nuevas funcionalidades y cambios estructurales para mejorar la jugabilidad y la organización del código.

El juego consta de una sala de escape con diversos objetos y posibles interacciones. Al iniciar el juego, el jugador solo conoce el primer objeto que aparece en el archivo de objetos. A través de la interacción con este objeto, se descubrirán más objetos que serán esenciales para escapar de la sala.

## Reglas del Juego

El juego se desarrolla mediante una interfaz de texto donde el jugador puede ingresar comandos para realizar diversas acciones. Los comandos básicos que el jugador puede usar son:

- `ayuda`: Muestra un mensaje de ayuda para recordar al jugador los comandos disponibles.
- `agarrar <objeto>`: Intenta agarrar uno de los objetos conocidos de la sala.
- `describir <objeto>`: Describe uno de los objetos conocidos de la sala.
- `salir`: Sale del juego.

Además de estos comandos, existen otros comandos específicos definidos en el archivo de interacciones que permiten al jugador interactuar con los diferentes objetos de la sala. Por ejemplo:

- `examinar habitacion`: Si el verbo "examinar" existe para la habitación, se ejecuta la acción especificada en el archivo de interacciones.
- `usar <objeto1> <objeto2>`: Si el verbo "usar" existe para el objeto1 con el objeto2, se ejecuta la acción especificada en el archivo de interacciones.

Cada interacción posible en el archivo de interacciones puede tener diferentes efectos, como descubrir nuevos objetos, eliminar objetos, o permitir al jugador escapar de la sala.

## Compilación y Ejecucion

Para compilar el programas, utiliza el siguiente comando:

```
gcc sala.c escape_pokemon.c -o escape_pokemon -Wall -Wextra -std=c99

```
```
./escape_pokemon objetos.txt interacciones.txt
```


## Conceptos Evaluados

- **Lectura y manejo de archivos**: Se implementaron funciones para leer y procesar archivos de texto que describen los objetos y las interacciones.
- **Manejo de memoria dinámica**: Se usaron adecuadamente las funciones `malloc` y `free` para gestionar la memoria.
- **Estructuras de datos**: Se emplearon estructuras de datos definidas para representar objetos e interacciones, así como la estructura de la sala.
- **Modularización del código**: Se dividió el código en múltiples archivos y funciones para mejorar la organización y legibilidad. La estructura de la sala se definió en `sala.c`, y se implementaron TDA utilizados a lo largo del cuatrimestre.
- **Validación de interacciones**: Se comprobó la validez de las interacciones entre objetos, incluyendo nuevas acciones como `ESCAPAR`.
- **Interfaz de usuario**: Se desarrolló una interfaz de texto que permite al usuario interactuar con el juego mediante comandos básicos como `ayuda`, `agarrar`, `describir`, y `salir`, además de comandos específicos definidos en el archivo de interacciones.
- **Pruebas**: Se elaboraron pruebas para verificar el correcto comportamiento de las funciones implementadas, especialmente las nuevas funciones de `sala.c`.



