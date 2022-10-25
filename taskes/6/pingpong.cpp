// INF205 Tutorial w42 #3, "MPI send-receive ping-pong"
// katla.maria.meyer@nmbu.no
// 20221024

#include <iostream>
#include <mpi.h>

// No .h file, since we don't have anything global, and this is a program of very limited scope.

using namespace std;

// We don't need any arguments today, but MPI might want to see they're empty, so we pass them on.
int main(int argc, char *argv[])
{
	int size;		// # of ranks (not quite threads but close)
	int rank;		// current rank
	int token = 0;		// "ping-pong ball"
	int maxtoken = 1000000;	// when to stop

	// Starting up MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

// Using tags 0 (r0>r1) and 1 (r1>r0), denoting rank of sender.
while (token < (maxtoken+1)) {

	// Rank 0 sends first, and so quits upon having sent the max token.
	if (rank == 0) {
		MPI_Send(&token,1,MPI_INT,1,0,MPI_COMM_WORLD);
		if (token == maxtoken) {
			break;
		}
		MPI_Recv(&token,1,MPI_INT,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		token++;
	}
	// Rank 1 receives first, and so quits upon having received the max token.
	else {
		MPI_Recv(&token,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		if (token==maxtoken) {
			cout << "Max token received, terminating.\n";
			break;
		}
		token++;
		MPI_Send(&token,1,MPI_INT,0,1,MPI_COMM_WORLD);
	}
}

	// A barrier makes sure the ranks only progress in order. This is not very parallel, but then neither is pingpong.
	MPI_Barrier(MPI_COMM_WORLD);

	// Shut down MPI
	MPI_Finalize();
	return 0;
}
