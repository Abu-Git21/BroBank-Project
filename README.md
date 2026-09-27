# BroBank

## Problem

BroBank processes transactions and uses stacks, queues, BFS, and DFS.

## Design

I used a queue for transactions, a stack for undo, and BFS/DFS for account connections.

## Compile and Run

`make`

`make test`

`./exercise10`

## Testing

I tested transactions, undo, BFS, DFS, and invalid inputs.

## Bug Fixed

I made sure failed transactions were not added to the undo stack.
