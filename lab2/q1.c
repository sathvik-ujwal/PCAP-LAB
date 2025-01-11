#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "mpi.h"

void toggle_word(char *word) {
    int i = 0;
    while (word[i] != '\0') {
        if (islower(word[i])) {
            word[i] = toupper(word[i]);
        } else if isupper(word[i]) {
            word[i] = tolower(word[i]);
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    int rank, size, len;
    char s[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        
        printf("Enter the word ");
        fprintf(stdout, "Rank of the process: %d \n", rank);
        fflush(stdout);
        scanf("%s", s);
        len = strlen(s);
        MPI_Ssend(&len, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Ssend(s, len, MPI_CHAR, 1, 2, MPI_COMM_WORLD);
        MPI_Recv(s, len, MPI_CHAR, 1, 3, MPI_COMM_WORLD, &status);
        fprintf(stdout, "toggled word %s \n", s);
        fflush(stdout);
    } else if (rank == 1) {
        
        MPI_Recv(&len, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        fprintf(stdout, "Rank of the process: %d \n", rank);
        fflush(stdout);
        fprintf(stdout, "Length of the word : %d \n", len);
        fflush(stdout);
        MPI_Recv(s, len, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
        fprintf(stdout, "The Word: %s \n", s);
        fflush(stdout);
        toggle_word(s);
        MPI_Ssend(s, len, MPI_CHAR, 0, 3, MPI_COMM_WORLD);
    }
    //fflush(stdout);
    
    MPI_Finalize();
    return 0;
}


// mpicc - o q1 q1.c -lm 
// mpirun -n 3 ./q1