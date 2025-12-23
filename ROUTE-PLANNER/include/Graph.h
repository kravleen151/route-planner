#pragma once
#include <vector>

struct Edge {
    int to;
    int distance;
};

struct Graph {
    int N;
    std::vector<std::vector<Edge>> adj;

    Graph(int n) : N(n) { adj.resize(N); }

    void addEdge(int u, int v, int dist) {
        adj[u].push_back({v, dist});
        adj[v].push_back({u, dist}); // undirected graph
    }
};
