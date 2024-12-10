/*  Represent a graph of city using adjacency matrix /adjacency list.Nodes should represent the various landmarks and links should represent the distance between them.
Find the shortest path using Dijkstra's algorithm from single source to all destination.*/


#include <iostream>
#define MAX 20 
#define INF 9999 

using namespace std;

class Graph {
    int g[MAX][MAX], n, c[MAX], ch[MAX];
    int min_dist, client_dist;
    char v[MAX], str[MAX][MAX];
    
public:
    Graph(int m) {
        n = m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
            }
        }
    }

    void acceptLandmarks();
    void acceptEdges();
    void display();
    void initializeDijkstra();
    void dijkstra(char start, char destination);
};

void Graph::acceptLandmarks() {
    cout << "\n\t\t\tNames Of Landmarks";
    for (int i = 0; i < n; i++) {
        cout << "\nEnter Name of Landmark [" << i + 1 << "] : ";
        cin >> v[i];
    }
    cout << "\n";    
}

void Graph::acceptEdges() {
    int cst;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "\n\tDistance Between Landmark [" << v[i] << "] and [" << v[j] << "] :  ";
            cin >> cst;
            g[i][j] = g[j][i] = cst;
        }
    }
    cout << "\n";    
}

void Graph::display() {
    cout << "\nLandmarks: ";
    for (int i = 0; i < n; i++) {
        cout << "\t" << v[i];
    }

    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << v[i];
        for (int j = 0; j < n; j++) {
            cout << "\t" << g[i][j];
        }
        cout << "\n";
    }
    cout << "\n";    
}

void Graph::initializeDijkstra() {
    for (int i = 0; i < n; i++) {
        c[i] = INF; 
        ch[i] = 0;
        for (int j = 0; j < n; j++) {
            str[i][j] = '-';
        }
    }
}

void Graph::dijkstra(char start, char destination) {
    initializeDijkstra();
    
    int sIndex = 0;
    while (v[sIndex] != start) {
        sIndex++;
    }
    
    c[sIndex] = 0;
    str[sIndex][0] = v[sIndex];

    for (int count = 0; count < n - 1; count++) {
        int minIndex = -1, minValue = INF;
        
        // Find the minimum distance vertex
        for (int j = 0; j < n; j++) {
            if (!ch[j] && c[j] < minValue) {
                minValue = c[j];
                minIndex = j;
            }
        }
        
        ch[minIndex] = 1; // Mark as visited

        for (int j = 0; j < n; j++) {
            if (g[minIndex][j] != 0 && !ch[j] && c[minIndex] != INF) {
                if (c[minIndex] + g[minIndex][j] < c[j]) {
                    c[j] = c[minIndex] + g[minIndex][j];
                    str[j][0] = str[minIndex][0];
                    str[j][1] = v[j];
                }
            }
        }
    }

    int dIndex = 0;
    while (v[dIndex] != destination) {
        dIndex++;
    }
    
    cout << "Minimum Distance from " << start << " to " << destination << ": " << c[dIndex] << "\n";
    cout << "Shortest Path: ";
    for (int k = 0; str[dIndex][k] != '-'; k++) {
        cout << str[dIndex][k] << " ";
    }
    cout << "\n";
}
int main() {
    int n, ch;
    cout << "\nEnter Number of Landmarks: ";
    cin >> n;

    Graph g(n);

    do {
        cout << "\n1. Accept Names Of Landmarks.\n2. Accept Distance Between Landmarks.\n3. Display Adjacency Matrix.\n4. Display Shortest Distance.\n5. Exit.";
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                g.acceptLandmarks();
                break;
            case 2:
                g.acceptEdges();
                break;
            case 3:
                g.display();
                break;
            case 4: {
                char v1, v2;
                cout << "\nEnter Source Landmark: ";
                cin >> v1;
                cout << "Enter Destination Landmark: ";
                cin >> v2;
                g.dijkstra(v1, v2);
                break;
            }
            case 5:
                cout << "You Have Successfully Exited.\n";
                break;
            default: 
                cout << "INVALID CHOICE.\n";
        }
    } while (ch != 5);

    return 0;
}
