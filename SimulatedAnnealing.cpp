//
// Created by mikolaj on 19.12.2020.
//

#include "SimulatedAnnealing.h"
#define INT_MAX 2147483647

using namespace std::chrono;

SimulatedAnnealing::SimulatedAnnealing(Graph *graph, float maxTemperature, float stopTemperature, float cooling, unsigned duration) {
    this->graph = graph;
    this->maxTemperature = maxTemperature;
    this->temperature = maxTemperature;
    this->stopTemperature = stopTemperature;
    this->duration = duration;
    this->durationUntilFound = 0;
    this->cooling = cooling;

    bestPath = new Path(graph->getNodesCount());
    initializeBestPath();
}

SimulatedAnnealing::~SimulatedAnnealing() {
    delete bestPath;
}

void SimulatedAnnealing::solve() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nodes_dist(0, graph->getNodesCount() - 1);
    std::uniform_int_distribution<> probability_dist(0, INT_MAX - 1);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;

    start = high_resolution_clock::now();

    temperature = maxTemperature;

    int best_cost = bestPath->cost(graph);

    Path path(*bestPath);
    randomShuffle(path, nodes_dist, gen);

    Path path_neighbour(path);

    int neighbour_cost;

    int no_improvement = 0;
    do {
        for(int i = 0; i < graph->getNodesCount() * 2; i++)
        {
            path_neighbour = path;

            twoOptShuffle(path_neighbour, nodes_dist, gen);
            neighbour_cost = path_neighbour.cost(graph);

            if(neighbour_cost < best_cost) {
                *bestPath = path_neighbour;
                best_cost = neighbour_cost;
                durationUntilFound = duration_cast<seconds>(high_resolution_clock::now() - start).count();
            } else
            {
                no_improvement++;
            }


            if(no_improvement == 50000)
            {
                no_improvement = 0;
                randomShuffle(path, nodes_dist, gen);
            }


            if(neighbour_cost < path.cost(graph) || (float) probability_dist(gen) / INT_MAX < acceptanceProbability(best_cost, neighbour_cost, temperature))
            {
                path = path_neighbour;
                break;
            }
        }

/*
        if(duration_cast<seconds>(stop - start).count() % 15 == 0) {
            printf("best: %i  temp:  %f  prob: %f  neighbour_cost: %i\n", best_cost, temperature, acceptanceProbability(best_cost, neighbour_cost, temperature), neighbour_cost );
        }
*/


        temperature *= cooling;

        stop = high_resolution_clock::now();
    } while(temperature >= stopTemperature && duration_cast<seconds>(stop - start).count() <= duration);
}

float SimulatedAnnealing::acceptanceProbability(int best_cost, int cost, float temperature)
{
    float delta = best_cost - cost;

    return exp(delta/temperature);
}

void SimulatedAnnealing::initializeBestPath()
{
    for(int i = 0; i < graph->getNodesCount(); i++) {
        (*bestPath)[i] = i;
    }
}

void SimulatedAnnealing::twoOptShuffle(Path &path, std::uniform_int_distribution<> &dist, std::mt19937 &gen) {
    int node1, node2;

    do {
        node1 = dist(gen);
        node2 = dist(gen);
    } while(node1 == node2);

    int tmp = path[node2];
    path[node2] = path[node1];
    path[node1] = tmp;
}

void SimulatedAnnealing::randomShuffle(Path &path, std::uniform_int_distribution<> &dist, std::mt19937 &gen) {
    int node1, node2;

    bool *node_used = new bool[path.getSize()];
    memset(node_used, false, sizeof(*node_used) * path.getSize());

    int v;
    for(int i = 0; i < path.getSize(); i++)
    {
        do {
            v = dist(gen);
        } while(node_used[v]);

        path[i] = v;
        node_used[v] = true;
    }

    delete[] node_used;
}

Path SimulatedAnnealing::getBestPath() {
    return *bestPath;
}

float SimulatedAnnealing::getTemperature() {
    return temperature;
}

unsigned SimulatedAnnealing::getDurationUntilFound() {
    return durationUntilFound;
}

float SimulatedAnnealing::getOptimalTemperature(Graph *graph, float cooling) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nodes_dist(0, graph->getNodesCount() - 1);
    std::uniform_int_distribution<> probability_dist(0, INT_MAX - 1);

    Path path(graph->getNodesCount());

    int c1, c2;
    unsigned diff = 0;

    int samples = 50000;

    for(int i = 1; i <= samples; i++)
    {
        randomShuffle(path, nodes_dist, gen);
        c1 = path.cost(graph);
        twoOptShuffle(path, nodes_dist, gen);
        c2 = path.cost(graph);

        diff += abs(c2 - c1);
    }

    float avg_diff = (float) diff / samples;

    return avg_diff / (-1 * log(cooling));
}