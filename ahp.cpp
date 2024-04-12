#include <iostream>
#include <vector>
#include <algorithm> // Para std::sort
#include <utility>   // Para std::pair
#include <cmath>
#include <stdio.h>

using namespace std;

// Función para normalizar una matriz
void matriznormalizada(vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<double> colSum(n, 0);

    // Calcular la suma de cada columna
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            colSum[j] += matriz[i][j];
        }
    }

    // Normalizar la matriz dividiendo cada elemento por la suma de su columna
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            matriz[i][j] /= colSum[j];
        }
    }
}

// Función para calcular el vector propio para una matriz
vector<double> calcularVectorPropio(vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<double> eigenVector(n, 0);

    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += matriz[i][j];
        }
        eigenVector[i] = sum / n;
    }

    return eigenVector;
}

// Función principal para el algoritmo AHP
vector<double> AHP(vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<double> weights(n, 0);

    // Paso 1: Normalizar la matriz
    matriznormalizada(matriz);

    // Paso 2: Calcular el vector propio
    weights = calcularVectorPropio(matriz);

    return weights;
}

int main() {
    // Ejemplo de matriz de comparación
    vector<vector<double>> MatrizComparacion = {
        {1, 7, 5, 1.0/3},
        {1.0/7, 1, 1.0/3, 1.0/9},
        {1.0/5, 3, 1, 1.0/7},
        {3, 9, 7, 1}
    };

    // Imprimir la matriz de comparación original
    cout << "Matriz de comparacion original:" << endl;
    for (const auto& fila : MatrizComparacion) {
        for (const auto& elemento : fila) {
            cout << elemento << "\t";
        }
        cout << endl;
    }

    // Obtener los pesos utilizando AHP
    vector<double> weights = AHP(MatrizComparacion);

    // Crear un vector de pares (índice, peso) para mantener el ranking
    vector<pair<int, double>> ranking;
    for (int i = 0; i < weights.size(); ++i) {
        ranking.push_back({i, weights[i]});
    }

    // Ordenar el ranking en orden descendente basado en los pesos
    sort(ranking.begin(), ranking.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Imprimir el ranking
    cout << "\nRanking:" << endl;
    for (const auto& pair : ranking) {
        cout << "Opcion " << pair.first + 1 << ": Peso " << pair.second << endl;
    }

    // Mostrar al usuario qué opción es la mejor
    cout << "\nLa mejor opcion es la numero " << ranking[0].first + 1 << endl;

    system("pause");
    return 0;
}
