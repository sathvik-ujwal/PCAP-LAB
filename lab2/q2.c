#include<stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int size, rank, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        printf("Rank of the process is %d\n", rank);
        printf("Enter the number: ");
        scanf("%d", &x);
        for (int i=1;i<size;i++) {
            MPI_Ssend(&x, 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        printf("Process: %d \n Number: %d\n", rank, x);
    }

    MPI_Finalize();
    return 0;
}
