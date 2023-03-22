#include <iostream>
#include <vector>
#include <mpi.h>
#include "e3int.h"
#include <map>


struct Mpin{
    SecureInt<8> num;
};


int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //std::map<int,Secure> mpin; ?? memory not in line
    Mpin *mpin;
    const int ARRAY_SIZE = 2;
    //int* window_buffer;
    MPI_Win window;
    MPI_Win_allocate(ARRAY_SIZE * sizeof(Mpin), sizeof(Mpin), MPI_INFO_NULL, MPI_COMM_WORLD, &mpin, &window);
    printf("[MPI process %d] Window created.\n", rank);

    if (size != 2)
    {
        std::cerr << "Error: This program must be run with exactly 2 processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        mpin[i].num = _5_En;
    }

    mpin[0].num  = _5_En;
    mpin[1].num  = _7_En;

    if (rank == 0)
    {
    	int a = 0 , b=1;

        //Secure a = _5_En,b = _7_En;
        //int a = 110, b = 20;
        MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&b, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        std::cout << "Rank 0: Sent " << mpin[a].num << " and " << mpin[b].num << " to Rank 1." << std::endl;

        //Secure res;
        //int res;
        //MPI_Recv(&res, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //auto sum = mpin[res];
        //std::cout << "Rank 0: Received " << sum << " from Rank 1." << std::endl;
    }
    else if (rank == 1)
    {
        //Secure a, b;
        int a,b;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout <<"hello r"<<std::endl;
        std::cout << "Rank 1: Received " << mpin[a].num << " and " << mpin[b].num << " to Rank 0." << std::endl;
        auto sum = mpin[a].num + mpin[b].num;
        //auto sum = a + b;
        //int c=2;
        //mpin[c] = sum;
        //MPI_Send(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        //std::cout << "Rank 1: Sent " << sum << " to Rank 0." << std::endl;
    }

    MPI_Win_free(&window);
    MPI_Finalize();
    return 0;
}

