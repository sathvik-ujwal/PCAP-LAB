#include<stdio.h>
#include<string.h>
#include"mpi.h"

int main(int argc, char * argv[]) {
    int rank, size, b, r;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int arr[size];
    int recv[size];
    if (rank == 0)
    {
        printf("Enter %d elements\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    }
    MPI_Scatter(arr, 1, MPI_INT, &b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    b = b * b;
    printf("Process: %d, Squared: %d\n", rank + 1, b);
    MPI_Gather(&b, 1, MPI_INT, recv, size, MPI_INT,0,  MPI_COMM_WORLD);
    MPI_Reduce(&b, &r, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    int s = 0;
    if (rank == 0)
    {
        printf("The summed result found by MPI_Reduce is %d\n", r);
        for (int i = 0; i < size; i++) {
            s = s + recv[i];
            printf("%d \t", recv[i]);
        }
        printf("The sum of the squares gathered at root is %d \n", s);
    }

    MPI_Finalize();
    return 0;
}