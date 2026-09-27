#include <stddef.h>
#include "josephus.h"

int josephusSurvivor(int n, int k, int eliminated[], int *count) {

    if (count != NULL) {
        *count = 0;
    }

    if (n <= 0 || k <= 0) {
        return -1;
    }

    Queue q;
    queueInit(&q);

    for (int i = 1; i <= n; i++) {
        if (!enqueue(&q, i)) {
            return -1;
        }
    }

    int removed_count = 0;

    while (q.count > 1) {

        for (int i = 0; i < k - 1; i++) {
            int person;

            if (!dequeue(&q, &person)) {
                return -1;
            }

            if (!enqueue(&q, person)) {
                return -1;
            }
        }

        int removed;

        if (!dequeue(&q, &removed)) {
            return -1;
        }

        if (eliminated != NULL) {
            eliminated[removed_count] = removed;
        }

        removed_count++;
    }

    int survivor;

    if (!dequeue(&q, &survivor)) {
        return -1;
    }

    if (count != NULL) {
        *count = removed_count;
    }

    return survivor;
}