#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message;
        int value1,value2,sum;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        if (myrank == 0) { int v;
                value1=123;
                printf("\n%d I am Sending message to proc %d of value %d",myrank,1,value1);
                MPI_Send(&value1, 1, MPI_INT,1, 0, MPI_COMM_WORLD);
                printf("\n%d Message sent",myrank);
                MPI_Recv(&v,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
                printf("\nSum Received %d",v);
        }
        else
        {       value2=321;
                printf("\n%d I am preparing to receive message from %d",myrank,0);
                MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                printf("\n%d Message received %d\n",myrank, message);
                sum=value2+message;
                printf("\n%d Sending sum",myrank);
                MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
                printf("\n%d Sum Sent",myrank);
        }
        MPI_Finalize();
        return 0;
}

