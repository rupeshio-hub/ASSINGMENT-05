#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[32];
    double amount;
} Record;

int main(void) {
    const char *text_name = "records.txt";
    const char *binary_name = "records.bin";
    Record records[] = {
        {101, "Asha", 1250.50},
        {102, "Bala", 980.00},
        {103, "Charan", 2100.75}
    };
    size_t n = sizeof records / sizeof records[0];

    FILE *fp = fopen(text_name, "w");
    if (fp == NULL) { perror(text_name); return 1; }
    for (size_t i = 0; i < n; i++)
        if (fprintf(fp, "%d %s %.2f\\n", records[i].id,
                    records[i].name, records[i].amount) < 0) {
            perror("write text"); fclose(fp); return 1;
        }
    if (fclose(fp) != 0) { perror("close text"); return 1; }

    fp = fopen(binary_name, "wb");
    if (fp == NULL) { perror(binary_name); return 1; }
    if (fwrite(records, sizeof records[0], n, fp) != n) {
        perror("write binary"); fclose(fp); return 1;
    }
    if (fclose(fp) != 0) { perror("close binary"); return 1; }

    Record loaded[3];
    fp = fopen(binary_name, "rb");
    if (fp == NULL) { perror(binary_name); return 1; }
    size_t got = fread(loaded, sizeof loaded[0], 3, fp);
    if (ferror(fp)) { perror("read binary"); fclose(fp); return 1; }
    fclose(fp);

    printf("Wrote %zu records; read back %zu binary records.\\n", n, got);
    for (size_t i = 0; i < got; i++)
        printf("%d %-10s %.2f\\n", loaded[i].id, loaded[i].name, loaded[i].amount);
    return got == n ? 0 : 1;
}
