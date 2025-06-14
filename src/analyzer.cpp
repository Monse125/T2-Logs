#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct ExperimentResult {
    int n;
    long long sortedOpt;
    long long heapOpt;
    long long sortedNoOpt;
    long long heapNoOpt;
};

vector<ExperimentResult> readResults(const string& filename) {
    vector<ExperimentResult> results;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        istringstream iss(line);
        ExperimentResult result;
        
        if (iss >> result.n >> result.sortedOpt >> result.heapOpt >> result.sortedNoOpt >> result.heapNoOpt) {
            results.push_back(result);
        }
    }
    
    return results;
}

void printAnalysis(const vector<ExperimentResult>& results) {
    cout << "=== ANÁLISIS DE RESULTADOS ===" << endl << endl;
    
    cout << "Datos experimentales:" << endl;
    cout << "N\tSorted+Opt\tHeap+Opt\tSorted-Opt\tHeap-Opt" << endl;
    cout << string(60, '-') << endl;
    
    for (const auto& result : results) {
        cout << result.n << "\t" << result.sortedOpt << "\t\t" << result.heapOpt 
             << "\t\t" << result.sortedNoOpt << "\t\t" << result.heapNoOpt << endl;
    }
    cout << endl;
    
    // Calcular speedup de la optimización
    cout << "Speedup de la optimización:" << endl;
    double sortedSpeedupSum = 0.0;
    double heapSpeedupSum = 0.0;
    
    for (const auto& result : results) {
        double sortedSpeedup = result.sortedOpt > 0 ? (double)result.sortedNoOpt / result.sortedOpt : 0.0;
        double heapSpeedup = result.heapOpt > 0 ? (double)result.heapNoOpt / result.heapOpt : 0.0;
        
        sortedSpeedupSum += sortedSpeedup;
        heapSpeedupSum += heapSpeedup;
        
        cout << fixed << setprecision(2);
        cout << "N=" << result.n << ": Sorted " << sortedSpeedup << "x, Heap " << heapSpeedup << "x" << endl;
    }
    
    double sortedAvg = sortedSpeedupSum / results.size();
    double heapAvg = heapSpeedupSum / results.size();
    
    cout << endl << "Promedio - Sorted Array: " << sortedAvg << "x" << endl;
    cout << "Promedio - Heap: " << heapAvg << "x" << endl << endl;
    
    // Comparar estructuras de datos
    cout << "Comparación de estructuras (con optimización):" << endl;
    int sortedWins = 0;
    
    for (const auto& result : results) {
        if (result.sortedOpt < result.heapOpt) {
            cout << "N=" << result.n << ": Sorted Array es " 
                 << (double)result.heapOpt / result.sortedOpt << "x más rápido" << endl;
            sortedWins++;
        } else {
            cout << "N=" << result.n << ": Heap es " 
                 << (double)result.sortedOpt / result.heapOpt << "x más rápido" << endl;
        }
    }
    
    cout << endl << "Comparación de estructuras (sin optimización):" << endl;
    for (const auto& result : results) {
        if (result.sortedNoOpt < result.heapNoOpt) {
            cout << "N=" << result.n << ": Sorted Array es " 
                 << (double)result.heapNoOpt / result.sortedNoOpt << "x más rápido" << endl;
        } else {
            cout << "N=" << result.n << ": Heap es " 
                 << (double)result.sortedNoOpt / result.heapNoOpt << "x más rápido" << endl;
        }
    }
    
    cout << endl << "=== OBSERVACIONES ===" << endl;
    
    // Análisis de complejidad
    cout << "1. Efecto de la optimización Union-Find:" << endl;
    if (sortedAvg > 1.0) {
        cout << "   - La compresión de caminos mejora el rendimiento en promedio " 
             << sortedAvg << "x para sorted array" << endl;
    }
    if (heapAvg > 1.0) {
        cout << "   - La compresión de caminos mejora el rendimiento en promedio " 
             << heapAvg << "x para heap" << endl;
    }
    
    cout << endl << "2. Comparación de estructuras de datos:" << endl;
    int heapWins = results.size() - sortedWins;
    
    if (sortedWins > heapWins) {
        cout << "   - El arreglo ordenado tiende a ser más rápido que el heap" << endl;
    } else if (heapWins > sortedWins) {
        cout << "   - El heap tiende a ser más rápido que el arreglo ordenado" << endl;
    } else {
        cout << "   - Ambas estructuras tienen rendimiento similar" << endl;
    }
    
    cout << "   - Sorted Array gana en " << sortedWins << "/" << results.size() << " casos" << endl;
    cout << "   - Heap gana en " << heapWins << "/" << results.size() << " casos" << endl;
    
    cout << endl << "3. Escalabilidad:" << endl;
    if (results.size() >= 2) {
        double firstRatio = results[0].sortedOpt > 0 ? (double)results[1].sortedOpt / results[0].sortedOpt : 0.0;
        double lastRatio = results[results.size()-2].sortedOpt > 0 ? (double)results[results.size()-1].sortedOpt / results[results.size()-2].sortedOpt : 0.0;
        
        cout << "   - Factor de crecimiento inicial: " << firstRatio << "x" << endl;
        cout << "   - Factor de crecimiento final: " << lastRatio << "x" << endl;
    }
    
    cout << endl << "4. Complejidad teórica vs práctica:" << endl;
    cout << "   - Kruskal tiene complejidad O(E log E) donde E = n(n-1)/2" << endl;
    cout << "   - La optimización Union-Find reduce las operaciones find de O(n) a O(α(n))" << endl;
    cout << "   - El heap debería ser más eficiente para grafos dispersos, pero aquí tenemos grafos completos" << endl;
    cout << "   - El arreglo ordenado puede aprovechar mejor la localidad de memoria" << endl;
}

int main() {
    cout << "=== Analizador de Resultados - Tarea 2 Kruskal ===" << endl << endl;
    
    vector<ExperimentResult> results = readResults("results.txt");
    
    if (results.empty()) {
        cout << "Error: No se encontraron datos válidos en results.txt" << endl;
        cout << "Ejecuta primero el programa principal para generar los datos." << endl;
        return 1;
    }
    
    printAnalysis(results);
    
    return 0;
}
