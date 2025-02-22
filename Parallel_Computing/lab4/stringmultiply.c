#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char word[size];  // Input word
    if (rank == 0) {
        printf("Enter a word with %d characters:\n", size);
        scanf("%s", word);
    }

    char letter[2] = "";  // Buffer to store the scattered letter as a string
    MPI_Scatter(word, 1, MPI_CHAR, letter, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    letter[1] = '\0';  // Null-terminate the string

    // Prepare a buffer to store the repeated string
    char result[100] = "";  // Ensure it is large enough for repetitions
    for (int i = 0; i < rank + 1; i++) {
        strcat(result, letter);
    }

    // Gather all the results at the root
    int maxLen = 100;  // Maximum size of each process's string
    char gathered[size * maxLen];  // Buffer to hold all results at root
    MPI_Gather(result, maxLen, MPI_CHAR, gathered, maxLen, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Root process combines and prints the final result
    if (rank == 0) {
        printf("Final combined string: ");
        for (int i = 0; i < size; i++) {
            printf("%s", &gathered[i * maxLen]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
