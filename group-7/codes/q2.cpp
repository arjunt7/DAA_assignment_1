#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <climits>
#include <queue>
#include <sstream>
#include <chrono>  

using namespace std;

unordered_map<int, unordered_set<int>> graph;
vector<int> Q;
long long cnt = 0;
long long len = INT_MIN;
unordered_map<int, int> clique_size_distribution;  


void preprocessGraph(const string& filename, unordered_map<int, unordered_set<int>>& graph) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int u, v;
        ss >> u >> v;

        graph[u].insert(v);
        graph[v].insert(u);
    }

    file.close();
}


vector<int> degeneracy_ordering() {
    unordered_map<int, int> degrees; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;  

    
    for (auto& entry : graph) {
        int vertex = entry.first;
        degrees[vertex] = entry.second.size();
        min_heap.push({degrees[vertex], vertex});
    }

    vector<int> ordering;  
    unordered_set<int> processed;

    while (!min_heap.empty()) {
        int vertex = min_heap.top().second;
        min_heap.pop();

        if (processed.find(vertex) != processed.end()) {
            continue;
        }

        processed.insert(vertex);
        ordering.push_back(vertex);

        
        for (int neighbor : graph[vertex]) {
            if (processed.find(neighbor) == processed.end()) {
                degrees[neighbor]--;
                min_heap.push({degrees[neighbor], neighbor});
            }
        }
    }

    return ordering;
}


void EXPAND(unordered_set<int> SUBG, unordered_set<int> CAND) {
    if (SUBG.empty()) {
        cnt++;
        long long x = Q.size();
        if (x > len)
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
   
    auto start = chrono::high_resolution_clock::now();

    preprocessGraph("Wiki-Vote.txt", graph);

    
    vector<int> order = degeneracy_ordering();

    

    unordered_set<int> V;
    for (const auto& entry : graph) {
        V.insert(entry.first);
    }

  
    unordered_set<int> orderedV;
    for (int v : order) {
        orderedV.insert(v);
    }

   
    EXPAND(orderedV, orderedV);


    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;


    cout << "Number of maximal cliques: " << cnt << endl;
    cout << "Max length of maximal cliques found: " << len << endl;
    cout << "Time taken: " << duration.count() << " seconds." << endl;


    return 0;
}
