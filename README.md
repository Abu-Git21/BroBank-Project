# BroBank

## Overview

BroBank is a C programming project that simulates a transaction processing system using fundamental data structures and graph traversal algorithms.

The project processes banking transactions through a queue, maintains successful transactions using a stack for undo functionality, and uses graph traversal techniques to explore account connections.

## Features

- Processes incoming transactions using a queue
- Supports undo functionality using a stack
- Uses BFS to explore account connections
- Uses DFS to explore account connections
- Handles successful and failed transactions
- Validates transaction inputs
- Prevents failed transactions from being added to the undo stack

## Data Structures and Algorithms

### Queue

Incoming transactions are stored and processed using a FIFO queue structure.

### Stack

Successful transactions are stored in a stack to support undo functionality.

### Breadth-First Search

BFS is used to explore account connections level by level.

### Depth-First Search

DFS is used to explore account connections by following paths as deeply as possible.

## Concepts Demonstrated

- C Programming
- Data Structures
- Queues
- Stacks
- Graph Traversal
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Modular Programming
- Error Handling
- Debugging and Testing

## Building and Running

Compile the project:

```bash
make
