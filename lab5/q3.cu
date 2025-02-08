#include <stdio.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void computeSine(float* input, float* output, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; 
    if (idx < size) {
        output[idx] = sinf(input[idx]);  
    }
}

int main() {
    float h_input[5];  
    printf("Enter 5 angles in radians:\n"); 
    for (int i = 0; i < 5; i++) {
        printf("Angle %d: ", i + 1);
        scanf("%f", &h_input[i]);
    }

    int N = 5;  
    
    float* h_output = (float*)malloc(N * sizeof(float));  

    float* d_input;
    float* d_output;
    cudaMalloc(&d_input, N * sizeof(float));
    cudaMalloc(&d_output, N * sizeof(float));

    cudaMemcpy(d_input, h_input, N * sizeof(float), cudaMemcpyHostToDevice);

    dim3 blockSize(256); 
    dim3 numBlocks((N + blockSize.x - 1) / blockSize.x);  

    computeSine<<<numBlocks, blockSize>>>(d_input, d_output, N);

    cudaMemcpy(h_output, d_output, N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("\nResults:\n");
    for (int i = 0; i < N; i++) {
        printf("Input angle (radians): %f -> sin: %f\n", h_input[i], h_output[i]);
    }

    cudaFree(d_input);
    cudaFree(d_output);

    free(h_output);

    return 0;
}
