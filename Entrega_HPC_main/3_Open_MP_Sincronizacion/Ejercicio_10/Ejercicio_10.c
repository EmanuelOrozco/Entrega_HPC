/*
Ejercicio 3: 
Movimiento rectilíneo uniformemente acelerado (MRUA) - 
Modela el movimiento de un objeto bajo movimiento rectilíneo uniformemente acelerado (MRUA), 
donde el objeto parte de una posición inicial con una velocidad inicial, y se actualizan la posición y la velocidad en función de la aceleración

Utiliza OpenMP para calcular las posiciones y velocidades en varios puntos de tiempo de forma paralela, 
pero respetando las dependencias (cada posición futura depende de la posición anterior).

    Pseudocódigo
    - Inicializar valores de velocidad y posición.
    - Crear tareas para calcular posición y velocidad en diferentes tiempos t.
    - Utilizar dependencias para asegurar que cada tarea respete los cálculos previos.
*/

