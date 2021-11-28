
void insertion_sort(int a[], int n, int stride) {
    for (int j = stride; j < n; j += stride) {
        int key = a[j];
        int i = j - stride;
        while (i >= 0 && a[i] > key) {
            a[i + stride] = a[i];
            i -= stride;
        }
        a[i + stride] = key;
    }
}

void shell_sort(int array[], int n) {
    int i, m;
    for (m = n / 2; m > 0; m /= 2) {
        for (i = 0; i < m; i++)
            insertion_sort(&(array[i]), n - i, m);
    }
}

void parallel_shell_sort(int array[], int n) {
    int i, m;
    for (m = n / 2; m > 0; m /= 2) {
        #pragma omp parallel for shared(array, m, n) private (i) default(none)
        for (i = 0; i < m; i++)
            insertion_sort(&(array[i]), n - i, m);
    }
}