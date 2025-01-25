#include <stdio.h>
#include <string.h>
#include <mpi.h>

void findv(char str[], char str2[], char result[], int chunk, int rank) {
    int a1 = 0, a2 = 0;
    for (int i = 0; i < chunk * 2; i++) {
        if (i % 2 == 0) {
            result[i] = str[a1];
            a1++;
        } else {
            result[i] = str2[a2];
            a2++;
        }
    }
    result[chunk * 2] = '\0';
}

int main(int argc, char *argv[]) {
    int rank, size, chunk;
    char str1[1000], str2[1000], recvstr1[1000], recvstr2[1000], substr[1000], finstr[1000 * 2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter String1: ");
        scanf("%s", str1);
        printf("Enter String2: ");
        scanf("%s", str2);
        chunk = strlen(str1) / size;
    }
    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, chunk, MPI_CHAR, recvstr1, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, chunk, MPI_CHAR, recvstr2, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    findv(recvstr1, recvstr2, substr, chunk, rank);
    MPI_Gather(substr, chunk * 2, MPI_CHAR, finstr, chunk * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        finstr[chunk * 2 * size] = '\0';
        printf("Final String: %s\n", finstr);
    }

    MPI_Finalize();
    return 0;
}