[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/1kKW-HvG)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=12641309&assignment_repo_type=AssignmentRepo)
# PathFinding

## Integrantes
> Fabrizzio Nicolay Vilchez Espinoza
> 
> 
> Angello Soldi

## Enunciado
Implementar **eficientemente** los siguientes algoritmos de búsqueda en grafos y aplicarlo al problema de PathFinding de manera visual.
- Dijkstra
- A*
- Greedy BSF (Opcional, +0.5 examen final)

> **Nota:** El código debe ser original, si se evidencia copia completa, copia parcial o copia estructural, la nota del ejercicio será de 0 y se penaliza con -10 puntos en evaluación contínua.


**Representación del Grafo**:
- Cada celda representa un vertice del grafo
- Los vertices adyacentes son los vecinos en vertical (2), horizontal (2) y diagonal (4). Como máximo 8 vertices adyacentes.
- Considerar como costo de movimiento:
  * Movimiento en horizontal y vertical: 10
  * Movimiento en diagonal: 14
- Implementar dos heurísticas: distancia manhattan y distancia euclidiana

![image](https://github.com/utec-cs-aed/PathFinding/assets/48141762/48c513ba-4a34-4f42-874e-a32a1e50cc72)


**Visualización**:
- Visualizar la ejecución del algoritmo de manera interactiva en consola. 
- Pueden usar interfaz gráfica de usuario (GUI) con cualquier libreria gráfica (Opcional, +1 examen final):
    * [SFML](https://www.sfml-dev.org/)
    * [QT Open Source](https://www.qt.io/download-open-source#source)
    * [WxWidgets](https://www.wxwidgets.org/)
    * [Visual Studio C++](https://visualstudio.microsoft.com/es/vs/features/cplusplus/)
    * [C++ Builder](https://www.embarcadero.com/es/products/cbuilder)

![image](https://github.com/utec-cs-aed/PathFinding/assets/48141762/0836d9ad-ca21-4382-b515-9feb4e467023)

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
