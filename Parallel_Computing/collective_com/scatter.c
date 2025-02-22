#include<stdio.h>
#include<mpi.h>

int main(int argc, char * argv[]) {
    int rank, size, n, arr[10], recv[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0){
        printf("Enter the number of elements to send to each arr\n");
        scanf("%d", &n);
        
        for (int i = 0; i < size * n; i ++)  {
            scanf("%d", &arr[i]);
        }
    }
    MPI_Scatter(arr, n, MPI_INT, recv, n, MPI_INT, 0, MPI_COMM_WORLD);

    printf("The numbers received by process %d is \n", rank + 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", recv[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
