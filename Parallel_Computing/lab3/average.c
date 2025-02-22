#include<stdio.h>
#include<string.h>
#include"mpi.h"

float average(float *arr, int size) {
    float avg = 0;
    for (int i = 0; i < size; i++) {
        avg += arr[i];
    }
    return avg / size;
}

int main(int argc, char * argv[]) {
    int rank, size, m;
    float res;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    float arr[size * 10];

    if (rank == 0) {
        printf("Enter the value of M (less then 10)\n");
        scanf("%d", &m);
        printf("Enter %d values for the array\n", size * m);
        for (int i = 0; i < size * m; i++)
        {
            scanf("%f", &arr[i]);
        }
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    float recv[m];
    MPI_Scatter(arr, m, MPI_FLOAT, recv, m, MPI_FLOAT, 0, MPI_COMM_WORLD);
    float pres = average(recv, m);
    printf("The aveage found at process %d is %f \n", rank + 1, pres);
    MPI_Reduce(&pres, &res, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        float result = res / size;
        printf("The average of all the averages is %f \n", result);
    }

    MPI_Finalize();
    return 0;
}