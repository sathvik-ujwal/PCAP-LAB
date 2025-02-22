#include<stdio.h>
#include<string.h>
#include"mpi.h"
#include<ctype.h>

int nonVowelCount(char * curr) {
    int count = 0;
    for (int i = 0; i < strlen(curr); i++) {
        char c = tolower(curr[i]);
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
            count++;
        }
    }
    return count;
}

int main(int argc, char * argv[]) {
    int rank, size, n, res;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    char word[size * 4];
    

    if (rank == 0) {
        printf("Enter the string (length should be a multiple of %d and it should be less %d)\n", size, size * 4);
        scanf("%s", word);
        n = strlen(word) / size;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    char recv[n+1];
    MPI_Scatter(word, n, MPI_CHAR, recv, n, MPI_CHAR, 0, MPI_COMM_WORLD);
    recv[n] = '\0';
    int cnt = nonVowelCount(recv);
    MPI_Reduce(&cnt, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("The total number of non vowels in the word is %d \n", res);
    }

    MPI_Finalize();
    return 0;
}