#include "mpi.h"
#include <stdio.h>
#include <string.h>

/*
4. On the basis of the sample program modify the previous program and send your structure
with MPI_PACK data type. Measure the time of sending the data and compare with a
previous results.
*/

typedef struct {
    char name[20];
    int age,i;
    int phone;
    float weight;
    float height;
} Data;

int main(int argc, char *argv[])
{
    int rank, size, packet_size;
    int i;
    char buffer[110];
    int position = 0;
    MPI_Status status;
    MPI_Datatype new_type;
    MPI_Datatype type[5] = { MPI_CHAR, MPI_INT , MPI_INT, MPI_FLOAT, MPI_FLOAT};
    int blen[5] = { 20, 1 ,1,1.0,1.0};
    MPI_Aint disp[5];
    MPI_Aint base, addr;
    Data tabrecord,tabreceive;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Get_address(&tabreceive, &base);
        MPI_Get_address(&(tabreceive.name), &addr);
        disp[0] = addr - base;
        MPI_Get_address(&(tabreceive.age), &addr);
        disp[1] = addr - base;
        MPI_Get_address(&(tabreceive.phone), &addr);
        disp[2] = addr - base;
        MPI_Get_address(&(tabreceive.weight), &addr);
        disp[3] = addr - base;
        MPI_Get_address(&(tabreceive.height), &addr);
        disp[4] = addr - base;
        MPI_Type_create_struct(5, blen, disp, type, &new_type);
        MPI_Type_commit(&new_type);

    if (size < 2)
    {
        printf("Please run with 2 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (i=0; i<100; i++)
            strcpy(tabrecord.name, "Peter");
            tabrecord.age = 20;
            tabrecord.phone = 98765;
            tabrecord.weight = 80.6;
            tabrecord.height = 1.92;
        
        MPI_Pack(&tabrecord, 1, new_type, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 110, MPI_COMM_WORLD);
    }

    if (rank == 1)
    {
        position = 0;
        MPI_Recv(buffer, 110, MPI_PACKED, 0, 110, MPI_COMM_WORLD, &status);
        MPI_Unpack(buffer, 110, &position, &tabreceive, 1, new_type, MPI_COMM_WORLD); 
        printf("name = %s\nage = %d\nphone = %d\nweight = %f\nheight = %f\n", tabreceive.name,tabreceive.age,tabreceive.phone,tabreceive.weight,tabreceive.height);fflush(stdout);
    }

    MPI_Finalize();
    return 0;
} 