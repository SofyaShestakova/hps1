#ifndef HPS1_COMMON_H
#define HPS1_COMMON_H

#include <stdint-gcc.h>

void test_sort(int64_t executions_amount, int64_t elements_number, void (*sort)(uint32_t *, int64_t), char *sort_name);

#endif //HPS1_COMMON_H