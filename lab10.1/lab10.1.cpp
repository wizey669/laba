#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdio> 
#include <queue>
#include <climits>
#include <cstdlib>
using namespace std;

void BFSD(int** G, int* dist, int numG, int** GD) {
    for (int s = 0; s < numG; s++) {
        for (int i = 0; i < numG; i++) {
            GD[s][i] = INT_MAX;
        }
        GD[s][s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int i = 0; i < numG; i++) {
                if (G[v][i] > 0 && GD[s][i] > GD[s][v] + G[v][i]) {
                    GD[s][i] = GD[s][v] + G[v][i];
                    q.push(i);
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    int r = INT_MAX;
    int d = -1;
    int** G;
    int** GD;
    int* Ecc;
    int numG;

    std::cout << "Введите кол-во элементов: " << std::endl;
    std::cin >> numG;

    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    GD = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        GD[i] = (int*)malloc(numG * sizeof(int));
        for (int j = 0; j < numG; j++) {
            GD[i][j] = 0;
        }
    }

    Ecc = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        Ecc[i] = 0;
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = (rand() % 2 == 0) ? 0 : (rand() % 10 + 1);
                G[j][i] = G[i][j];  
            }
        }
    }

    std::cout << "Матрица смежности графа:" << std::endl;
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]);
        }
        printf("\n");
    }

    BFSD(G, Ecc, numG, GD);

    std::cout << "\nМатрица расстояний:" << std::endl;
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", GD[i][j] == INT_MAX ? -1 : GD[i][j]);
            if (GD[i][j] != INT_MAX && Ecc[i] < GD[i][j]) {
                Ecc[i] = GD[i][j];
            }
        }
        printf("\n");
    }

    std::cout << "\nЭксцентриситеты вершин:" << std::endl;
    for (int i = 0; i < numG; i++) {
        printf("Вершина %d: %d\n", i, Ecc[i]);
        if (Ecc[i] > 0) {
            r = (r > Ecc[i]) ? Ecc[i] : r;
            d = (d < Ecc[i]) ? Ecc[i] : d;
        }
    }

    if (r == INT_MAX || d == -1) {
        std::cout << "\nГраф несвязный!" << std::endl;
    }
    else {
        std::cout << "\nРадиус графа: " << r << std::endl;
        std::cout << "Диаметр графа: " << d << std::endl;
    }

    for (int i = 0; i < numG; i++) {
        free(G[i]);
        free(GD[i]);
    }
    free(G);
    free(GD);
    free(Ecc);

    return 0;
}