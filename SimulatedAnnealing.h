//
// Created by mikolaj on 19.12.2020.
//

#ifndef SIMULATED_ANNEALING_SIMULATEDANNEALING_H
#define SIMULATED_ANNEALING_SIMULATEDANNEALING_H

#include "Graph.h"
#include "Path.h"
#include <random>
#include <chrono>
#include <cmath>
#include <cstring>

class SimulatedAnnealing {
private:
    Graph *graph;
    float cooling;
    float maxTemperature;
    float temperature;
    float stopTemperature;
    unsigned duration;
    unsigned durationUntilFound;
    Path* bestPath;

    void initializeBestPath();
    static void twoOptShuffle(Path &path, std::uniform_int_distribution<> &dist, std::mt19937 &gen);
    static void randomShuffle(Path &path, std::uniform_int_distribution<> &dist, std::mt19937 &gen);
    static float acceptanceProbability(int best_cost, int cost, float temperature);

public:
    SimulatedAnnealing(Graph *graph, float maxTemperature, float stopTemperature, float cooling, unsigned duration);
    ~SimulatedAnnealing();
    void solve();
    Path getBestPath();
    float getTemperature();
    unsigned getDurationUntilFound();
    static float getOptimalTemperature(Graph* graph, float cooling);
};


#endif //SIMULATED_ANNEALING_SIMULATEDANNEALING_H
