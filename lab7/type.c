#include<stdio.h>
#include<mpi.h>
#include<string.h>

typedef struct {
	char name[20];
	int age;
	char city[20];
	float average;
	int favNum;
} Data;


int main(int argc, char **argv)
{
	int rank, size, r;
	int src, dst, tag, i;	
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

	if(rank == 0) 
		printf("MPI_Type_create_struct()\n");

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

	if(rank != 0)
	{
		strcpy(tabrecieved.name, "Peter");
		tabrecieved.age = 14;
		strcpy(tabrecieved.city,"London");
		tabrecieved.average = 7.8;
		tabrecieved.favNum = 4;
		printf("In process %d my name is %s,my age is %d, my city is %s, my average note is %f and my favorite number is %d\n",rank,tabrecieved.name,tabrecieved.age,tabrecieved.city,tabrecieved.average,tabrecieved.favNum);		
		MPI_Recv(&tabrecieved, 1, new_type, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("In process %d I have received:\n",rank);
		printf("\t - name: %s\n",tabrecieved.name);
		printf("\t - age: %d\n",tabrecieved.age);
		printf("\t - city: %s\n",tabrecieved.city);
		printf("\t - average: %f\n",tabrecieved.average);
		printf("\t - favorite number: %d\n",tabrecieved.favNum);
	}
	else
	{
		strcpy(tabrecord.name, "John");
		tabrecord.age = 51;
		strcpy(tabrecord.city,"Lion");
		tabrecord.average = 9.8;
		tabrecord.favNum = 5;
		for (r=1; r<size; r++)
			MPI_Send(&tabrecord, 1, new_type, r, 0, MPI_COMM_WORLD);
	}
	//MPI_Barrier(MPI_COMM_WORLD);
	double tf = MPI_Wtime();
	MPI_Finalize();
	printf("Time of sendind data of proccess %d: %f\n",rank,tf-t0);
	return 0;
}

