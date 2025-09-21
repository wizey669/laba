#include <iostream>

using namespace std;

int main() {
    const int ROWS = 3;
    const int COLS = 4;

    int mass[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Вычисление суммы по столбцам
    int columnSums[COLS] = { 0 };

    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            columnSums[j] += mass[i][j];
        }
    }

    // Вывод результатов
    cout << "Arrays:" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "\n";
        for (int j = 0; j < COLS; j++) {
            cout << mass[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nSum col:" << endl;
    for (int j = 0; j < COLS; j++) {
        cout << "col " << j + 1 << ": " << columnSums[j] << endl;
    }

    return 0;
}