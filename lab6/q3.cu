#include <stdio.h>
#include <cuda_runtime.h>

#define N 10 

__global__ void oddKernel(int *arr, int n) {
    int i = 2 * threadIdx.x + 1;
    if (i < n - 1 && arr[i] > arr[i + 1]) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

__global__ void evenKernel(int *arr, int n) {
    int i = 2 * threadIdx.x;
    if (i < n - 1 && arr[i] > arr[i + 1]) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

int main() {
    int h_arr[N] = {64, 25, 12, 22, 1, 90, 55, 564, 77, 88};
    int *d_arr;

    cudaMalloc((void **)&d_arr, N * sizeof(int));
    cudaMemcpy(d_arr, h_arr, N * sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = N / 2;
    for (int i = 0; i < N; i++) {
        oddKernel<<<1, threadsPerBlock>>>(d_arr, N);
        cudaDeviceSynchronize();
        evenKernel<<<1, threadsPerBlock>>>(d_arr, N);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(h_arr, d_arr, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Sorted array: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", h_arr[i]);
    }
    printf("\n");

    cudaFree(d_arr);
    return 0;
}