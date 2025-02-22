#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size;
    int mat[4][4], share[4], newarr[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Process %d: Entering matrix input phase.\n", rank);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("Enter Element [%d][%d]: ", i, j);
                scanf("%d", &mat[i][j]);
            }
        }
        printf("Process %d: Matrix input complete.\n", rank);
    }
    MPI_Scatter(mat, 4, MPI_INT, share, 4, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d: Received data from MPI_Scatter: ", rank);
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", share[i]);
    }
    printf("\n");
    MPI_Scan(share, newarr, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d: Result after MPI_Scan: ", rank);
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", newarr[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}