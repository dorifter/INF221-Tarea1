#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {

    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    // Nombre del archivo a leer
    string filename = "random_1000000.txt"; // Cambia este nombre al archivo correspondiente

    // Vector para almacenar los números leídos del archivo
    vector<int> numbers;

    // Abrir el archivo para leer
    ifstream infile(filename);
    if (!infile) {
        cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }

    // Leer los números desde el archivo
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }
    infile.close();

    int size = numbers.size();


    mergeSort(numbers, 0, size - 1);


    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    
    return 0;
}