4#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

void ParallelMatrixVectorMult(float *submatrix,float *subVector,const int n,int comm_size,int myrank, float *subResult){
        float vector[n],y=0;
        MPI_Status status;
        MPI_Allgather(subVector,(n/comm_size),MPI_FLOAT,vector,(n/comm_size),MPI_FLOAT,MPI_COMM_WORLD);

        for(int j=0;j<(n/comm_size);j++)
        {
                for(int i=0;i<n;i++)
                {
                        y=y+(submatrix[i+j*n]*vector[i]);
                }
                subResult[j]=y;
        }

}
int main(int argc, char **argv) {
        const int n=100;
        int myrank;
        int comm_size;
        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        float Matrix[n*n/comm_size],subVector[n/comm_size],subresult[n/comm_size];
        for(int i=0;i<sizeof(Matrix);i++)
        {
                Matrix[i]=myrank+1.0;
        }
        for(int i=0;i<sizeof(subVector);i+)
        {
                subVector[0]=myrank+2.0;
        }

        ParallelMatrixVectorMult(Matrix,subVector,n,comm_size,myrank,subresult);

        MPI_Finalize();
        return 0;
}
