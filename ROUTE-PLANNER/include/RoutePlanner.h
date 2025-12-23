#pragma once
#include "Graph.h"
#include "Sensor.h"
#include <vector>
#include <unordered_map>
#include <climits>
#include <iostream>

class RoutePlanner {
private:
    int bestCost;
    std::vector<int> bestPath;

    void dfs(
        int current,
        int destination,
        Graph& graph,
        std::unordered_map<int, SensorData>& sensors,
        std::vector<bool>& visited,
        std::vector<int>& path,
        int currentCost
    );

public:
    std::vector<int> getBestPath() { return bestPath; }
    int getBestCost() { return bestCost; }

    void findOptimalRoute(
        int currentNode,
        int destination,
        Graph& graph,
        std::unordered_map<int, SensorData>& sensors,
        std::vector<int> &currentPath

    );
};
