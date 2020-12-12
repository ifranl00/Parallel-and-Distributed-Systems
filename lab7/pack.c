#include "mpi.h"
#include <stdio.h>
#include<string.h>

typedef struct {
    char name[20];
    int age;
    char city[20];
    float average;
    int favNum;
} Data;

int main(int argc, char *argv[])
{
    int rank, size;
    int i;
    char buffer[110];
    int position = 0;
    MPI_Status status;
    MPI_Datatype new_type;
    MPI_Datatype type[5] = { MPI_CHAR, MPI_INT, MPI_CHAR, MPI_FLOAT, MPI_INT};
    int blen[5] = { 20,1,20,1.0,1};
    MPI_Aint disp[5];
    MPI_Aint base, addr;
    Data tabrecord,tabrecieved;

    MPI_Init(&argc, &argv);
    double t0 = MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2)
    {
        printf("Please run with 2 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }

    if (rank == 0)
    {
        MPI_Pack(&i, 1, MPI_INT, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Pack(c, 100, MPI_CHAR, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 100, MPI_COMM_WORLD);
    }

    if (rank == 1)
    {
        MPI_Recv(buffer, 110, MPI_PACKED, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Unpack(buffer, 110, &position, &i, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, 110, &position, c, 100, MPI_CHAR, MPI_COMM_WORLD);
        printf("i=%d\nc[0] = %d\n...\nc[99] = %d\n", i, (int)c[0], (int)c[99]);fflush(stdout);
    }

    MPI_Finalize();
    return 0;
} 
