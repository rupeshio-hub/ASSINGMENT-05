#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *end = NULL;
    long count;
    int *values;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number-of-values>\\n", argv[0]);
        return 1;
    }

    errno = 0;
    count = strtol(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\\0' ||
        count < 1 || count > 1000000L || count > INT_MAX) {
        fprintf(stderr, "Count must be an integer from 1 to 1000000.\\n");
        return 1;
    }

    values = malloc((size_t)count * sizeof *values);
    if (values == NULL) {
        perror("malloc");
        return 1;
    }

    for (long i = 0; i < count; i++) {
        values[i] = (int)(i + 1);
    }

    long long sum = 0;
    for (long i = 0; i < count; i++) sum += values[i];

    printf("Allocated %ld integers; sum = %lld\\n", count, sum);
    free(values);
    values = NULL;
    return 0;
}
