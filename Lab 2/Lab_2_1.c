#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message;
        int value;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        value=2;
        if (myrank == 0) {
                printf("%d I am Preparing to send message to proc %d of value %d\n",myrank,1,value);
                MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("\n%d Message sent %d",myrank, value);
        }
        else
        {
                printf("\n%d I am preparing to receive message from %d",myrank,0);
                MPI_Recv(&message, 1, MPI_INT,0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("\n%d received %d\n",myrank,message);
        }
        MPI_Finalize();
        return 0;
}

