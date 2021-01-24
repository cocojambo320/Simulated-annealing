//
// Created by mikolaj on 19.12.2020.
//

#ifndef SIMULATED_ANNEALING_GRAPH_H
#define SIMULATED_ANNEALING_GRAPH_H


#include <string>
#include <vector>
#include "SquareMatrix.h"

class Graph
{
private:
    SquareMatrix* adjacencyMatrix;
    int nodesCount;

public:
    Graph(int nodes_count);
    Graph();
    ~Graph();
    SquareMatrix* getAdjacencyMatrix();
    int getWeight(int from, int to);
    bool reset(int new_nodes_count);
    int getNodesCount();
    std::string toString();
    bool empty();
};


#endif //SIMULATED_ANNEALING_GRAPH_H
