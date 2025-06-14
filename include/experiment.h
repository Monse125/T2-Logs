#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>
#include <functional>
#include <chrono>

/**
 * Mide el tiempo de ejecución de una función
 * @param func Función a ejecutar
 * @return Tiempo de ejecución en microsegundos
 */
template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

/**
 * Ejecuta experimentos para un tamaño de entrada dado
 * @param n Número de puntos
 * @param results Vector para almacenar los resultados
 */
void runExperiments(int n, std::vector<std::vector<long long>>& results);

/**
 * Ejecuta una prueba rápida para validar la implementación
 */
void runQuickTest();

/**
 * Guarda los resultados en un archivo
 * @param results Matriz con los tiempos de ejecución
 */
void saveResults(const std::vector<std::vector<long long>>& results);

#endif
