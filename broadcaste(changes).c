#include <mpi.h>
#include <stdio.h>
#include <string.h> // For using strcpy and strlen

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    char broadcast_value[100]; // Array of characters

    if (world_rank == 0) {
        // The root process sets the broadcast value
        strcpy(broadcast_value, "Hello MPI World"); // Copying a string into the array
        printf("Process 0 broadcasting value %s\n", broadcast_value);
    }

    // Use MPI_Bcast to broadcast the value
    MPI_Bcast(broadcast_value, strlen(broadcast_value) + 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Now all processes print the value received
    printf("Process %d received value %s\n", world_rank, broadcast_value);

    MPI_Finalize();
    return 0;
}