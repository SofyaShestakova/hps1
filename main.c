#include <stdio.h>
#include "shell_sort.c"
#include "merge_sort.c"
#include "common.h"

int main() {
    int64_t executions_amount, array_size;

    printf("Input executions_amount: ");
    scanf("%ld", &executions_amount);

    printf("Input array_size: ");
    scanf("%ld", &array_size);

    test_sort(executions_amount, array_size, &merge_sort, "merge_sort");
    test_sort(executions_amount, array_size, &parallel_merge_sort, "parallel_merge_sort");

    test_sort(executions_amount, array_size, &shell_sort, "shell_sort");
    test_sort(executions_amount, array_size, &parallel_shell_sort, "parallel_shell_sort");

    return 0;
}