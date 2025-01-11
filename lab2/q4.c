#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int size, rank, x;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the number: ");
        scanf("%d", &x);
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        x += 1; 
        printf("Process %d received number: %d, incremented to: %d\n", rank, x - 1, x);

        if (rank != size - 1) {
            MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == size - 1) {
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent final value: %d back to root\n", rank, x);
    }

    if (rank == 0) {
        MPI_Recv(&x, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Root process received final value: %d\n", x);
    }

    MPI_Finalize();
    return 0;
}
