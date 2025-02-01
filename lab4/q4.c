#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    int rank, size;
    char input_word[MAX_LEN] = {0}, local_result[MAX_LEN] = {0};
    int word_length;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter a word of length %d: ", size);
        fflush(stdout);
        scanf("%s", input_word);
        word_length = strlen(input_word);
    }

    MPI_Bcast(input_word, MAX_LEN, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i <= rank; i++) {
        local_result[i] = input_word[rank]; 
    }
    local_result[rank + 1] = '\0'; 


    printf("Rank %d: Local result is \"%s\"\n", rank, local_result);
    char *gathered = (rank == 0) ? malloc(size * MAX_LEN) : NULL;

    if (rank != 0) {
        MPI_Send(local_result, MAX_LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        strncpy(gathered, local_result, MAX_LEN);
    }

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(gathered + i * MAX_LEN, MAX_LEN, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        char *final_output = malloc(MAX_LEN * size + 1);
        memset(final_output, 0, MAX_LEN * size + 1);  

        for (int i = 0; i < size; i++) {
            strncat(final_output, gathered + i * MAX_LEN, MAX_LEN);
        }

        printf("Rank 0: Final Output: %s\n", final_output);
        free(final_output);
        free(gathered);
    }

    MPI_Finalize();
    return 0;
}


