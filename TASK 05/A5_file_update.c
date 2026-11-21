#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[32];
    double balance;
} Account;

int main(void) {
    const char *filename = "accounts.dat";
    Account initial[] = {
        {1, "Anu", 1000.0},
        {2, "Binu", 1500.0},
        {3, "Chitra", 800.0}
    };
    FILE *fp = fopen(filename, "wb+");
    if (fp == NULL) { perror(filename); return 1; }

    if (fwrite(initial, sizeof initial[0], 3, fp) != 3) {
        perror("initial write"); fclose(fp); return 1;
    }

    int target_id = 2, found = 0;
    Account item;
    rewind(fp);
    while (fread(&item, sizeof item, 1, fp) == 1) {
        if (item.id == target_id) {
            item.balance += 250.0;
            long offset = ftell(fp) - (long)sizeof item;
            if (fseek(fp, offset, SEEK_SET) != 0 ||
                fwrite(&item, sizeof item, 1, fp) != 1) {
                perror("update"); fclose(fp); return 1;
            }
            found = 1;
            break;
        }
    }
    if (ferror(fp)) { perror("read"); fclose(fp); return 1; }
    fclose(fp);

    printf("Account %d %s.\\n", target_id, found ? "updated" : "not found");
    return 0;
}
