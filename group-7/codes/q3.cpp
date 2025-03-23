#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include<limits.h>

using namespace std;

vector<vector<int>> adj;
int n; 
long long x=0,len =INT_MIN;

set<vector<int>> foundCliques;

void printClique(const vector<int>& clique, const vector<int>& new_to_original) {
    vector<int> originalLabels;
    for (int v : clique) {
        originalLabels.push_back(new_to_original[v]);
    }
    sort(originalLabels.begin(), originalLabels.end()); 
    
    
    if (foundCliques.find(originalLabels) == foundCliques.end()) {
        foundCliques.insert(originalLabels);
        x++;
        int w = originalLabels.size();
       // cout<<w<<endl;
        if(w > len) len = w;
       /* cout << "Maximal Clique (original labels): ";
        for (int v : originalLabels) {
            cout << v << " ";
        }
        cout << endl;*/
    }
}

void UPDATE(int i, vector<int> C, vector<int> S, vector<int> T, const vector<int>& new_to_original) {
    sort(C.begin(), C.end()); 

    if (i >= n) {
        printClique(C, new_to_original);
        return;
    }

    
    vector<int> C_intersect_Ni, C_minus_Ni;
    for (int x : C) {
        if (binary_search(adj[i].begin(), adj[i].end(), x)) {
            C_intersect_Ni.push_back(x);
        } else {
            C_minus_Ni.push_back(x);
        }
    }

    
    if (!C_minus_Ni.empty()) {
        UPDATE(i + 1, C, S, T, new_to_original);
    }

    
    vector<int> modified_T, modified_S;

    
    for (int x : C_intersect_Ni) {
        for (int y : adj[x]) {
            if (y != i && !binary_search(C.begin(), C.end(), y)) {
                T[y]++;
                modified_T.push_back(y);
            }
        }
    }

  
    for (int x : C_minus_Ni) {
        for (int y : adj[x]) {
            if (!binary_search(C.begin(), C.end(), y)) {
                S[y]++;
                modified_S.push_back(y);
            }
        }
    }

    
    bool FLAG = true;
    for (int y : adj[i]) {
        if (!binary_search(C.begin(), C.end(), y) && y < i) {
            if (T[y] == (int)C_intersect_Ni.size()) {
                FLAG = false;
                break;
            }
        }
    }

   
    sort(C_minus_Ni.begin(), C_minus_Ni.end());
    int p = C_minus_Ni.size();

    
    for (int k = 0; k < p; ++k) {
        int jk = C_minus_Ni[k];
        for (int y : adj[jk]) {
            if (binary_search(C.begin(), C.end(), y) || y >= i) continue;
            if (T[y] != (int)C_intersect_Ni.size()) continue;

            if (y >= jk) {
                S[y]--;
            } else {
                bool is_first = true;
                for (int m = 0; m < k; ++m) {
                    if (y < C_minus_Ni[m]) {
                        is_first = false;
                        break;
                    }
                }
                if (is_first) {
                    int prev_j = (k == 0) ? -1 : C_minus_Ni[k - 1];
                    if (S[y] + k == p && y >= prev_j) {
                        FLAG = false;
                    }
                }
            }
        }
    }

    
    if (!C_intersect_Ni.empty()) {
       
        for (int x : C_intersect_Ni) {
            for (int y : adj[x]) {
                if (y == i || binary_search(C.begin(), C.end(), y)) continue;
                if (y >= i) continue;
                if (T[y] == (int)C_intersect_Ni.size() && S[y] == 0) {
                  
                    int j_y = -1;
                    for (int m = 0; m < (int)C_minus_Ni.size(); ++m) {
                        if (C_minus_Ni[m] > y) {
                            j_y = C_minus_Ni[m];
                            break;
                        }
                    }
                    if (j_y != -1) {
                        if (j_y < y || j_y < (i - 1)) {
                            FLAG = false;
                        }
                    }
                }
            }
        }

       
        for (int x : C_intersect_Ni) {
            for (int y : adj[x]) {
                if (binary_search(C.begin(), C.end(), y) || y == i) continue;
                T[y] = 0;
            }
        }
        for (int x : C_minus_Ni) {
            for (int y : adj[x]) {
                if (binary_search(C.begin(), C.end(), y)) continue;
                S[y] = 0;
            }
        }
    }

    
    for (int y : modified_T) T[y] = 0;
    for (int y : modified_S) S[y] = 0;

  
    if (FLAG) {
        vector<int> new_C = C_intersect_Ni;
        new_C.push_back(i);
        sort(new_C.begin(), new_C.end());
        UPDATE(i + 1, new_C, S, T, new_to_original);
    }
}

void CLIQUE(const vector<int>& new_to_original) {
    vector<int> S(n, 0);  
    vector<int> T(n, 0); 
    vector<int> C = {0};  
    UPDATE(1, C, S, T, new_to_original);  
}

int main() {
    ifstream infile("input2.txt");
    if (!infile) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }

   
    map<int, vector<int>> original_adj_map;
    int max_vertex = -1;
    int u, v;
    
    
    while (infile >> u >> v) {
        original_adj_map[u].push_back(v);
        original_adj_map[v].push_back(u); 
        max_vertex = max(max_vertex, max(u, v));
    }
    
  
    n = max_vertex + 1;
    
   
    vector<vector<int>> original_adj(n);
    for (const auto& entry : original_adj_map) {
        int vertex = entry.first;
        original_adj[vertex] = entry.second;
    }

 
    vector<int> original_vertices(n);
    for (int i = 0; i < n; ++i) original_vertices[i] = i;
    sort(original_vertices.begin(), original_vertices.end(), [&original_adj](int a, int b) {
        return original_adj[a].size() < original_adj[b].size();
    });

   
    vector<int> original_to_new(n);
    vector<int> new_to_original(n);
    for (int new_label = 0; new_label < n; ++new_label) {
        int orig = original_vertices[new_label];
        original_to_new[orig] = new_label;
        new_to_original[new_label] = orig;
    }

   
    adj.resize(n);
    for (int orig_u = 0; orig_u < n; ++orig_u) {
        int new_u = original_to_new[orig_u];
        for (int orig_v : original_adj[orig_u]) {
            int new_v = original_to_new[orig_v];
            adj[new_u].push_back(new_v);
        }
        sort(adj[new_u].begin(), adj[new_u].end());
    }

    
    foundCliques.clear();
    
    CLIQUE(new_to_original);

    cout << "Total number of distinct maximal cliques: " << x << endl;
    cout << "max lenght: " << len;

    return 0;
}