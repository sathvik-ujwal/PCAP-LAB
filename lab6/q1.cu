#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

__global__ void convolution_1D_basic_kernel(float *N, float *M, float *P, int Mask_Width, int Width) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    float Pvalue = 0;
    int N_start_point = i - (Mask_Width/2);
    for (int j = 0; j < Mask_Width; j++ ) {
        if (N_start_point + j >= 0 && N_start_point + j < Width) {
            Pvalue += N[N_start_point + j] * M[j];
        }
    }
    P[i] = Pvalue;
}

int main() {
    int N, M;
    printf("Enter the size of the array\n");
    scanf("%d", &N);
    printf("Enter the size of the convolution mask\n");
    scanf("%d", &M);

    float inputArr[N];
    float Mask[M];
    float resultantArr[N];

    printf("Enter %d elements for input array\n", N);
    for (int i = 0 ; i < N ; i++) {
        scanf("%f", &inputArr[i]);
    }
    printf("Enter %d elements of the Mask\n", M);
    for (int i = 0; i < M; i++) {
        scanf("%f", &Mask[i]);
    } 

    float *d_inputArr, *d_Mask, *d_resultArr;
    cudaMalloc((void**)&d_inputArr, N * sizeof(float));
    cudaMalloc((void**)&d_Mask, M * sizeof(float));
    cudaMalloc((void**)&d_resultArr, N * sizeof(float));

    cudaMemcpy(d_inputArr, inputArr, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_Mask, Mask, M * sizeof(float), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (N + blockSize - 1) / blockSize;

    convolution_1D_basic_kernel<<<gridSize, blockSize>>>(d_inputArr, d_Mask, d_resultArr, M, N);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA ERROR : %s \n", cudaGetErrorString(err));
    }

    cudaMemcpy(resultantArr, d_resultArr, N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Convolution  result\n");
    for (int i = 0; i < N; i++) {
        printf("%f ", resultantArr[i]);
    }
    printf("\n");

    cudaFree(d_inputArr);
    cudaFree(d_Mask);
    cudaFree(d_resultArr);

    return 0;
}

