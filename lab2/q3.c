#include<stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int size, rank, x, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        printf("Size of ther process: %d\n", size);
        int array[size];
        printf("Enter the array: ");
        for (i=0;i<size;i++) {
            scanf("%d", &array[i]);
            }
        printf("Process : %d\n  squared Number: %d\n", rank, array[0]*array[0]);
        for (i=1;i<size;i++) {
            MPI_Ssend(&array[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
        
    } else {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        
        if (rank % 2 == 0) {
            printf("Process: %d \n squared Number: %d\n", rank, x*x);
        } else {
            printf("Process: %d \n cubed Number: %d\n", rank, x*x*x);
        }
    }
    MPI_Finalize();
    return 0;
}
