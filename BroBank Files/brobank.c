#include <string.h>

#include "brobank.h"

void brobank_init(BroBank *bank, int account_count) {
    if (bank == NULL) {
        return;
    }

    memset(bank, 0, sizeof *bank);

    if (account_count < 0 || account_count > BROBANK_MAX_ACCOUNTS) {
        bank->account_count = 0;
    }
    else {
        bank->account_count = account_count;
    }

    bank->p_rear = -1;
    bank->undo_top = -1;
}

int brobankSubmit(BroBank *bank, Transaction tx) {
    if (bank == NULL) {
        return 0;
    }

    if (bank->p_count >= CAPACITY) {
        return 0;
    }

    bank->p_rear = (bank->p_rear + 1) % CAPACITY;
    bank->pending[bank->p_rear] = tx;
    bank->p_count++;

    return 1;
}

int brobankProcessNext(BroBank *bank) {
    if (bank == NULL || bank->p_count == 0) {
        return 0;
    }

    Transaction tx = bank->pending[bank->p_front];

    bank->p_front = (bank->p_front + 1) % CAPACITY;
    bank->p_count--;

    if (bank->undo_top >= CAPACITY - 1) {
        return 0;
    }

    if (tx.type == TX_DEPOSIT) {
        if (tx.from < 0 || tx.from >= bank->account_count ||
            tx.amount < 0.0) {
            return 0;
        }

        bank->balances[tx.from] += tx.amount;
    }

    else if (tx.type == TX_WITHDRAW) {
        if (tx.from < 0 || tx.from >= bank->account_count ||
            tx.amount <= 0.0 ||
            tx.amount > bank->balances[tx.from]) {
            return 0;
        }

        bank->balances[tx.from] -= tx.amount;
    }

    else if (tx.type == TX_TRANSFER) {
        if (tx.from < 0 || tx.from >= bank->account_count ||
            tx.to < 0 || tx.to >= bank->account_count ||
            tx.amount <= 0.0 ||
            tx.amount > bank->balances[tx.from]) {
            return 0;
        }

        bank->balances[tx.from] -= tx.amount;
        bank->balances[tx.to] += tx.amount;

        bank->graph[tx.from][tx.to] = 1;
    }

    else {
        return 0;
    }

    bank->undo_top++;
    bank->undo[bank->undo_top] = tx;

    return 1;
}

int brobankUndo(BroBank *bank) {
    if (bank == NULL || bank->undo_top < 0) {
        return 0;
    }

    Transaction tx = bank->undo[bank->undo_top];

    if (tx.type == TX_DEPOSIT) {
        bank->balances[tx.from] -= tx.amount;
    }

    else if (tx.type == TX_WITHDRAW) {
        bank->balances[tx.from] += tx.amount;
    }

    else if (tx.type == TX_TRANSFER) {
        bank->balances[tx.from] += tx.amount;
        bank->balances[tx.to] -= tx.amount;
    }

    else {
        return 0;
    }

    bank->undo_top--;

    return 1;
}

int brobankBFS(const BroBank *bank, int source, int destination) {
    if (bank == NULL ||
        source < 0 || source >= bank->account_count ||
        destination < 0 || destination >= bank->account_count) {
        return -1;
    }

    if (source == destination) {
        return 0;
    }

    int visited[BROBANK_MAX_ACCOUNTS] = {0};
    int distance[BROBANK_MAX_ACCOUNTS] = {0};

    Queue q;
    queueInit(&q);

    visited[source] = 1;

    if (!enqueue(&q, source)) {
        return -1;
    }

    while (!queueIsEmpty(&q)) {
        int current;

        if (!dequeue(&q, &current)) {
            return -1;
        }

        for (int i = 0; i < bank->account_count; i++) {
            if (bank->graph[current][i] && !visited[i]) {
                visited[i] = 1;
                distance[i] = distance[current] + 1;

                if (i == destination) {
                    return distance[i];
                }

                if (!enqueue(&q, i)) {
                    return -1;
                }
            }
        }
    }

    return -1;
}

int brobankDFS(const BroBank *bank, int source, int destination) {
    if (bank == NULL ||
        source < 0 || source >= bank->account_count ||
        destination < 0 || destination >= bank->account_count) {
        return 0;
    }

    int visited[BROBANK_MAX_ACCOUNTS] = {0};

    Stack s;
    stackInit(&s);

    if (!stackPush(&s, source)) {
        return 0;
    }

    while (!stackIsEmpty(&s)) {
        int current;

        if (!stackPop(&s, &current)) {
            return 0;
        }

        if (visited[current]) {
            continue;
        }

        visited[current] = 1;

        if (current == destination) {
            return 1;
        }

        for (int i = bank->account_count - 1; i >= 0; i--) {
            if (bank->graph[current][i] && !visited[i]) {
                if (!stackPush(&s, i)) {
                    return 0;
                }
            }
        }
    }

    return 0;
}