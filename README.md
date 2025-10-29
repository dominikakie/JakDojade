# JakDojade

**JakDojade** is a C++ program that calculates the shortest path between cities on a grid-based map. The program uses BFS for finding direct paths and Dijkstra's algorithm for shortest route calculations between cities. It also supports additional flights with custom distances.

---

## Features

- Parse a grid map to identify cities.
- Find direct paths between cities using **BFS**.
- Calculate shortest paths using **Dijkstra's algorithm**.
- Handle additional flights with custom distances.
- Print the shortest path and optionally the route with city names.

---

## File Structure

- `JakDojadeAIDS.cpp` – main program and all algorithm implementations.
- `Structure.h` – data structures (City, LinkedList, Point, Position).

---

## How to Compile and Run

```bash
g++ -o JakDojadeAIDS JakDojadeAIDS.cpp
./JakDojadeAIDS
