#include "mpi.h"
#include <stdio.h>
#include<string.h>

/* MPI_PACK() AND MPI_UNPACK() packs/unpacks data into a contiguous buffer before sending it, and unpacks it from a contiguous buffer after receiving it. */
/* 
    MPI_PACK(inbuf, incount, datatype, outbuf, outsize, position, comm)
    MPI_UNPACK(inbuf, insize, position, outbuf, outcount, datatype, comm)
*/
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


    if (size < 2) //only 2 proccess
    {
        printf("Please run with 2 processes.\n");fflush(stdout);
        MPI_Finalize();
        return 1;
    }

    MPI_Get_address(&tabrecord, &base);
    MPI_Get_address(&(tabrecord.name), &addr);
    disp[0] = addr - base;
    MPI_Get_address(&(tabrecord.age), &addr);
    disp[1] = addr - base;
    MPI_Get_address(&(tabrecord.city),&addr);
    disp[2] = addr - base;
    MPI_Get_address(&(tabrecord.average), &addr);
    disp[3] = addr - base;
    MPI_Get_address(&(tabrecord.favNum), &addr);
    disp[4] = addr - base;
        

    MPI_Type_create_struct(5, blen, disp, type, &new_type);
    MPI_Type_commit(&new_type);
       
    if (rank == 0) //proccess 0
    {

        strcpy(tabrecord.name, "John");
        tabrecord.age = 51;
        strcpy(tabrecord.city,"Lion");
        tabrecord.average = 9.8;
        tabrecord.favNum = 5;

        MPI_Pack(&tabrecord, 1, new_type, buffer, 110, &position, MPI_COMM_WORLD);
        MPI_Send(buffer, position, MPI_PACKED, 1, 110, MPI_COMM_WORLD);
    }

    if (rank == 1) //proccess 1
    {
        strcpy(tabrecieved.name, "Peter");
        tabrecieved.age = 14;
        strcpy(tabrecieved.city,"London");
        tabrecieved.average = 7.8;
        tabrecieved.favNum = 4;
        printf("In process %d my name is %s,my age is %d, my city is %s, my average note is %f and my favorite number is %d\n",rank,tabrecieved.name,tabrecieved.age,tabrecieved.city,tabrecieved.average,tabrecieved.favNum);      
        
        MPI_Recv(buffer, 110, MPI_PACKED, 0, 110, MPI_COMM_WORLD, &status);
        MPI_Unpack(buffer, 110, &position, &tabrecieved, 1, new_type, MPI_COMM_WORLD);

        printf("In process %d I have received all the struct:\n",rank);
        printf("\t - name: %s\n",tabrecieved.name);
        printf("\t - age: %d\n",tabrecieved.age);
        printf("\t - city: %s\n",tabrecieved.city);
        printf("\t - average: %f\n",tabrecieved.average);
        printf("\t - favorite number: %d\n",tabrecieved.favNum);   
    }
    double tf = MPI_Wtime();
    MPI_Finalize();
    printf("Time of execution data of proccess %d: %f\n",rank,tf-t0);
    return 0;
} 
