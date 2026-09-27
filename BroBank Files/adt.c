#include <stddef.h>
#include "adt.h"

void stackInit(Stack *s) {
    if (s == NULL) {
        return;
    }

    s->top = -1;
}

int stackIsEmpty(const Stack *s) {
    if (s == NULL) {
        return 1;
    }

    return s->top < 0;
}

int stackIsFull(const Stack *s) {
    if (s == NULL) {
        return 0;
    }

    return s->top == CAPACITY - 1;
}

int stackPush(Stack *s, int value) {
    if (s == NULL || stackIsFull(s)) {
        return 0;
    }

    s->top++;
    s->data[s->top] = value;

    return 1;
}

int stackPop(Stack *s, int *value) {
    if (s == NULL || value == NULL || stackIsEmpty(s)) {
        return 0;
    }

    *value = s->data[s->top];
    s->top--;

    return 1;
}

void queueInit(Queue *q) {
    if (q == NULL) {
        return;
    }

    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int queueIsEmpty(const Queue *q) {
    if (q == NULL) {
        return 1;
    }

    return q->count == 0;
}

int queueIsFull(const Queue *q) {
    if (q == NULL) {
        return 0;
    }

    return q->count == CAPACITY;
}

int enqueue(Queue *q, int value) {
    if (q == NULL || queueIsFull(q)) {
        return 0;
    }

    q->rear = (q->rear + 1) % CAPACITY;
    q->data[q->rear] = value;
    q->count++;

    return 1;
}

int dequeue(Queue *q, int *value) {
    if (q == NULL || value == NULL || queueIsEmpty(q)) {
        return 0;
    }

    *value = q->data[q->front];

    q->front = (q->front + 1) % CAPACITY;
    q->count--;

    return 1;
}