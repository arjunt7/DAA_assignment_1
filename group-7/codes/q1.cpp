#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include "helper.h"
#include <climits>

using namespace std;

unordered_map<int, unordered_set<int>> graph;
vector<int> Q;
long long cnt=0;
long long len = INT_MIN;
int n=0,m=0;

void EXPAND(unordered_set<int> SUBG, unordered_set<int> CAND) {
    
    if (SUBG.empty()) {
    	  cnt++;
       // cout << "clique, {";  // Represents a maximal clique
      //  for (int v : Q) cout << v << " ";
       // cout << "}," << endl;
       long long x= Q.size();
       if(x>len)
       	len = x; 
        return;
    }
    unordered_set<int> FINI;
    int u = -1;
    size_t max_neighbors = 0;
    for (int v : SUBG) {  
        size_t count = 0;
        for (int neighbor : graph[v]) {
            if (CAND.count(neighbor)) count++;
        }
        if (count > max_neighbors) {
            max_neighbors = count;
            u = v;
        }
    }
    
    unordered_set<int> extu;
    for (int v : CAND) {
        if (!graph[u].count(v)) extu.insert(v);
    }
    
    while (!extu.empty()) {
        int q = *extu.begin();
        extu.erase(q);
    
        Q.push_back(q);
        unordered_set<int> SUBGq, CANDq;
        for (int v : SUBG) {
            if (graph[q].count(v)) SUBGq.insert(v);
        }
        for (int v : CAND) {
            if (graph[q].count(v)) CANDq.insert(v);
        }
        
        EXPAND(SUBGq, CANDq);
        
        CAND.erase(q);
        FINI.insert(q);
      
        Q.pop_back();
    }
}


int main() {
    preprocessGraph("Wiki-Vote.txt", graph);
    Q.clear();
    unordered_set<int> V;
    for (const auto& entry : graph) V.insert(entry.first);
    EXPAND(V, V);
    cout<<"no. of maximal cliques: "<<cnt<<endl;
    cout<<"max length of maximal cliques found: "<<len<<endl;
    return 0;
}


//as-skitter.txt
//Email-Enron.txt
//Wiki-Vote.txt
