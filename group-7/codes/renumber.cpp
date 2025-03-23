#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("Wiki-Vote_31.txt"); 
    ofstream outputFile("Wiki-Vote_32.txt");  
    int x,z=0;
    string line;
    unordered_map<int, int> nodeMap; 
    int newNodeIndex = 0;
    

    vector<pair<int, int>> edges;
    
    
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int nodeA, nodeB;
        ss >> nodeA >> nodeB;
        
      
        if (nodeMap.find(nodeA) == nodeMap.end()) {
            newNodeIndex++;
            nodeMap[nodeA] = newNodeIndex;
        }
        if (nodeMap.find(nodeB) == nodeMap.end()) {
            newNodeIndex++;
            nodeMap[nodeB] = newNodeIndex;
        }
    
        edges.push_back({nodeMap[nodeA], nodeMap[nodeB]});
    }
    for (auto &edge : edges) {
        int y=0;
        outputFile << edge.first << " " << edge.second << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
