#include <iostream>
#include <time.h>
using namespace std;
void print_mass(int* mass, int size);
void quick_sort(int mass[], int L, int H);
void print_mass(int* mass, int size);
void sum_max_min(int* mass, int size);
int main(){
    srand(time(0));
    int size=0;
    cin >> size;
    
    int* mass = new int[size];
    for (int i = 0; i < size; ++i) {
        mass[i] = rand() % 100-20;
    }
    cin.ignore();
    quick_sort(mass, 0, size - 1);
    print_mass(mass, size);
    sum_max_min(mass, size);
    delete []mass;
}
void print_mass(int* mass, int size) {
    for (int i = 0; i < size; i++) {
        cout << mass[i]<<endl;
    }
}

void sum_max_min(int* mass,int size) {
    int sum = mass[0] + mass[size-1];
    cout << sum << endl;
}

int partitaion(int mass[], int L, int H) {
    int firstHigh = L;
    int p = H;
    for (int i = L; i < H; ++i) {
        if (mass[i] < mass[p]) {
            int temp = mass[firstHigh];
            mass[firstHigh] = mass[i];
            mass[i] = temp;
            firstHigh++;
        }
    }
    int temp = mass[firstHigh];
    mass[firstHigh] = mass[p];
    mass[p] = temp;
    return firstHigh;
}

void quick_sort(int mass[], int L, int H) {
    if (H - L > 0) {
        int p = partitaion(mass, L, H);
        quick_sort(mass, L, p - 1);
        quick_sort(mass, p + 1, H);
    }
}
