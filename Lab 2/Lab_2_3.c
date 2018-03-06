#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message,value=5;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        if (myrank == 0) {
                value=123;
                printf("\nEnter any value:");
                scanf("%d",&value);
                printf("\n%d I am sending message to proc %d of value %d",myrank,1,value);
                MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("\n%d Message Sent %d",myrank,value);
                MPI_Recv(&message,1,MPI_INT,(comm_size-1),0,MPI_COMM_WORLD,&status);
                printf("\n%d Message Received Ring Completed %d",myrank,message);
        }
        else
        {
                printf("\n%d I am Preparing to receive message from %d",myrank,myrank-1);
                MPI_Recv(&message, 1, MPI_INT, myrank-1, 0,MPI_COMM_WORLD,&status);
                printf("\n%d Message received %d",myrank,message);
                if(myrank==(comm_size-1))
                {
                   printf("\n%d I am sending message to %d of value %d",myrank,0,message);
                   MPI_Send(&message,1,MPI_INT,0,0,MPI_COMM_WORLD);
                   printf("\nMessage Sent");
                }
                else{
                printf("\n%d I am sending message to proc %d of value %d",myrank,myrank+1,message);
                MPI_Send(&message,1,MPI_INT,myrank+1,0,MPI_COMM_WORLD);
                MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("\n%d Message Sent %d",myrank,value);
                MPI_Recv(&message,1,MPI_INT,(comm_size-1),0,MPI_COMM_WORLD,&status);
                printf("\n%d Message Received Ring Completed %d",myrank,message);
        }
        else
        {
                printf("\n%d I am Preparing to receive message from %d",myrank,myrank-1);
                MPI_Recv(&message, 1, MPI_INT, myrank-1, 0,MPI_COMM_WORLD,&status);
                printf("\n%d Message received %d",myrank,message);
                if(myrank==(comm_size-1))
                {
                   printf("\n%d I am sending message to %d of value %d",myrank,0,message);
                   MPI_Send(&message,1,MPI_INT,0,0,MPI_COMM_WORLD);
                   printf("\nMessage Sent");
                }
                else{
                printf("\n%d I am sending message to proc %d of value %d",myrank,myrank+1,message);
                MPI_Send(&message,1,MPI_INT,myrank+1,0,MPI_COMM_WORLD);
                printf("\nMessage Sent");}
        }
        MPI_Finalize();
        return 0;
}

