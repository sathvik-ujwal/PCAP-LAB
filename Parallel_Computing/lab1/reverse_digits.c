#include<stdio.h>
#include"mpi.h"

int reverse_digits(int n) {
    int rem;
    int res = 0;
    while (n > 0)
    {
        rem = n % 10;
        res = (res * 10) + rem;
        n = n/10;
    }
    return res;
}

int main(int argc, char * argv[]) {
    int rank, size, arr[10], b, res[10], resInt;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter the array\n");
        for (int i = 0; i < size; i++){
            scanf("%d", &arr[i]);
        }
    }
    for (int i = 0; i < size; i++) {
        MPI_Send(&arr[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
    }
    MPI_Recv(&b, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
    int reverse = reverse_digits(b);
    MPI_Send(&reverse, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            MPI_Recv(&res[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
        }

        for (int i = 0; i < size; i++) {
            printf("%d ", res[i]);
        }
    }
    MPI_Finalize();
    return 0;
}