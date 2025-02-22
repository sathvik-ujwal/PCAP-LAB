#include<stdio.h>
#include<string.h>
#include"mpi.h"

int main(int argc, char * argv[]) {
    int rank, size, arr[10], b, ts;
    int even, odd;
    int res[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0){
        printf("Enter the elements of the array\n");
        for (int i = 0; i < size;  i++) {
            scanf("%d", &arr[i]);
        }
    }
    MPI_Scatter(arr, 1, MPI_INT, &b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (b % 2 == 0) {
        ts = 1;
    } else {
        ts = 0;
    }
    MPI_Gather(&ts, 1, MPI_INT, res, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Input Array : ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        printf("Resultant Array : ");
        for (int i = 0; i < size;i++) {
            printf("%d ", res[i]);
        }
    }

    MPI_Finalize();
    return 0;
}