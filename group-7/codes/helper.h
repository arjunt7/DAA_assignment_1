#ifndef GRAPH_PREPROCESSING_H
#define GRAPH_PREPROCESSING_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

void preprocessGraph(const string& filename, unordered_map<int, unordered_set<int>>& graph) {
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        if (line.find("# FromNodeId") != string::npos) {
            break; // Skip metadata lines
        }
    }

    int from, to;
    while (file >> from >> to) {
        graph[from].insert(to);
        graph[to].insert(from);
    }
    file.close();
}

#endif // GRAPH_PREPROCESSING_H
