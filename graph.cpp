#include "graph.h"

Edge::Edge():
distance(1),
speed(1),
traffic(1) {
    travelTime = distance/(speed*traffic);
}
// helper function to update my travelTime only when i call it
void Edge::update() {
    travelTime = distance/(speed*traffic);
}

Graph::Graph() {
}

void Graph::insertEdge(int& node1, int& node2, double distance, double speed) {
    // update or create new edge
    weightedGraph[node1][node2].distance = distance;
    weightedGraph[node1][node2].speed = speed;
    weightedGraph[node1][node2].update();
    // update or create new edge
    weightedGraph[node2][node1].distance = distance;
    weightedGraph[node2][node1].speed = speed;
    weightedGraph[node2][node1].update();

    return;
}

// update the edge between nodes if edge exists
bool Graph::updateEdge(int& node1, int& node2, double traffic) {
    // made a way to check if any nodes had been updated
    bool updated{false};
    // got this from cpp documentation
    auto iterator  = weightedGraph.find(node1);
    // if the node is in the graph
    if (iterator != weightedGraph.end()) {
        auto iterator2  = weightedGraph[node1].find(node2);
        // edge exists between node1 and node2
        if (iterator2 != weightedGraph[node1].end()) {
            // set new traffic value and update time
            weightedGraph[node1][node2].traffic = traffic;
            weightedGraph[node1][node2].update();
            // set new traffic value and update time           
            weightedGraph[node2][node1].traffic = traffic;
            weightedGraph[node2][node1].update();
            // set to true if the edge exists and is updated
            updated = true;
        }
    }
    // returns the check
    return updated;
}

void Graph::printAdjacent(int& node1) {
    // got this from cplusplus documentation
    auto iterator = weightedGraph.find(node1);
    // if the node is in the graph
    if (iterator != weightedGraph.end()) {
        int count{0};
        for (auto it = weightedGraph[node1].begin(); it != weightedGraph[node1].end(); it++){
            std::cout << it->first << " ";
            count++;
        }
        // if there isn't at least 1 adjacent node
        if (count == 0) {
            std::cout << "failure";
        }
    } else {
        std::cout << "failure";
    }

    std::cout << std::endl;

    return;
}

// found this on stackoverflow in order to sort my priority queue to be a min heap
struct compareSecondValue {
    bool operator()(const std::pair<int, double>& a, const std::pair<int, double>& b) const {
        return a.second > b.second;
    }
};

std::pair<std::vector<int>, double> Graph::findLowest(int& node1, int& node2) {
    // priority queue to store nodes with their respective times
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compareSecondValue> queue;
    // set to keep track of visited nodes
    std::set<int> visited;
    // table to store node information {parent node, time}
    std::unordered_map<int, std::pair<int, double>> table;

    if ((weightedGraph.find(node1) == weightedGraph.end()) || (weightedGraph.find(node1) == weightedGraph.end())) {
        return {std::vector<int> {-1}, -1};
    }

    // initialize the distance table
    for (auto it = weightedGraph.begin(); it != weightedGraph.end(); ++it) { 
        table[it->first] = {0, std::numeric_limits<double>::infinity()};
    }
    // set the distance of the starting node to 0
    table[node1] = {-1, 0};
    // push the starting node onto the priority queue
    queue.push({node1, 0});

    // run Dijkstra's algorithm
    while (!queue.empty()) {
        // get node with the shortest distance from the priority queue
        int currNode = queue.top().first;
        double currTime = queue.top().second;
        queue.pop();
        // if currNode is our destination we found shortest path
        if (currNode == node2) {
            break;
        }
        // check if the node has already been visited
        if (visited.count(currNode)) {
            continue;
        }
        // mark the current node as visited
        visited.insert(currNode);
        // iterate over the neighbors of the current node
        for (auto it = weightedGraph[currNode].begin(); it != weightedGraph[currNode].end(); ++it) {
            // get neighbor node and its edge
            int neighbor = it->first;
            Edge& edge = it->second;
            // calculate time to reach neighbor through current node
            double newTime = currTime + edge.travelTime;

            // if new time is shorter than neighbor's current time, update it
            if (newTime < table[neighbor].second) {
                // update neighbor's parent node and time
                table[neighbor] = {currNode, newTime};
                // push neighbor and its new time into priority queue
                queue.push({neighbor, newTime});
            }
        }
    }
    // if the time to the destination node after the while loop is inf then flag it with -1 time
    if (table[node2].second == std::numeric_limits<double>::infinity()) {
        return {std::vector<int> {-1}, -1};
    }
    
    // reconstruct the shortest path
    std::vector<int> path;
    // access second data in tuple
    double time = table[node2].second;
    int nodeTraverse = node2;
    // while currNode during traversal isn't -1 keep going
    while (nodeTraverse != -1) {
        // add currNode to the vector
        path.push_back(nodeTraverse);
        // set currNode to be prev Nodes parent
        nodeTraverse = table[nodeTraverse].first;
    }
    // return the shortest path and its length
    return {path, time};
}

void Graph::traverseTime(int& node1, int& node2) {
    // set time to be second data in returned tuple
    double time = findLowest(node1, node2).second;
    // if time was marked with -1 then no path exists
    if (time == -1) {
        std::cout << "failure" << std::endl;
    // otherwise print time
    } else {
        std::cout << time << std::endl;
    }
}

void Graph::shortestPath(int& node1, int& node2) {
    // set path to be first data in returned tuple
    std::vector<int> path = findLowest(node1, node2).first;
    // if path returned is -1, no path exists
    if (path == std::vector<int> {-1}) {
        std::cout << "failure";
    // otherwise print out the path in reverse order to get path taken
    } else {
        for (long unsigned k{path.size()}; k > 0; k--) {
            std::cout << path[k - 1] << " ";
        }
    }
    std::cout << std::endl;
}

void Graph::removeNode(int& node1) {
    // check if node exists in the graph
    if (weightedGraph.find(node1) == weightedGraph.end()) {
        std::cout << "failure" << std::endl;
        return;
    }
    // erase the node and its edges from the graph
    weightedGraph.erase(node1);

    // iterate over the remaining nodes in the graph
    for (auto it = weightedGraph.begin(); it != weightedGraph.end(); ++it) {
        // Erase any edges pointing to the removed node
        it->second.erase(node1);
    }

    std::cout << "success" << std::endl;
}
