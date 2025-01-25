#include <stdio.h>
#include <string.h>
#include <mpi.h>

int findv(char str[], int rank){
    char *i = &str[0];
    int c = 0;
    while(*i!='\0'){
        if (*i == 'a' || *i =='e' || *i== 'i' || *i=='o' || *i=='u'){
            c+=1;
        }
        i++;
    }
    printf("Process %d found %d in %s\n", rank, c, str);
    return c;
}

int main(int argc, char *argv[]){
    int rank, size, chunk, fincount;
    char str[1000], recvstr[1000];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
        printf("Enter String: ");
        scanf("%s", str);
        chunk = (int) strlen(str)/size;
    }

    MPI_Bcast(&chunk, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str, chunk, MPI_CHAR, recvstr, chunk, MPI_CHAR, 0, MPI_COMM_WORLD);
    int count = findv(recvstr, rank);
    MPI_Reduce(&count, &fincount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("total count = %d\n", strlen(str)-fincount);
    }
    MPI_Finalize();
    return 0;

}