#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int send_number;
    int recv_number;
    MPI_Status status;
    double start_time, end_time;
    int size = sizeof(int);  // Size of the data being sent/received

    if (world_rank == 0) {
        send_number = -1;
        start_time = MPI_Wtime();  // Start timing

        // Process 0 sends a message to Process 1 and receives a message from Process 1
        MPI_Sendrecv(&send_number, 1, MPI_INT, 1, 0, &recv_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

        end_time = MPI_Wtime();  // End timing
        printf("Process 0 sent number %d and received number %d from process 1\n", send_number, recv_number);

        // Calculate and print bandwidth
        double bandwidth = size / (end_time - start_time); // Bandwidth in bytes per second
        printf("Bandwidth (Process 0): %f bytes/sec\n", bandwidth);

    } else if (world_rank == 1) {
        send_number = -2;
        start_time = MPI_Wtime();  // Start timing

        // Process 1 sends a message to Process 0 and receives a message from Process 0
        MPI_Sendrecv(&send_number, 1, MPI_INT, 0, 0, &recv_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        end_time = MPI_Wtime();  // End timing
        printf("Process 1 sent number %d and received number %d from process 0\n", send_number, recv_number);

        // Calculate and print bandwidth
        double bandwidth = size / (end_time - start_time); // Bandwidth in bytes per second
        printf("Bandwidth (Process 1): %f bytes/sec\n", bandwidth);
    }

    MPI_Finalize();
    return 0;
}