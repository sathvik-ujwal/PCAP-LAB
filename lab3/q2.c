#include <stdio.h>
#include <mpi.h>

float average_int(int arr[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

float average_float(float arr[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}
int main(int argc, char *argv[]) {
    int size, rank, M, N;
    float g, final;
    int a[100]; 
    int b[100]; 
    float r[100]; 
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    N = size;

    if (rank == 0) {
        printf("Enter value M (number of elements per process):\n");
        scanf("%d", &M); 

        printf("Enter %d elements:\n", N * M);
        for (int i = 0; i < N * M; i++) {
            scanf("%d", &a[i]); 
        }
    }


    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, M, MPI_INT, b, M, MPI_INT, 0, MPI_COMM_WORLD);
    g = average_int(b, M);
    MPI_Gather(&g, 1, MPI_FLOAT, r, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Results:\n");
        for (int i = 0; i < size; i++) {
            printf("%f ", r[i]); 
        }
        printf("\n");
        final = average_float(r, size);
        printf("Total average found in root %f", final);
    }

    MPI_Finalize();
    return 0;
}
