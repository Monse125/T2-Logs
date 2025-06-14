#include <iostream>
#include <vector>
#include "experiment.h"

using namespace std;

/**
 * Función principal que ejecuta todos los experimentos
 */
int main() {
    cout << "=== Tarea 2: Algoritmo de Kruskal ===" << endl;
    cout << "Implementación de 4 variantes del algoritmo de Kruskal" << endl << endl;
    
    // Ejecutar prueba rápida primero
    runQuickTest();
    
    cout << "Ejecutando experimentos completos..." << endl << endl;
    
    vector<vector<long long>> results;
    
    // Ejecuta experimentos para n = 2^5, 2^6, ..., 2^12
    for (int exp = 5; exp <= 12; exp++) {
        int n = 1 << exp;  // 2^exp
        runExperiments(n, results);
    }
    
    // Guarda resultados
    saveResults(results);
    
    cout << endl << "=== Experimentos completados ===" << endl;
    cout << "Los resultados han sido guardados en results.txt" << endl;
    cout << "Puedes usar estos datos para crear gráficos comparativos." << endl;
    cout << "Ejecuta './analyzer' para generar análisis automáticamente." << endl;
    
    return 0;
}
