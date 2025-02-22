#include<stdio.h>
#include"mpi.h"
#include<stdbool.h>
#include<math.h>

// mpicc -o prime prime.c -lm
// when importing math.h use the above command to compile the code

bool isPrime(int num){
    for (int i = 2; i < sqrt(num) + 1; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char * argv[]) {
    int rank, size, fh[20], sh[20];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0) {
        int curr = 0;
        for (int i = 0; i < 50; i++)
        {
            if (isPrime(i)) {
                fh[curr] = i;
                printf("%d ", i);
            }
        }
    } else {
        int curr = 0;
        for (int i = 50; i < 101; i++)
        {
            if (isPrime(i)) {
                sh[curr] = i;
                printf("%d ", i);
            }
        }
    }
    MPI_Finalize();
    return 0;
}