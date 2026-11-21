#include <stdio.h>

void swap_values(int *a, int *b) {
    if (a == NULL || b == NULL) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(const int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("index=%zu value=%d address=%p\\n",
               i, *(a + i), (void *)(a + i));
    }
}

int main(void) {
    int x = 12, y = 35;
    printf("Before swap: x=%d y=%d\\n", x, y);
    swap_values(&x, &y);
    printf("After swap:  x=%d y=%d\\n", x, y);

    int values[] = {4, 8, 15, 16, 23, 42};
    puts("Array traversal using pointer arithmetic:");
    print_array(values, sizeof values / sizeof values[0]);
    return 0;
}
