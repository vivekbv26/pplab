#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void sequentialMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (r + l) / 2;
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (r + l) / 2;

        // Implementing cut-off level for parallelization
        if (r-l > 1000) {  // Assume 1000 is the appropriate cut-off, adjust as per your tests
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    parallelMergeSort(arr, l, m);
                }
                #pragma omp section
                {
                    parallelMergeSort(arr, m + 1, r);
                }
            }
        } else {
            sequentialMergeSort(arr, l, m);
            sequentialMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}


int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // Random values between 0 and 99
    }

    int seqArr[n], parArr[n];
    for (int i = 0; i < n; i++) {
        seqArr[i] = arr[i];
        parArr[i] = arr[i];
    }


    double start = omp_get_wtime();
    sequentialMergeSort(seqArr, 0, n-1);
    double end = omp_get_wtime();
    printf("Time taken for sequential sort: %lf seconds\n", (end - start));

    start = omp_get_wtime();
    parallelMergeSort(parArr, 0, n-1);
    end =omp_get_wtime();
    printf("Time taken for parallel sort: %lf seconds\n", (end - start));

    return 0;
}