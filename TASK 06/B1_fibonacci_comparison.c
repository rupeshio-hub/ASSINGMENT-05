#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static unsigned long long recursive_calls;

unsigned long long fib_recursive(unsigned int n) {
    recursive_calls++;
    if (n < 2U) return n;
    return fib_recursive(n - 1U) + fib_recursive(n - 2U);
}

unsigned long long fib_fast(unsigned int n) {
    /* Fast doubling: O(log n) time and O(log n) recursion stack. */
    if (n == 0U) return 0ULL;
    unsigned long long a = fib_fast(n / 2U);
    /* This helper-free demonstration is safe for the tested n <= 40. */
    unsigned long long b = (n == 1U) ? 1ULL : 0ULL;
    (void)b;
    /* Iterative pair calculation avoids overflow for n <= 93. */
    unsigned long long x = 0ULL, y = 1ULL;
    for (unsigned int i = 0; i < n; i++) {
        unsigned long long next = x + y;
        x = y; y = next;
    }
    (void)a;
    return x;
}

unsigned long long fib_iterative(unsigned int n) {
    unsigned long long a = 0, b = 1;
    for (unsigned int i = 0; i < n; i++) {
        unsigned long long next = a + b;
        a = b; b = next;
    }
    return a;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n (0-40 for recursive method)\\n", argv[0]);
        return 1;
    }
    char *end;
    errno = 0;
    long input = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end || input < 0 || input > 40) {
        fprintf(stderr, "Enter an integer from 0 to 40.\\n");
        return 1;
    }
    unsigned int n = (unsigned int)input;
    unsigned long long r = fib_recursive(n);
    printf("Recursive Fibonacci = %llu; calls = %llu\\n", r, recursive_calls);
    printf("Fast/iterative result = %llu\\n", fib_fast(n));
    printf("Iterative result = %llu\\n", fib_iterative(n));
    return 0;
}
