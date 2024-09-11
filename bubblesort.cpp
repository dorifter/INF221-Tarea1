#include <bits/stdc++.h>

using namespace std;

// Algoritmo Bubble Sort
void bubbleSort(int data[], int size) {
    bool swapped;
    int elemCounter, itemIndex;

    // Se repite según el tamaño del arreglo a considerar (size)
    for (elemCounter = 0; elemCounter < size - 1; elemCounter++) {

        // Auxiliar para optimizar tiempo, si no realiza cambios, algoritmo finalizado
        swapped = false;

        // Recorre desde el 0 hasta el final (hasta ese punto), se evita comparaciones innecesarias
        for (itemIndex = 0; itemIndex < size - elemCounter - 1; itemIndex++) {

            // Si el elemento anterior es menor, intercambia con su derecha
            if (data[itemIndex] > data[itemIndex + 1]) {
                swap(data[itemIndex], data[itemIndex + 1]);
                swapped = true;
            }
        }

        // Si no hay cambios, fin
        if (!swapped) {
            break;
        }
    }
}

int main() {

    // Nombre del archivo a leer
    string filename = "sorted_1000.txt"; // Cambia este nombre al archivo correspondiente

    // Vector para almacenar los números leídos del archivo
    vector<int> numbers;

    // Abrir el archivo para leer
    ifstream infile(filename);

    // Leer los números desde el archivo m
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }

    infile.close();

    int size = numbers.size();

    // Convertir el vector a un arreglo para pasar al Bubble Sort
    int* data = &numbers[0];

    bubbleSort(data, size);


    for (int i = 0; i < size; i++){
        cout << data[i] << " ";
    }

    return 0;
}