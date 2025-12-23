Emergency Vehicle Route Planner

Project Overview
This project simulates an emergency vehicle navigation system in a city. It dynamically calculates optimal routes for multiple vehicles considering:
City road network as a graph (adjacency list)
Blocked roads/nodes representing accidents or construction
Traffic congestion at each node (affecting travel cost)
Dynamic rerouting from current vehicle positions when block/unblock events occur

Features
Multi-vehicle path planning: Handles multiple vehicles simultaneously.
Dynamic rerouting: Vehicles recalculate the shortest feasible path from their current node whenever a node is blocked/unblocked.
Distance + congestion cost: Calculates travel cost using distance plus congestion at the next node.

Edge cases handled:
Vehicle starting on a blocked node → reports “No feasible path”
Destination blocked → reports “No feasible path”
Alternate paths calculated if primary route is blocked

File Structure
ROUTE_PLANNER/
│
├─ include/
│   ├─ Graph.h
│   ├─ RoutePlanner.h
│   ├─ Sensor.h
│
├─ src/
│   ├─ main.cpp
│   ├─ Graph.cpp
│   ├─ RoutePlanner.cpp
│   └─ Sensor.cpp
│
├─ data/
│   ├─ city_map.txt         # Nodes and edges of city graph
│   └─ sensor_data.txt      # Congestion and initial blocked nodes
│
└─ README.md

Compilation & Running
Open terminal in ROUTE_PLANNER directory
Compile:
g++ -std=c++11 src/*.cpp -Iinclude -o emergency.exe
Run:
./emergency.exe

How to Customize
City Graph: Edit data/city_map.txt
Format: u v distance
Sensor/Congestion Data: Edit data/sensor_data.txt
Format: node congestion blocked
blocked = 0 → unblocked, 1 → blocked
Add more vehicles: Enter at program prompt

Technologies: C++ (STL), DFS/Backtracking, Graphs, Hashing

