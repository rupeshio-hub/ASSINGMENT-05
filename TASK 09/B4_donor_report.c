#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

typedef struct {
    int id;
    char name[40];
    int age;
    char blood_group[4];
    int last_donation_days;
} Donor;

typedef struct {
    Donor *data;
    size_t size;
    size_t capacity;
} DonorList;

int append_donor(DonorList *list, Donor donor) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? INITIAL_CAPACITY : list->capacity * 2;
        if (new_capacity > (size_t)-1 / sizeof *list->data) return 0;
        Donor *new_data = realloc(list->data, new_capacity * sizeof *list->data);
        if (new_data == NULL) return 0;
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = donor;
    return 1;
}

int eligible(const Donor *d) {
    /* Demonstration rule: age 18-65 and at least 90 days since donation. */
    return d->age >= 18 && d->age <= 65 && d->last_donation_days >= 90;
}

int main(void) {
    DonorList donors = {NULL, 0, 0};
    const Donor sample[] = {
        {1, "Aarav", 22, "O+", 120},
        {2, "Diya", 17, "A+", 200},
        {3, "Kavin", 35, "B+", 45},
        {4, "Mira", 28, "AB+", 180},
        {5, "Nila", 66, "O-", 300},
        {6, "Rohan", 41, "A-", 95}
    };
    size_t sample_count = sizeof sample / sizeof sample[0];

    for (size_t i = 0; i < sample_count; i++) {
        if (!append_donor(&donors, sample[i])) {
            fprintf(stderr, "Memory allocation failed.\\n");
            free(donors.data);
            return 1;
        }
    }

    puts("Eligible donor report:");
    size_t eligible_count = 0;
    for (size_t i = 0; i < donors.size; i++) {
        if (eligible(&donors.data[i])) {
            printf("%d %-10s age=%d blood=%s days_since_donation=%d\\n",
                   donors.data[i].id, donors.data[i].name, donors.data[i].age,
                   donors.data[i].blood_group, donors.data[i].last_donation_days);
            eligible_count++;
        }
    }
    printf("Eligible donors=%zu, total donors=%zu\\n", eligible_count, donors.size);
    printf("Allocated capacity=%zu, memory=%zu bytes\\n",
           donors.capacity, donors.capacity * sizeof *donors.data);

    /* Always release the growable list. */
    free(donors.data);
    donors.data = NULL;
    donors.size = donors.capacity = 0;
    return 0;
}
