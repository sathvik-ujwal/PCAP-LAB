#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void vectorAdd256(int *a, int *b, int *c, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N) {
        c[idx] = a[idx] + b[idx];
    }
}

__global__ void vectorAdd(int *a, int *b, int *c, int N) {
    int idx = blockIdx.x;
    if (idx < N) {
        c[idx] = a[idx] + b[idx];
    }
}

int main() {
    int N;
    printf("Enter the size of the vector: ");
    scanf("%d", &N);
    
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));
    c = (int *)malloc(N * sizeof(int));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

    for (int i = 0; i < N; i++) {
        a[i] = i*i;
        b[i] = i;
    }

    cudaMalloc(&d_a, N * sizeof(int));
    cudaMalloc(&d_b, N * sizeof(int));
    cudaMalloc(&d_c, N * sizeof(int));

    cudaMemcpy(d_a, a, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N * sizeof(int), cudaMemcpyHostToDevice);

    vectorAdd<<<N, 1>>>(d_a, d_b, d_c, N);
    cudaDeviceSynchronize();  
    
    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);
    printf("Results using N blocks: ");
    for (int i = 0; i < N && i < 10; i++) {  
        printf("%d ", c[i]);
    }
    printf("\n");

    vectorAdd256<<<1, N>>>(d_a, d_b, d_c, N);
    cudaDeviceSynchronize();

    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);
    printf("Results using N threads (1 block): ");
    for (int i = 0; i < N && i < 10; i++) { 
        printf("%d ", c[i]);
    }
    printf("\n");

    int threadsPerBlock = 256;
    int numBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;  
    vectorAdd256<<<numBlocks, threadsPerBlock>>>(d_a, d_b, d_c, N);
    cudaDeviceSynchronize(); 

    cudaMemcpy(c, d_c, N * sizeof(int), cudaMemcpyDeviceToHost);
    printf("Results using 256 threads per block: ");
    for (int i = 0; i < N && i < 10; i++) { 
        printf("%d ", c[i]);
    }
    printf("\n");

    free(a);
    free(b);
    free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
