#include <stdio.h>

#define VEC_SIZE 10

void bubble_sort(int* v, int n) {
    int i, j, tmp;
    
    for (i = 0; i < (n - 1); i++) {
        for (j = (i + 1); j < n; j++) {
            if (v[i] > v[j]) {
                tmp     = v[i];
                v[i]    = v[j];
                v[j]    = tmp;
            }
        }
    }
}

void selection_sort(int* v, int n) {
    int i, j, min, tmp;
    
    for (i = 0; i < (n - 1); i++) {
       min = i;
        for (j = (i + 1); j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        
        tmp     = v[min];
        v[min]  = v[i];
        v[i]    = tmp;
    }
}

int main(int argc, char** argv) {
    int v[VEC_SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int i;
    
    //bubble_sort(v, VEC_SIZE);
    selection_sort(v, VEC_SIZE);
    
    for (i = 0; i < VEC_SIZE; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    
    return 0;
}
