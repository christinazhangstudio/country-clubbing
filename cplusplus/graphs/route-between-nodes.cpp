#include <vector>
#include <iostream>
#include <queue>

using namespace std;

// directed graph in adacency list

class Graph{
public:
    int V;
    vector<int> *adj;

    Graph(int V);
    void addEdge(int x, int y);
    bool isRoute(int x, int y);
};

Graph::Graph(int V) {
    this->V=V;
    this->adj = new vector<int>[V];   // array of vectors
}

// [5][2, 0]
// [4][0, 1]
// [2][3]
// [3][1] 
void Graph::addEdge(int x, int y) {
    adj[x].push_back(y);
}

// see if there is a route between x and y
bool Graph::isRoute(int x, int y)  {
    vector<bool> visited(V, false);
    queue<int> q; // make a queue that stores the nodes that are not visited but could be en-route

    q.push(x);  // init our queue 

    while(!q.empty()) {
        int curr = q.front(); // if the queue contains y, return true
        if(curr == y) {
            return true;
        }

        q.pop();   // else pop the queue and add the next unvisited nodes in the adjacency list

        visited[curr] = true;   // mark this node as being visited

        int n_size = adj[curr].size();

        for(int i = 0; i < n_size; ++i) {   // traverse the adjacency list for this current node and put all unvisited nodes in queue
            if(!visited[adj[curr][i]]) {    // we will use every unvisited node and traverse their adjacency list etc.
                q.push(adj[curr][i]);
            }
        }
    }

    return false;
}

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    /*
        0 <-- 4 --> 1
        ^           ^
        |           |
        5 --> 2 --> 3
    
    */
    

    cout << boolalpha << g.isRoute(5, 4) <<endl;
    cout << boolalpha << g.isRoute(5, 1) << endl;

    return 0;
}