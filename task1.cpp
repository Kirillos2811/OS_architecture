#include <iostream>
#include <numeric>
#include <pthread.h>
using namespace std;

void* multiply(void* args){
    float** args_array = (float **) args;
    *args_array[2] = *args_array[0] * (*args_array[1]);
    return 0;
}

int main(){
    int l = 3;
    int m = 2;
    int n = 3;

    float matrix1[l][m] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    float matrix2[m][n] = {
        {7, 8, 9},
        {10, 11, 12}
    };
    float res_matrix[l][n];

    for (int i = 0; i < l; i++){
        for (int j = 0; j < n; j++){
            float temp_array[m];
            for (int r = 0; r < m; r++){
                pthread_t thread;
                float* args[3] = {&matrix1[i][r], &matrix2[r][j], &temp_array[r]};
                pthread_create(&thread, NULL, multiply, (void *) args);
                pthread_join(thread, NULL);
            }
            res_matrix[i][j] = accumulate(temp_array, temp_array + m, 0.0);
        }
    }

    printf("Resulting matrix\n");
    for (int i = 0; i < l; i++){
        for (int j = 0; j < n; j++){
            printf("%f ", res_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}