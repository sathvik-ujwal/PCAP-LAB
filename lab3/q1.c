#include <stdio.h>
#include "mpi.h"

int factorial(int n) {
    if (n == 1) {
        return 1;
    }

    return n * factorial(n-1);
}
int main(int argc, char *argv[]) {
    int size, rank, recvBuff ;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int a[size];
    int b[size];

    if (rank == 0){
       printf("Enter %d elements\n", size);
       for (int i=0; i < size; i++) {
        scanf("%d", &a[i]);
       }
    }

    MPI_Scatter(a, 1, MPI_INT, &recvBuff, 1, MPI_INT, 0, MPI_COMM_WORLD);
    recvBuff = factorial(recvBuff);
    MPI_Gather(&recvBuff, 1, MPI_INT,b,1,MPI_INT, 0, MPI_COMM_WORLD);
    
    
    if (rank == 0) {
        printf("Results:");
        for (int i=0;i< size;i++) {
            
            printf("%d ", b[i]);
        }
    }

    


    MPI_Finalize();
    return 0;
}

