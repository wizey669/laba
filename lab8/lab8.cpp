#include <iostream>
#include <locale.h>
#include <time.h>
#include <cstdio> 
#include <queue>
using namespace std;

void BFS(int** G, int* vis, int numG, int s) {
    queue<int> q;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        printf("%3d", v);
        for (int i = 0; i < numG; i++) {
            if (vis[i] == 0 && G[v][i] == 1) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int** G;
    int* vis;
    int numG, s;

    std::cout << "Введите кол-во элементов: " << std::endl;
    std::cin >> numG;

    G = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    vis = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        vis[i] = 0;
        for (int j = 0; j < numG; j++) {
            G[i][j] = G[j][i] = (i == j ? 0 : rand() % 2);
        }
    }

    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d ", G[i][j]);
        }
        printf("\n");
    }
    printf("Введите нач вершину: ");
    scanf_s("%d", &s);
    printf("Порядок обхода: ");
    BFS(G, vis, numG, s);
    return 0;
}