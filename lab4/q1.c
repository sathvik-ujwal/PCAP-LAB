#include<stdio.h>
#include"mpi.h"

int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    return n*factorial(n-1);
}
    
int main(int argc, char * argv[]) {
    int size, rank, fact=1, factsum;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    fact = factorial(rank+1);

    MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("The sum of factorials at process %d %d\n",rank+1, factsum);
    if (rank == size-1) {
        printf("The fina sum of factorials is : %d\n", factsum);
    }
    MPI_Finalize();
    return 0;




}