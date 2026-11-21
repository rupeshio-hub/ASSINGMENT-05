#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    long count = 100000L;
    if (argc == 2) {
        char *end;
        count = strtol(argv[1], &end, 10);
        if (*end || count < 1 || count > 5000000L) {
            fprintf(stderr, "Usage: %s [records: 1..5000000]\\n", argv[0]);
            return 1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [records]\\n", argv[0]);
        return 1;
    }

    const char *filename = "benchmark_data.txt";
    clock_t start = clock();
    FILE *fp = fopen(filename, "w");
    if (!fp) { perror(filename); return 1; }
    for (long i = 0; i < count; i++) {
        if (fprintf(fp, "%ld,Donor%ld,%ld\\n", i + 1, i + 1, (i % 5) + 1) < 0) {
            perror("write"); fclose(fp); return 1;
        }
    }
    if (fclose(fp) != 0) { perror("close"); return 1; }
    clock_t written = clock();

    fp = fopen(filename, "r");
    if (!fp) { perror(filename); return 1; }
    long lines = 0;
    char buffer[128];
    while (fgets(buffer, sizeof buffer, fp) != NULL) lines++;
    if (ferror(fp)) { perror("read"); fclose(fp); return 1; }
    fclose(fp);
    clock_t finished = clock();

    FILE *sizefp = fopen(filename, "rb");
    if (!sizefp) { perror(filename); return 1; }
    if (fseek(sizefp, 0, SEEK_END) != 0) { perror("seek"); fclose(sizefp); return 1; }
    long bytes = ftell(sizefp);
    fclose(sizefp);

    printf("Records written=%ld, lines read=%ld, file bytes=%ld\\n", count, lines, bytes);
    printf("Write CPU time=%.6f s, read CPU time=%.6f s\\n",
           (double)(written - start) / CLOCKS_PER_SEC,
           (double)(finished - written) / CLOCKS_PER_SEC);
    return lines == count ? 0 : 1;
}
