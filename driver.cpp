// include libraries here
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"

int main() {
    Graph graph;
    std::string line{};
    std::string command{};

    // got most of this from stack overflow and my previous labs
    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> command;

        if (command == "insert") {
            int a{};
            int b{};
            double d{};
            double s{};
            // stores the parameters after the command into corresponding variable
            iss >> a >> b >> d >> s;
            graph.insertEdge(a, b, d, s);
            std::cout << "success" << std::endl;

        } else if (command == "load") {
            std::string filename;
            iss >> filename;
            
            std::ifstream file(filename);
            std::string line;

            while (getline(file, line)) {
                std::istringstream iss(line);
                int a{};
                int b{};
                double d{};
                double s{};

                if (iss >> a >> b >> d >> s) {
                    graph.insertEdge(a, b, d, s);
                }
            }

            file.close();
            std::cout << "success" << std::endl;

        } else if (command == "update") {
            // made a check to see if any values were updated
            bool updated{false};
            std::string filename;
            iss >> filename;
            
            std::ifstream file(filename);
            std::string line;

            if (!file.is_open()) {
                std::cout << "failure" << std::endl;
            }

            while (getline(file, line)) {
                bool check{false};
                std::istringstream iss(line);
                int a{};
                int b{};
                double A{};
                if (iss >> a >> b >> A) {
                    check = graph.updateEdge(a, b, A);
                }
                // if something was updated
                if (check) {
                    updated = true;
                }
            }

            if (updated) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }

            file.close();

        } else if (command == "traffic") {
            int a{};
            int b{};
            double A{};
            iss >> a >> b >> A;
            bool updated = graph.updateEdge(a, b, A);
            if (updated) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        } else if (command == "print") {
            int a{};
            iss >> a;
            graph.printAdjacent(a);
        } else if (command == "delete") {
            int a{};
            iss >> a;
            graph.removeNode(a);
        } else if (command == "path") {
            int a{};
            int b{};
            iss >> a >> b;
            graph.shortestPath(a, b);
        } else if (command == "lowest") {
            int a{};
            int b{};
            iss >> a >> b;
            graph.traverseTime(a, b);
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}