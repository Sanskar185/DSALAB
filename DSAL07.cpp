#include <iostream>
#include <vector>
using namespace std;

class Graph {
    vector<vector<int> > adj_matrix;

public:
    Graph(int n) {
        adj_matrix = vector<vector<int> >(n, vector<int>(n, 0));
    }

    void add_edge(int u, int v, int w) {
        adj_matrix[u][v] = w;
        adj_matrix[v][u] = w;
    }

    void prim() {
        int n = adj_matrix.size();
        vector<int> key(n, 1e9), parent(n, -1);
        vector<bool> inMST(n, false);
        key[0] = 0;
        int total_weight = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            for (int v = 0; v < n; v++)
                if (!inMST[v] && (u == -1 || key[v] < key[u]))
                    u = v;

            inMST[u] = true;
            total_weight += key[u];

            for (int v = 0; v < n; v++) {
                if (adj_matrix[u][v] && !inMST[v] && adj_matrix[u][v] < key[v]) {
                    key[v] = adj_matrix[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "Total weight of the MST Prim's: " << total_weight << endl;
        cout << "Prim MST Edges:\n";
        for (int i = 1; i < n; i++) {
            cout << parent[i] << " -- " << i << " : " << adj_matrix[parent[i]][i] << endl;
        }
    }

    void kruskal() {
        vector<pair<int, pair<int, int> > > edges;

        for (int i = 0; i < adj_matrix.size(); i++) {
            for (int j = i + 1; j < adj_matrix.size(); j++) {
                if (adj_matrix[i][j] > 0) {
                    edges.push_back({adj_matrix[i][j], {i, j}});
                }
            }
        }

        for (int i = 0; i < edges.size() - 1; i++) {
            for (int j = i + 1; j < edges.size(); j++) {
                if (edges[i].first > edges[j].first) {
                    swap(edges[i], edges[j]);
                }
            }
        }

        vector<int> parent(adj_matrix.size());
        for (int i = 0; i < parent.size(); i++) parent[i] = i;

        int total_weight = 0;
        cout << "Kruskal MST Edges:\n";
        for (int i = 0; i < edges.size(); i++) {
		    int u = edges[i].second.first;
		    int v = edges[i].second.second;
		    while (u != parent[u])
		        u = parent[u];
		    while (v != parent[v])
		        v = parent[v];
		    if (u != v) {
		        total_weight += edges[i].first;
		        parent[v] = u;
		        cout << u << " -- " << v << " : " << edges[i].first << endl;
		    }
		}



        cout << "Total weight of the MST Kruskal's: " << total_weight << endl;
    }
};

int main() {
    int n = 5;
    Graph g(n);
    g.add_edge(0, 1, 10);
    g.add_edge(0, 2, 6);
    g.add_edge(0, 3, 5);
    g.add_edge(1, 3, 15);
    g.add_edge(3, 2, 4);
    g.kruskal();
    
    g.prim();


    return 0;
}
