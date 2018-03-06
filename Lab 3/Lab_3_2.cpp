#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        if (myrank == 0)
        {
                message=99;
                printf("\nI am preparing to Broadcast Message my id is %d and message is %d",myrank,message);
        }
        MPI_Bcast(&message,1,MPI_INT,0,MPI_COMM_WORLD);
        if(myrank!=0){
                printf("\nI am preparing to receive message my id is %d",myrank);
                printf("\n%d I have received the message %d",myrank,message);
        }
        if(myrank==0)
        {
                printf("\n%d Message Broadcasted\n",myrank);
        }
        MPI_Finalize();
        return 0;
}

