#include "RoutePlanner.h"

void RoutePlanner::dfs(
    int current,
    int destination,
    Graph& graph,
    std::unordered_map<int, SensorData>& sensors,
    std::vector<bool>& visited,
    std::vector<int>& path,
    int currentCost
) {
    if (sensors[current].isBlocked) return;

    if (current == destination) {
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = path;
        }
        return;
    }

    for (auto &edge : graph.adj[current]) {
        int next = edge.to;
        if (!visited[next] && !sensors[next].isBlocked) {
            visited[next] = true;
            path.push_back(next);
            int cost = edge.distance + sensors[next].congestion;
            dfs(next, destination, graph, sensors, visited, path, currentCost + cost);
            path.pop_back();
            visited[next] = false;
        }
    }
}

void RoutePlanner::findOptimalRoute(
    int currentNode,
    int destination,
    Graph& graph,
    std::unordered_map<int, SensorData>& sensors,
    std::vector<int> &currentPath
) {
    bestCost = INT_MAX;
    bestPath.clear();

    std::vector<bool> visited(graph.N, false);
    std::vector<int> path = currentPath;

    visited[currentNode] = true;
    path.push_back(currentNode);

    dfs(currentNode, destination, graph, sensors, visited, path, 0);

    if (bestCost == INT_MAX) {
        std::cout << "No feasible path found from node " << currentNode << " to " << destination << "\n";
        return;
    }

    std::cout << "Optimal Emergency Route from " << currentNode << " to " << destination << ":\n";
    for (int i = 0; i < bestPath.size(); i++) {
        std::cout << bestPath[i];
        if (i != bestPath.size() - 1) std::cout << " -> ";
    }
    std::cout << "\nTotal Cost: " << bestCost << "\n";
}
