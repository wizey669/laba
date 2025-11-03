#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

//функция для генерации матрицы
void generateMatrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {

                if (rand() % 2 == 1) {
                    matrix[i][j] = 1;
                }
            }
            else {
                if (rand() % 2 == 1) {
                    matrix[i][j] = 1;
                    matrix[j][i] = 1;
                }
            }
        }
    }
}

//функция для вывода
void printMatrix(int n, int** matrix) {
    printf("Матрица смежности:\n   ");
    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//функция для степени с учетом петель
int calculateDegree(int n, int** matrix, int vertex) {
    int degree = 0;
    for (int i = 0; i < n; i++) {
        if (i == vertex && matrix[vertex][i] == 1) {
            degree += 2;
        }
        else {
            degree += matrix[vertex][i];
        }
    }
    return degree;
}

//определение размера графа с учетом петель
int graphSize(int n, int** matrix) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                edges += matrix[i][j];
            }
            else {
                edges += matrix[i][j];
            }
        }
    }
    return edges;
}

//подсчет петель
int countLoops(int n, int** matrix) {
    int loops = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            loops++;
        }
    }
    return loops;
}

//изолированные вершины
void findIsolated(int n, int** matrix) {
    printf("Изолированные вершины (степень 0): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, matrix, i) == 0) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//концевые вершины 
void findEnd(int n, int** matrix) {
    printf("Концевые вершины (степень 1): ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, matrix, i) == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//доминирующие вершины
void findDominating(int n, int** matrix) {
    printf("Доминирующие вершины (степень %d): ", n - 1);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (calculateDegree(n, matrix, i) == n - 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//вершины с петлями
void findVerticesWithLoops(int n, int** matrix) {
    printf("Вершины с петлями: ");
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) printf("нет");
    printf("\n");
}

//функция для вывода степеней вершин
void printDegrees(int n, int** matrix) {
    printf("Степени вершин:\n");
    for (int i = 0; i < n; i++) {
        int degree = calculateDegree(n, matrix, i);
        printf("Вершина %d: степень %d", i + 1, degree);
        if (matrix[i][i] == 1) {
            printf(" (имеет петлю)");
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    int n;

    printf("Введите количество вершин графа: ");
    scanf_s("%d", &n);

    // выделение памяти 
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }

    generateMatrix(n, matrix);

    printf("\n");
    printMatrix(n, matrix);


    int size = graphSize(n, matrix);
    int loops = countLoops(n, matrix);
    printf("\nРазмер графа (количество ребер): %d\n", size);
    printf("Количество петель: %d\n", loops);

    printf("\n");
    printDegrees(n, matrix);

    printf("\n");
    findIsolated(n, matrix);
    findEnd(n, matrix);
    findDominating(n, matrix);
    findVerticesWithLoops(n, matrix);

    //освобождение памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
