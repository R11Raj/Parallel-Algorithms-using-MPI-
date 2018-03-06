#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>
void SelectionSort(float *data,float *fdata,int comm_size,int myrank,int Psize,int Tsize)
{
        MPI_Status status;
        float t;
        int m,i,j,p,k;
        struct R{
                float val;
                int lpos;
        }lmin,gmin;

        for(i=0,p=0,k=0;i<Tsize;i++,k++)
        {
                gmin.lpos=-1;
                gmin.val=-1;
                lmin.val=-1;

                if(myrank>p){
                        lmin.lpos=0;
                        for(j=0;j<Psize;j++)
                        {
                                if(data[j]<data[lmin.lpos])
                                {
                                        lmin.val=data[j];
                                        lmin.lpos=j+myrank*Psize;
                                }
                        }
                }
                else if(myrank==p)
                {       lmin.lpos=i%Psize;
                        for(j=i%Psize;j<Psize;j++)
                        {
                                if(data[j]<data[lmin.lpos])
                                {
                                        lmin.val=data[j];
                                        lmin.lpos=j+myrank*Psize;
                        }
                }
                else if(myrank==p)
                {       lmin.lpos=i%Psize;
                        for(j=i%Psize;j<Psize;j++)
                        {
                                if(data[j]<data[lmin.lpos])
                                {
                                        lmin.val=data[j];
                                        lmin.lpos=j+myrank*Psize;
                                }
                        }
                }
                else
                {
                        lmin.val=10000;
                }
                printf("\n%d  All reduce %d lmin %.1f\n",myrank,i,lmin.val);
                MPI_Allreduce(&lmin,&gmin,1,MPI_FLOAT_INT,MPI_MINLOC,MPI_COMM_WORLD);
                if(myrank==0)
                {
                        printf("\nGvalue=%.1f and Gpos=%d\n",gmin.val,gmin.lpos);
                }
                if((gmin.lpos/Psize)==p)
                {
                        t=data[i%Psize];
                        data[i%Psize]=gmin.val;
                        data[gmin.lpos%Psize]=t;
                        printf("\nSwapped value %.1f with %.1f\n",data[i%Psize],data[gmin.lpos%Psize]);
                }
                else if(myrank==p)
                {
                        t=data[i%Psize];
                        data[i%Psize]=gmin.val;
                        printf("\nvalue going to be changed %.1f by %.1f\n",t,data[i%Psize]);
                        MPI_Send(&t,1,MPI_FLOAT,(gmin.lpos/Psize),0,MPI_COMM_WORLD);
                }
                else if(myrank==(gmin.lpos/Psize))
                        {
                                MPI_Recv(&t,1,MPI_FLOAT,p,0,MPI_COMM_WORLD,&status);
                                printf("\nvalue changed %.1f by %.1f\n",data[lmin.lpos%Psize],t);
                                data[lmin.lpos%Psize]=t;
                        }

                if(k==(Psize-1))
                {
                        k=-1;
                        p++;
                }
        }
}
int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        int length=20,i,j;
        float data[length],sdata[length/comm_size];
        if(myrank==0)
        {
                for (i = 0; i < length; i++)
                {
                        if (i % 2 == 0)
                                data[i] = length - i ;
                        else
                                data[i] = length + i ;
                        printf("%.1f ",data[i]);
                }

        }
        MPI_Scatter(data,(length/comm_size),MPI_FLOAT,sdata,(length/comm_size),MPI_FLOAT,0,MPI_COMM_WORLD);

        SelectionSort(sdata,data,comm_size,myrank,(length/comm_size),length);

        MPI_Gather(sdata,Psize,MPI_FLOAT,data,Psize,MPI_FLOAT,0,MPI_COMM_WORLD);

        if(myrank==0)
        {
                for(i=0;i<length;i++)
                {
                        printf(" %.1f ",data[i]);
                }
        }
        MPI_Finalize();
        return 0;
}
