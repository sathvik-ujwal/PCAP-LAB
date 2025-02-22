#include<stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, b;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_rank(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter the number to broadcast\n");
        scanf("%d", &b);
    }

    MPI_Bcast(&b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("The value received by process %d is %d \n", rank + 1, b);

    MPI_Finalize();
    return 0;
}