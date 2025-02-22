#include <stdio.h>
#include"mpi.h"

int main(int argc, char * argv[]) {
    int rank, size, b, recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    b = rank*rank;
    printf("The input for process %d is %d\n", rank + 1, b);

    MPI_Reduce(&b, &recv, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("The sum of all of the numbers is %d\n", recv);
    }
       
    MPI_Finalize();
    return 0;
}