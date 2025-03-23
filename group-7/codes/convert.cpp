#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <map>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("Wiki-Vote.txt");
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return -1;
    }

    string line;
    int x;
    while (getline(inputFile, line)) {
        if (line[0] != '#' || line.empty()) {
            break;
        }
    }

    set<pair<int, int>> undirectedEdges;
    int tem=0;
    int fromNode, toNode;

    while (inputFile >> fromNode >> toNode) {
        toNode--; 
        fromNode--;         
                
        if (fromNode != toNode) {
            undirectedEdges.insert({min(fromNode, toNode), max(fromNode, toNode)});
        }
    }

    inputFile.close();

    ofstream outputFile("Wiki-Vote_31.txt");

    for (const auto& edge : undirectedEdges) {
        outputFile << edge.first << " " << edge.second << endl;
    }

    outputFile.close();

    cout << "Conversion to undirected graph complete!" << endl;

    return 0;
}
