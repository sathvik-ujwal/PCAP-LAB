#include <stdio.h>
#include <cuda.h>
#include <string.h>
#include <stdlib.h>

__global__ void transformString(char *d_S, char *d_RS, int N) {
    int idx = threadIdx.x;
    int start_index = 0;

    for (int i = 0; i < N; i++) {
        if (idx < (N - i)) {
            d_RS[start_index + idx] = d_S[idx];
        }
        start_index += (N - i);
    }
}

int main() {
    char *h_S; 
    char *h_RS;
    int N, M;

    printf("Enter a string: ");
    h_S = (char *)malloc(1000 * sizeof(char)); 
    scanf("%s", h_S); 

    N = strlen(h_S);  
    M = (N * (N + 1)) / 2; 

    h_RS = (char *)malloc((M + 1) * sizeof(char)); 
    char *d_S, *d_RS;
    cudaMalloc((void **)&d_S, N * sizeof(char));
    cudaMalloc((void **)&d_RS, M * sizeof(char));

    cudaMemcpy(d_S, h_S, N * sizeof(char), cudaMemcpyHostToDevice);
    transformString<<<1, N>>>(d_S, d_RS, N);
    cudaMemcpy(h_RS, d_RS, M * sizeof(char), cudaMemcpyDeviceToHost);
    h_RS[M] = '\0'; 

    printf("Input string S: %s\n", h_S);
    printf("Output string RS: %s\n", h_RS);

    free(h_S);
    free(h_RS);
    cudaFree(d_S);
    cudaFree(d_RS);

    return 0;
}