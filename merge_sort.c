#include <stdlib.h>
#include <stdint-gcc.h>
#include <memory.h>

//Merging 2 sorted subarrays into one tmp array
void merge(uint32_t * X, int64_t n, uint32_t * tmp) {
    int64_t i = 0;
    int64_t j = n/2;
    int64_t ti = 0;
    //i will iterate till first  half anf J will iterate for 2nd half of array
    while (i<n/2 && j<n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        } else {
            tmp[ti] = X[j];
            ti++;
            j++;
        }
    }
    while (i<n/2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++;
        i++;
    }
    while (j<n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++;
        j++;
    }
    //Copy sorted array tmp back to  X (Original array)
    memcpy(X, tmp, n*sizeof(int));

} // end of merge()

void call_merge_sort(uint32_t * X, int64_t n, uint32_t * tmp)
{
    if (n < 2) return;

    call_merge_sort(X, n/2, tmp);
    call_merge_sort(X+(n/2), n-(n/2), tmp);

    merge(X, n, tmp);
}

void call_parallel_merge_sort(uint32_t * X, int64_t n, uint32_t * tmp) {
//#pragma omp parallel
    if (n < 2) return;

    #pragma omp task firstprivate (X, n, tmp)
    call_merge_sort(X, n/2, tmp);

    #pragma omp task firstprivate (X, n, tmp)
    call_merge_sort(X+(n/2), n-(n/2), tmp);

    //Wait for both paralel tasks to complete execution
    #pragma omp taskwait

    /* merge sorted halves into sorted list */
    merge(X, n, tmp);
}

void merge_sort(uint32_t *array, int64_t size) {
    uint32_t *tmp = (uint32_t*) malloc(size * sizeof(uint32_t));
    call_merge_sort(array, size, tmp);
    free(tmp);
}

void parallel_merge_sort(uint32_t *array, int64_t size) {
    uint32_t *tmp = (uint32_t*) malloc(size * sizeof(uint32_t));
    #pragma omp parallel
    {
        #pragma omp single
        call_parallel_merge_sort(array, size, tmp);
    }
    free(tmp);
}

