#include <stdio.h>
#include <stdlib.h>

#include "houses.h"

House *houses_read(const char *filename, int *count) {
    if (filename == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        return NULL;
    }

    int n;

    if (fscanf(fp, "%d", &n) != 1 || n <= 0) {
        fclose(fp);
        return NULL;
    }

    House *houses = malloc(n * sizeof(House));

    if (houses == NULL) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%20s %d %f %d",
                   houses[i].street,
                   &houses[i].number,
                   &houses[i].price,
                   &houses[i].months) != 4) {

            free(houses);
            fclose(fp);
            return NULL;
        }

        houses[i].likelihood = 0.0f;
    }

    fclose(fp);

    *count = n;

    return houses;
}

void houses_calculate_likelihood(House houses[], int count) {
    if (houses == NULL || count <= 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        if (houses[i].price > 0.0f) {
            houses[i].likelihood =
                0.5f * (1.0f / (houses[i].price / 10000.0f))
                + 0.5f * houses[i].months;
        }
        else {
            houses[i].likelihood = 0.0f;
        }
    }
}

void houses_sort(House houses[], int count) {
    if (houses == NULL || count <= 0) {
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {

            int swap = 0;

            if (houses[j].likelihood < houses[j + 1].likelihood) {
                swap = 1;
            }
            else if (houses[j].likelihood == houses[j + 1].likelihood &&
                     houses[j].price > houses[j + 1].price) {
                swap = 1;
            }

            if (swap) {
                House temp = houses[j];
                houses[j] = houses[j + 1];
                houses[j + 1] = temp;
            }
        }
    }
}

int houses_select(const House houses[], int count, float budget,
                  int selected[], int capacity) {
    if (houses == NULL || selected == NULL ||
        count <= 0 || budget < 0.0f || capacity <= 0) {
        return 0;
    }

    float remaining = budget;
    int selected_count = 0;

    for (int i = 0; i < count && selected_count < capacity; i++) {
        if (houses[i].price <= remaining) {
            selected[selected_count] = i;
            selected_count++;

            remaining -= houses[i].price;
        }
    }

    return selected_count;
}