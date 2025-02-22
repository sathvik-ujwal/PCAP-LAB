#include<stdio.h>
#include<string.h>
#include"mpi.h"

int main(int argc, char * argv[]) {
    int rank, size;
    int arr[3][3];
    int recarr[3];
    int ele;
    int res;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0){
        printf("Enter the elements of the 3x3 matrix\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                printf("[%d][%d] \n", i, j);
                scanf("%d", &arr[i][j]);
               // printf("\n");
            }
        }
        printf("Enter element to search\n");
        scanf("%d", &ele);
    }
    MPI_Scatter(arr, 3, MPI_INT, recarr, 3, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < 3;i++) {
        if (recarr[i] == ele) {
            res = 1;
        }
    }
    int result;
    MPI_Reduce(&res, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            if (result > 0) {
            printf("The element found in the matrix\n");
        } else {
            printf("Element not found in the matrix\n");
        }
    }
    

    MPI_Finalize();
    return 0;
}