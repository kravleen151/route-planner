#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "Graph.h"
#include "Sensor.h"
#include "RoutePlanner.h"

int main() {
    // Load city map
    std::ifstream mapFile("data/city_map.txt");
    int N, E;
    mapFile >> N >> E;
    Graph graph(N);
    for (int i = 0; i < E; i++) {
        int u, v, d;
        mapFile >> u >> v >> d;
        graph.addEdge(u, v, d);
    }
    mapFile.close();

    // Load sensor/congestion data
    std::ifstream sensorFile("data/sensor_data.txt");
    std::unordered_map<int, SensorData> sensors;
    for (int i = 0; i < N; i++) {
        int node, congestion, blocked;
        sensorFile >> node >> congestion >> blocked;
        SensorData sd;
        sd.congestion = congestion;
        sd.isBlocked = blocked;
        sensors[node] = sd;
    }
    sensorFile.close();

    // Vehicle setup
    int vehicleCount;
    std::cout << "Enter number of vehicles: ";
    std::cin >> vehicleCount;

    std::unordered_map<int,int> vehicleCurrentNode;
    std::unordered_map<int,int> vehicleDestination;
    std::unordered_map<int,std::vector<int>> vehiclePath;

    RoutePlanner planner;

    // Input source/destination for each vehicle
    for (int v = 1; v <= vehicleCount; v++) {
        int src, dest;
        std::cout << "Vehicle " << v << " source: ";
        std::cin >> src;
        std::cout << "Vehicle " << v << " destination: ";
        std::cin >> dest;
        vehicleCurrentNode[v] = src;
        vehicleDestination[v] = dest;
        vehiclePath[v] = {};
    }

    // Initial routing
    for (int v = 1; v <= vehicleCount; v++) {
        std::vector<int> tmpPath;
        planner.findOptimalRoute(vehicleCurrentNode[v], vehicleDestination[v], graph, sensors, tmpPath);
        vehiclePath[v] = planner.getBestPath();
    }

    // Dynamic updates loop
    while (true) {
        std::string cmd;
        std::cout << "\nEnter command (block/unblock/exit): ";
        std::cin >> cmd;
        if (cmd == "exit") break;

        int node;
        std::cout << "Node number to " << cmd << ": ";
        std::cin >> node;

        if (cmd == "block") sensors[node].isBlocked = true;
        else if (cmd == "unblock") sensors[node].isBlocked = false;

        // Prompt user for current node of each vehicle
        for (int v = 1; v <= vehicleCount; v++) {
            int curr;
            std::cout << "Enter current node of Vehicle " << v << ": ";
            std::cin >> curr;
            vehicleCurrentNode[v] = curr;
        }

        std::cout << "\n--- Recalculating routes ---\n";
        for (int v = 1; v <= vehicleCount; v++) {
            std::vector<int> tmpPath;
            planner.findOptimalRoute(vehicleCurrentNode[v], vehicleDestination[v], graph, sensors, tmpPath);
            vehiclePath[v] = planner.getBestPath();
        }
    }

    return 0;
}
