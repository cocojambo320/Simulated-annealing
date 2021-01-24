#include <fstream>
#include <iostream>
#include "SimulatedAnnealing.h"

#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX 9223372036854775807;
#endif

using namespace std::chrono;

enum Option
{
    quit = 0,
    file = 1,
    display = 2,
    set_temperature = 3,
    set_stop = 4,
    set_cooling= 5,
    suggested_temperature = 6,
    solve = 7,
    test = 8
};

void print_menu()
{
    printf(	"----- Menu -----\n"
               "0. Quit.\n"
               "1. Load data from file.\n"
               "2. Display the recently loaded/generated data.\n"
               "3. Set the start temperature.\n"
               "4. Set the stop conditions.\n"
               "5. Set the cooling parameter.\n"
               "6. Calculate the suggested temperature.\n"
               "7. Solve using simulated annealing.\n"
               "8. Perform the tests.\n");
}

bool file_load(Graph* graph, std::string file_name)
{
    std::fstream file;

    file.open(file_name);

    if (!file.good())
        return false;

    std::string buffer;

    do {
        file >> buffer;
    } while(buffer != "DIMENSION:");

    int nodes_count;
    file >> nodes_count;

    if (nodes_count <= 0)
        return false;

    graph->reset(nodes_count);

    SquareMatrix* matrix = graph->getAdjacencyMatrix();

    do {
        file >> buffer;
    } while(buffer != "EDGE_WEIGHT_SECTION");

    for (int i = 0; i < nodes_count; i++)
        for (int j = 0; j < nodes_count; j++)
            file >> (*matrix)[i][j];

    return true;
}

bool file_load_prompt(Graph* graph)
{
    std::string file_name;

    std::cout << "Enter the file name: ";
    std::cin >> file_name;

    return file_load(graph, file_name);
}

void print_path(Path path)
{
    int n = path.getSize();

    for (int i = 0; i < n - 1; i++)
        printf("%d  ->  ", path[i]);

    printf("%d\n", path[n - 1]);
}

void perform_test(Graph* graph, std::string file_name, float cooling, int duration)
{
    file_load(graph, file_name);

    std::fstream file;
    file.open(file_name + "_" + std::to_string(cooling), std::fstream::out);

    if(!file.good())
        printf("Error while opening the file.\n");

    printf("cooling: %f\n", cooling);
    for(int i = 0; i < 10; i++)
    {
        SimulatedAnnealing sa(graph, SimulatedAnnealing::getOptimalTemperature(graph, cooling), -1, cooling, duration);
        sa.solve();

        printf("%d. Best path cost: %d  Time until found: %u\n", i, sa.getBestPath().cost(graph), sa.getDurationUntilFound());
        file << i << ". Best path cost: " << sa.getBestPath().cost(graph) << " Time until found: " << sa.getDurationUntilFound() << "\n";
    }

    printf("\n");
}

int main()
{
    Graph graph;
    float temperature;
    float stop_temperature;
    float optimal_temperature;
    float cooling;
    int duration;
    int opt;

    do
    {
        print_menu();

        std::cin >> opt;

        switch (opt)
        {
            case file:
                if (file_load_prompt(&graph))
                    printf("The data has been loaded.\n");
                else
                    printf("Error: Could not open the file.\n");

                break;

            case display:
                if (graph.empty()) {
                    printf("Error: There's no graph to display.\n");
                    break;
                }

                std::cout << graph.toString();
                break;

            case set_temperature:
                std::cout << "Enter the temperature: \n";
                std::cin >> temperature;

                break;


            case set_cooling:
                std::cout << "Enter the cooling parameter: \n";
                std::cin >> cooling;

                break;

            case set_stop:
                std::cout << "Enter the max duration time in seconds:\n";
                std::cin >> duration;

                std::cout << "Enter the stop temperature:\n";
                std::cin >> stop_temperature;

                break;

            case suggested_temperature:
            {
                optimal_temperature = SimulatedAnnealing::getOptimalTemperature(&graph, cooling);
                printf("Suggested temperature: %f\n", optimal_temperature);
                break;
            }
            case solve:
            {
                SimulatedAnnealing sa(&graph, temperature, stop_temperature, duration, cooling);

                sa.solve();

                Path best_path = sa.getBestPath();
                printf("Best path cost: %d\n", best_path.cost(&graph));
                print_path(best_path);

                break;
            }
            case test:
            {
                //cooling = 0.9999999;
                //cooling = 0.999; // rbg403
                printf("file: ftv47.atsp\n");
                perform_test(&graph, "ftv47.atsp", 0.99, 120);
                perform_test(&graph, "ftv47.atsp", 0.999, 120);
                perform_test(&graph, "ftv47.atsp", 0.999999, 120);

                printf("file: ftv170.atsp\n");
                perform_test(&graph, "ftv170.atsp", 0.99, 240);
                perform_test(&graph, "ftv170.atsp", 0.999, 240);
                perform_test(&graph, "ftv170.atsp", 0.999999, 240);

                printf("file: rbg403.atsp\n");
                perform_test(&graph, "rbg403.atsp", 0.99, 360);
                perform_test(&graph, "rbg403.atsp", 0.999, 360);
                perform_test(&graph, "rbg403.atsp", 0.999999, 360);

                break;
            }

            default:
                break;
        }
    } while (opt != 0);
}