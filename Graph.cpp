//
// Created by mikolaj on 19.12.2020.
//

#include "Graph.h"
#include <vector>
#include <algorithm>

Graph::Graph(int nodes_count)
{
    if (nodes_count < 0)
        throw "Error: Nodes count cannot be less than 0";

    nodesCount = nodes_count;
    adjacencyMatrix = new SquareMatrix(nodes_count);
}

Graph::Graph()
{
    nodesCount = 0;
    adjacencyMatrix = new SquareMatrix(0);
}

Graph::~Graph()
{
    delete adjacencyMatrix;
}

bool Graph::reset(int new_nodes_count)
{
    if (new_nodes_count < 0)
        return false;

    delete adjacencyMatrix;

    nodesCount = new_nodes_count;

    adjacencyMatrix = new SquareMatrix(new_nodes_count);

    return true;
}

int Graph::getNodesCount()
{
    return nodesCount;
}

SquareMatrix* Graph::getAdjacencyMatrix()
{
    return adjacencyMatrix;
}

bool Graph::empty()
{
    if (nodesCount <= 0)
        return true;

    if (!adjacencyMatrix)
        return true;

    return false;
}

std::string Graph::toString()
{
    std::string result = "";

    result += "Nodes count: " + std::to_string(nodesCount) + "\n";

    for (int i = 0; i < nodesCount; i++)
    {
        for (int j = 0; j < nodesCount; j++)
            result += std::to_string((*adjacencyMatrix)[i][j]) + " ";

        result += "\n";
    }

    return result;
}

int Graph::getWeight(int from, int to)
{
    return (*adjacencyMatrix)[from][to];
}
