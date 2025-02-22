// process 1 send to process 2 and 2 to 3 so on and the last 
// process sends it back to root
// the value should be incremented each time its sent

#include<stdio.h>
#include"mpi.h"

int main(int argc, char * argv[]){
    int rank, size,n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank == 0) {
        printf("Enter the number\n");
        scanf("%d", &n);
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank != size-1) {
        MPI_Recv(&n, 1, MPI_INT, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
        printf("The value received by process %d is %d \n", rank, n);
        n++;
        MPI_Send(&n, 1, MPI_INT, rank + 1, rank, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&n, 1, MPI_INT, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
        printf("The value received by process %d is %d \n", rank, n);
        n++;
        MPI_Send(&n, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        MPI_Recv(&n, 1, MPI_INT, size-1 , size-1, MPI_COMM_WORLD, &status);
        printf("The value received by process %d is %d \n", rank, n);
    }
    

    MPI_Finalize();
    return 0;
}