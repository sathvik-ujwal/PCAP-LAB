#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

#define N 10

__global__ void selectionSort(int * arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int k = i;
        for (int j = i+1;  j < n; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }

        if (k != i) {
            int temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
}

int main() {
    int input_arr[N] = {64,  25, 12, 22, 11, 90, 55, 33, 77, 88};
    int *d_arr;

    cudaMalloc((void**)&d_arr, N * sizeof(int));
    cudaMemcpy(d_arr, input_arr, N*sizeof(int), cudaMemcpyHostToDevice);

    selectionSort<<<1,1>>>(d_arr, N);

    cudaMemcpy(input_arr, d_arr, N* sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array ");
    for (int i = 0; i < N; i++) {
        printf("%d ", input_arr[i]);
    }
    printf("\n");

    cudaFree(d_arr);
    return 0;
}