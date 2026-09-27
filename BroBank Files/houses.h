#ifndef HOUSES_H
#define HOUSES_H

typedef struct {
    char street[21];
    int number;
    float price;
    int months;
    float likelihood;
} House;

House *houses_read(const char *filename, int *count);
void houses_calculate_likelihood(House houses[], int count);
void houses_sort(House houses[], int count);
int houses_select(const House houses[], int count, float budget,
                  int selected[], int capacity);

#endif