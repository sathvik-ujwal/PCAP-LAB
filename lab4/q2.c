#include<stdio.h>
#include"mpi.h"
    
int main(int argc, char * argv[]) {
    int size, rank, mat[3][3], val, recv[3], count=0, result;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter the 3x3 matrix\n");
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        printf("Enter the element to search\n");
        scanf("%d", &val);
    }

    MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&mat,3, MPI_INT, &recv,3, MPI_INT,0,MPI_COMM_WORLD);

    for (int i=0;i<3;i++) {
        if (recv[i] == val) {
            count += 1;
        }
    }
    printf("The number of occurances of %d in row %d is %d\n", val, rank+1, count);
    MPI_Reduce(&count, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0){
        printf("The total number of occurances of value %d is %d\n", val, result);
    }
  
    MPI_Finalize();
    return 0;

}