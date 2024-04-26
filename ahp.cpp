#include <iostream>
#include <vector>

using namespace std;

// Funcion para ingresar la matriz de comparacion de criterios
vector<vector<double>> ingresarMatriz(int n) {
    vector<vector<double>> matriz(n, vector<double>(n));
    cout << "Ingrese los valores de la matriz de comparacion de criterios:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Valor de C" << i+1 << " en comparacion con C" << j+1 << ": ";
            cin >> matriz[i][j];
        }
    }
    return matriz;
}

// Funcion para ingresar la matriz de alternativas
vector<vector<double>> ingresarMatrizAlternativas(int a) {
    vector<vector<double>> matriz(a, vector<double>(a));
    cout << "Ingrese los valores de la matriz de Alternativas:\n";
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            cout << "Valor de C" << i+1 << " en comparacion con C" << j+1 << ": ";
            cin >> matriz[i][j];
        }
    }
    return matriz;
}

// Funcion para normalizar la matriz
vector<vector<double>> normalizarMatriz(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<vector<double>> matrizNormalizada(n, vector<double>(n));
    vector<double> sumaColumnas(n, 0.0);

    // Calcular la suma de cada columna
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            sumaColumnas[j] += matriz[i][j];
        }
    }

    // Normalizar la matriz dividiendo cada elemento de una columna por la suma total de esa columna
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizNormalizada[i][j] = matriz[i][j] / sumaColumnas[j];
        }
    }

    return matrizNormalizada;
}

// Funcion para normalizar la matriz de alternativas
vector<vector<double>> normalizarMatrizAlternativas(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<vector<double>> matrizNormalizada(n, vector<double>(n));
    vector<double> sumaColumnas(n, 0.0);

    // Calcular la suma de cada columna
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            sumaColumnas[j] += matriz[i][j];
        }
    }

    // Normalizar la matriz dividiendo cada elemento de una columna por la suma total de esa columna
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizNormalizada[i][j] = matriz[i][j] / sumaColumnas[j];
        }
    }

    return matrizNormalizada;
}

// Funcion para calcular el promedio de cada fila
vector<double> calcularPromedioFilas(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<double> promedios(n, 0.0);

    for (int i = 0; i < n; ++i) {
        double sumaFila = 0.0;
        for (int j = 0; j < n; ++j) {
            sumaFila += matriz[i][j];
        }
        promedios[i] = sumaFila / n;
    }

    return promedios;
}

int encontrarMejorAlternativa(const vector<double>& promediosTotales) {
    // Buscar el máximo en el vector de promedios
    double maxPromedio = promediosTotales[0];
    int mejorAlternativa = 0;
    for (int i = 1; i < promediosTotales.size(); ++i) {
        if (promediosTotales[i] > maxPromedio) {
            maxPromedio = promediosTotales[i];
            mejorAlternativa = i;
        }
    }
    return mejorAlternativa + 1; // Sumar 1 porque los índices comienzan desde 0
}

int main() {
    int n, a;
    cout << "Ingrese el tamano de la matriz de comparacion de criterios: ";
    cin >> n;

    // Ingresar la matriz de comparacion de criterios
    vector<vector<double>> matriz = ingresarMatriz(n);

    // Normalizar la matriz
    vector<vector<double>> matrizNormalizada = normalizarMatriz(matriz);

    // Calcular el promedio de cada fila
    vector<double> promedios = calcularPromedioFilas(matrizNormalizada);

    // Mostrar los resultados
    cout << "Matriz normalizada:\n";
    for (const auto& fila : matrizNormalizada) {
        for (double valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }

    cout << "\nPromedio de cada fila:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Fila " << i+1 << ": " << promedios[i] << endl;
    }

    char continuar = 's';
    vector<vector<double>> promediosPorCriterio; // Vector de vectores para almacenar los promedios por criterio

    do {
        cout << "Numero de alternativas a evaluar: ";
        cin >> a;

        // Matriz de alternativas
        vector<vector<double>> matrizAlternativas = ingresarMatrizAlternativas(a);

        // Normalizar la matriz de alternativas
        vector<vector<double>> matrizNormalizadaAlternativas = normalizarMatrizAlternativas(matrizAlternativas);

        // Calcular los promedios de cada fila para las alternativas
        vector<double> promediosAlternativas = calcularPromedioFilas(matrizNormalizadaAlternativas);

        // Mostrar los resultados
        cout << "Matriz normalizada de Alternativas:\n";
        for (const auto& fila : matrizNormalizadaAlternativas) {
            for (double valor : fila) {
                cout << valor << " ";
            }
            cout << endl;
        }

        cout << "\nPromedio de cada fila para las alternativas:\n";
        for (int i = 0; i < a; ++i) {
            cout << "Fila " << i+1 << ": " << promediosAlternativas[i] << endl;
        }

        // Agregar los promedios de las alternativas al vector de promedios por criterio
        promediosPorCriterio.push_back(promediosAlternativas);

        // Preguntar al usuario si desea continuar ingresando alternativas
        cout << "¿Desea ingresar mas alternativas? (s/n): ";
        cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    // Mostrar los promedios totales por criterio al final
    cout << "\nPromedios de todas las alternativas por criterio:\n";
    for (int i = 0; i < promediosPorCriterio.size(); ++i) {
        cout << "Criterio " << i+1 << ":\n";
        for (int j = 0; j < promediosPorCriterio[i].size(); ++j) {
            cout << "Alternativa " << j+1 << ": " << promediosPorCriterio[i][j] << endl;
        }
    }

    vector<double> promediosTotales;
    for (const auto& promediosCriterio : promediosPorCriterio) {
        promediosTotales.insert(promediosTotales.end(), promediosCriterio.begin(), promediosCriterio.end());
    }

    int mejorAlternativa = encontrarMejorAlternativa(promediosTotales);
    cout << "\nLa mejor alternativa es la numero: " << mejorAlternativa << endl;

    system("pause");
    return 0;
}
