# Shortest Paths in C

Welcome to the "Shortest Paths in C" repository! This repository contains an implementation of Dijkstra's algorithm for finding the shortest paths in a weighted graph using a priority queue.

## Overview

Dijkstra's algorithm is a fundamental algorithm in graph theory used to find the shortest path from a starting node to all other nodes in a weighted graph. It efficiently determines the shortest path by iteratively selecting the closest unvisited node and updating the path distances.

### How Dijkstra's Algorithm Works

1. **Initialization**: Start by initializing the distance to the source node as 0 and all other nodes as infinity. Use a priority queue to store nodes to be processed, prioritized by their current shortest distance.

2. **Priority Queue**: Extract the node with the smallest distance from the priority queue. This node is considered as the "current node."

3. **Distance Update**: For each neighboring node of the current node, check if the path through the current node is shorter than the previously known shortest path. Update the distance and add the neighboring node to the priority queue if necessary.

4. **Repeat**: Continue the process until all nodes have been visited and the shortest path to each node has been determined.

5. **Output**: The result is a set of shortest paths from the source node to all other nodes in the graph.

## Repository Structure

The repository is organized as follows:

- **`entrada/`**: Contains input files (`entrada10.csv`, `entrada50.csv`, etc.) with graph data for testing.
- **`resposta/`**: Contains output files (`saida10.csv`, `saida50.csv`, etc.) with the results of the shortest path calculations.
- **`PQ.c`** and **`PQ.h`**: Implementation of the priority queue used by the algorithm.
- **`aresta.c`** and **`aresta.h`**: Implementation of edge-related functionalities.
- **`grafo.c`** and **`grafo.h`**: Implementation of graph-related functionalities, and Dijkstra's Algorithm.
- **`item.h`**: Defines the data structures used in the algorithm.
- **`main.c`**: Contains the main function to execute the algorithm.
- **`makefile`**: Build script for compiling the code.

## How to Use

1. **Clone the Repository**: Clone the repository to your local machine:
   ```bash
   git clone https://github.com/ThiagoLahass/Shortest-Paths_in_C
   ```

2. **Navigate to the Directory**: Go to the repository directory:
    ```bash
    cd Shortest-Paths_in_C
    ```

3. **Compile the Code**: Use the `makefile` to compile the project:
    ```bash
    make
    ```

4. **Run the Program**: Execute the compiled program with your input files:
    ```bash
    ./main entrada/entrada10.csv saida/saida10.csv
    ```
5. **Check Results**: Review the output files in the `resposta/` directory for the results.

## Acknowledgments
Thank you for visiting this repository! If you found this implementation useful, please consider giving it a star ⭐ to support and help others find this content.

We appreciate your interest and contributions!
