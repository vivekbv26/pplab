#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 10000000  

int main() {
    double pi = 0.0;

    // Serial computation
    double start_time = omp_get_wtime();
    for (int k = 0; k < NUM_STEPS; k++) {
        pi += (4.0 * (k % 2 == 0 ? 1.0 : -1.0)) / (2.0 * k + 1.0);
    }
    double end_time = omp_get_wtime();
    printf("Serial version: pi = %0.12f, time = %f seconds\n", pi, end_time - start_time);

    // Resetting pi for parallel computation
    pi = 0.0;
    
    // Parallel computation
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:pi) 
    for (int k = 0; k < NUM_STEPS; k++) {
        pi += (4.0 * (k % 2 == 0 ? 1.0 : -1.0)) / (2.0 * k + 1.0);
    }
    end_time = omp_get_wtime();
    printf("Parallel version: pi = %0.12f, time = %f seconds\n", pi, end_time - start_time);

    return 0;
}
