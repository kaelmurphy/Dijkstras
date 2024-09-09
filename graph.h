#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <functional>

class Edge {
    friend class Graph;

    public:

    Edge();

    void update();

    private:

    double distance;
    double speed;
    double traffic;

    double travelTime;
};

class Graph {
    friend class Edge;
    
    public:
    Graph();

    void insertEdge(int& node1, int& node2, double distance, double speed);

    bool updateEdge(int& node1, int& node2, double traffic);

    void printAdjacent(int& node1);
    
    std::pair<std::vector<int>, double> findLowest(int& node1, int& node2);

    void traverseTime(int& node1, int& node2);

    void shortestPath(int& node1, int& node2);

    void removeNode(int& node1);
    
    private:
    // hashmap of ints that store hashmaps with adjacent ints as keys and edges as values
    std::unordered_map<int, std::unordered_map<int, Edge>> weightedGraph;
};