#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

void all2allPersHC(int *inmsg, int *outmsg, int myrank, int commSize){
        MPI_Status status;
        outmsg[myrank]=inmsg[myrank];
        int next=myrank+1,prev=myrank-1;
        int i=0,j=0,v=0,s,r,buf[commSize-1],outbuf[commSize-1];
        if(myrank==0)
        {
                prev=commSize-1;
        }
        if(myrank==commSize-1)  {
                next=0;
        }
        for(i=0,j=myrank+1;i<(commSize-1);i++,j++)
        {
                if(j==commSize)
                {
                        j=0;
                }
                buf[i]=inmsg[j];
        }
        for(i=0;i<(commSize-1);i++)
        {
                printf("%d,",buf[i]);
        }
        printf("%d I am Sending the Message\n",myrank);
        MPI_Send(buf,(commSize-1),MPI_INT,next,0,MPI_COMM_WORLD);
        printf("%d Message Sent\n",myrank);
        for(i=1,j=0,v=myrank-1;i<commSize;i++,j++,v--)
        {
                printf("%d I am preparing to receive the message\n",myrank);
                MPI_Recv(buf,(commSize-1-j),MPI_INT,prev,0,MPI_COMM_WORLD,&status);
                printf("%d Message Received %d\n",myrank,buf[0]);
                fflush(stdout);
               if(v<0)
                {
                        v=commSize-1;
                }
                outmsg[v]=buf[0];

                printf("%d I am Sending the message\n",myrank);
                MPI_Send(&buf[1],(commSize-1-i),MPI_INT,next,0,MPI_COMM_WORLD);
                printf("%d Message Sent\n",myrank);

        }
}
int main(int argc, char **argv) {
        int myrank;
        int comm_size;
        int message;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        int *inMsg=new int[comm_size];
        int *outMsg=new int[comm_size];

        for(int i=0;i<comm_size;i++)
        {       inMsg[i]=1000*myrank+i;
        }
        all2allPersHC(inMsg, outMsg, myrank, comm_size);

        printf("\n%d)\n",myrank);

        for(int i=0;i<comm_size;i++)
                printf("%d,",outMsg[i]);

        MPI_Finalize();
        return 0;
}

