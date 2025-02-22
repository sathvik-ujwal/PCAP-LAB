#include<stdio.h>
#include"mpi.h"
#include <stdbool.h>
#include <string.h>

int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}

bool searchLetter(char word[], char ele){
    int l = strlen(word);
    for (int i = 0; i < l; i++) {
        if (word[i] == ele) {
            return true;
        }
    }
    return false;
}


int main(int argc, char * argv[]) {
    int rank, size, l;
    char word[20];
    char letter;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if (rank == 0) {
        printf("Enter word\n");
        scanf("%s", word);
        printf("Enter letter to search in the word\n");
        scanf(" %c", &letter);
        
        int len = strlen(word);
        MPI_Send(word, strlen(word)+1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&letter, 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
       
        MPI_Recv(word, 20, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&letter, 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        printf("The received value at process %d is %s \n", rank, word);
        printf("The letter to search for is %c \n", letter);
        if (searchLetter(word, letter)) {
            printf("The letter is found in the word\n");
        } else {
            printf("Letter not found in word\n");
        }
        // printf("Factorial of the num is %d", factorial(b));
    }

    MPI_Finalize();
    return 0;
}