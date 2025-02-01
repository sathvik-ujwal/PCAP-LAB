#include <stdio.h>
#include <mpi.h>

void handle_mpi_error(int mpi_error_code, const char* mpi_function_name) {
    if (mpi_error_code != MPI_SUCCESS) {
        char error_string[MPI_MAX_ERROR_STRING];
        int length_of_error_string;
        MPI_Error_string(mpi_error_code, error_string, &length_of_error_string);
        printf("MPI Error in %s: %s\n", mpi_function_name, error_string);
        MPI_Abort(MPI_COMM_WORLD, mpi_error_code);
    }
}

int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
    int size, rank, fact = 1, factsum;

    int mpi_error_code = MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size > 6) {
        mpi_error_code = 1;
        handle_mpi_error(mpi_error_code, "MPI_Comm_size"); 
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    fact = factorial(rank + 1);

    MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("The sum of factorials at process %d: %d\n", rank + 1, factsum);

    if (rank == size - 1) {
        printf("The final sum of factorials is: %d\n", factsum);
    }
    MPI_Finalize();

    return 0;
}
