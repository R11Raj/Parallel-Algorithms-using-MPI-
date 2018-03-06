#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>
#include<math.h>

int main(int argc, char **argv)
{
        void OnetoAll_BC(int,int,int &);
        int myrank;
        int comm_size;
        int message=-1;
        int d=3;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        if(myrank==0)
                message=99;


        OnetoAll_BC(d,myrank,message);

        printf("\n%d message=%d\n",myrank, message);
        MPI_Finalize();
        return 0;
}
void OnetoAll_BC(int d,int myrank,int &message)
{
    MPI_Status status;
    int i,x,mask;
    x=pow(2,d);
    mask=x-1;
    int msgdest,msgsource;
    for(i=d-1;i>=0;i--)
    {
  x=pow(2,i);
         mask=mask ^ x;
         if((myrank & mask)==0)
         {
                x=pow(2,i);
                if((myrank & x)==0)
                {       x=pow(2,i);
                        msgdest=myrank ^ x;
                        printf("\nI am Preparing to send the message my id:%d and message:%d",myrank,message);
                        MPI_Send(&message,1,MPI_INT,msgdest,0,MPI_COMM_WORLD);
                        printf("\nMessage Sent by id:%d",myrank);
                }
                else
                {       x=pow(2,i);
                        msgsource=myrank ^ x;
                        printf("\nI am Preparing to receive message and my  id:%d",myrank);
                        MPI_Recv(&message,1,MPI_INT,msgsource,0,MPI_COMM_WORLD,&status);
                        printf("\nI have received message:%d and my id:%d",message,myrank);
                }
        }
        if((myrank & mask)==0)
         {
                x=pow(2,i);
                if((myrank & x)==0)
                {       x=pow(2,i);
                        msgdest=myrank ^ x;
                        printf("\nI am Preparing to send the message my id:%d and message:%d",myrank,message);
                        MPI_Send(&message,1,MPI_INT,msgdest,0,MPI_COMM_WORLD);
                        printf("\nMessage Sent by id:%d",myrank);
                }
                else
                {       x=pow(2,i);
                        msgsource=myrank ^ x;
                        printf("\nI am Preparing to receive message and my  id:%d",myrank);
                        MPI_Recv(&message,1,MPI_INT,msgsource,0,MPI_COMM_WORLD,&status);
                        printf("\nI have received message:%d and my id:%d",message,myrank);
                }
        }
    }
}

