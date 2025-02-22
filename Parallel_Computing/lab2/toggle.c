#include<stdio.h>
#include<string.h>
#include"mpi.h"
#include<ctype.h>

void toggle(char * word) {
    int i = 0;
    while (word[i] != '\0') {
        if (islower(word[i])) {
            word[i] = toupper(word[i]);
        } else {
            word[i] = tolower(word[i]);
        }
        i++;
    }
}

int main(int argc, char * argv[]) {
    int rank, size, n;
    char word[8];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter the word to send\n");
        scanf("%s", word);
        n = strlen(word);
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(word, strlen(word), MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(word, strlen(word), MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        printf("The toggled word is %s\n", word);
    }
    else if (rank == 1){
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(word, n, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        printf("HEEHE\n");
        toggle(word);
        MPI_Send(word, n, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}