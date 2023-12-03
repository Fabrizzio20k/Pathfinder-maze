# PathFinding

PathFinding es un programa que encuentra el camino más corto entre dos puntos en un laberinto usando diferentes algoritmos de búsqueda.

Instrucciones

1. Necesita tener instalado CMake y un compilador de C++ (g++ o clang). Para ejecutar, ejecute los siguientes comandos en la terminal:

```bash
mkdir build
cd build
cmake ..
make
./PathFinding
```

Si eso no funciona, usando algún IDE como Visual Studio Code o CLion, abra la carpeta `PathFinding` como un proyecto CMake y ejecute el programa desde ahí.

**Nota:** Si está usando Windows, puede usar Visual Studio 2019 para compilar y ejecutar el programa.

Al momento de ejecutar el programa, usted puede generar un laberinto de 20x20, 30x30, 40x40 o 50x50. Luego, usted puede elegir el algoritmo de búsqueda que desea usar, y luego elegir el punto de inicio y el punto de destino. El programa le mostrará el camino más corto entre el punto de inicio y el punto de destino.
Para actualizar los obstaculos sin necesidad de pulsar el boton de "Reset", puede darle al boton "Save" cuantas veces quiera.
