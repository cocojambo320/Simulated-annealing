//
// Created by mikolaj on 19.12.2020.
//

#ifndef SIMULATED_ANNEALING_PATH_H
#define SIMULATED_ANNEALING_PATH_H

#include "Graph.h"

class Path {
private:
    int *ptr;
    int size;
public:
    Path(int size);
    Path( const Path& );
    ~Path();
    int cost(Graph *graph);
    int getSize();
    int& operator [] (int index);
    Path& operator=(const Path& src);
};


#endif //SIMULATED_ANNEALING_PATH_H
