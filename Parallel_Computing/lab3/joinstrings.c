#include<stdio.h>
#include<string.h>
#include"mpi.h"

int main(int argc, char * argv[]) {
    int rank, size, n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    char word1[10];
    char word2[10];

    if (rank == 0) {
        printf("Enter the string 1\n");
        scanf("%s", word1);
        printf("Enter the string 2\n");
        scanf("%s", word2);
        n = strlen(word1);
        }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int blocksize = n / size;
    char cw1[blocksize+1];
    char cw2[blocksize+1];
    MPI_Scatter(word1, blocksize, MPI_CHAR, cw1, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(word2, blocksize, MPI_CHAR, cw2, blocksize, MPI_CHAR, 0, MPI_COMM_WORLD);
    cw1[blocksize] = '\0';
    cw2[blocksize] = '\0';
    char localconcat[blocksize * 2 + 1];
    strcpy(localconcat, cw1);
    strcat(localconcat, cw2);
    char recv[2 * n + 1];
    MPI_Gather(localconcat, blocksize * 2, MPI_CHAR, recv, blocksize * 2, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        recv[2 * n] = '\0';
        printf("The resultant string is %s\n", recv);
    }
    MPI_Finalize();
    return 0;
}