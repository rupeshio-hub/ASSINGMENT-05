#include <stdio.h>

static unsigned long long calls = 0;

unsigned long long factorial(unsigned int n) {
    calls++;
    if (n <= 1U) return 1ULL;
    return (unsigned long long)n * factorial(n - 1U);
}

int main(void) {
    unsigned int n;
    printf("Enter n (0-20): ");
    if (scanf("%u", &n) != 1 || n > 20U) {
        fprintf(stderr, "Invalid input. Enter an integer from 0 to 20.\\n");
        return 1;
    }
    printf("%u! = %llu\\n", n, factorial(n));
    printf("Recursive calls = %llu\\n", calls);
    return 0;
}
