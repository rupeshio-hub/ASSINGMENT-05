#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int parse_int(const char *text, int *out) {
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\\0' ||
        value < INT_MIN || value > INT_MAX) return 0;
    *out = (int)value;
    return 1;
}

int main(void) {
    char line[128];
    int value;
    printf("Enter an integer: ");
    if (fgets(line, sizeof line, stdin) == NULL) {
        fprintf(stderr, "No input received.\\n");
        return 1;
    }
    /* Reject an overlong line rather than silently accepting a prefix. */
    if (line[0] != '\\0' && line[sizeof line - 2] != '\\n' &&
        line[sizeof line - 2] != '\\0') {
        int ch;
        while ((ch = getchar()) != '\\n' && ch != EOF) { }
        fprintf(stderr, "Input line too long.\\n");
        return 1;
    }
    char *newline = line;
    while (*newline && *newline != '\\n') newline++;
    *newline = '\\0';

    if (!parse_int(line, &value)) {
        fprintf(stderr, "Invalid integer.\\n");
        return 1;
    }
    printf("Accepted value = %d\\n", value);
    return 0;
}
