#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

typedef struct {
    vector<int> edges;
    bool explored;
    int depth;
    int id;
} Node;

float max_depth = 0;
int starter_id;

Node* create_node(int id)
{
    Node* node = new Node;
    node->edges = vector<int>();
    node->depth = 0;
    node->explored = false;
    node->id = id;
    
    return node;
}

void prepare_graph(map<int, Node*>& graph)
{
    Node* current;
    
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
        current = graph[it->first];
        
        current->explored = false;
        current->depth = 2147483647;
    } 
}

void BFS(
    map<int, Node*>& graph,
    int s_id)
{
    prepare_graph(graph);
    
    Node* s = graph[s_id];
    s->explored = true;
    s->depth = 0;
    
    queue<int> next;
    next.push(s->id);
    
    Node *current, *x;
    
    while (not next.empty()) {
        
        x = graph[next.front()];
        next.pop();
        
        for (int i = 0; i < x->edges.size(); i++) { // iterate x node edges
            //cerr << i << " i" << endl;
            //cerr << "edge: " << x->edges[i] << endl;
            current = graph[x->edges[i]];
            
            if (not current->explored) {
                current->explored = true;   
                current->depth = x->depth + 1;
                next.push(current->id); // Push current node to queue(next)
            }
        }
    }
    
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
        current = graph[it->first];
        
        //cerr << current->id << " depth = " << current->depth << endl;
        
        if (current->depth > max_depth) {
            max_depth = current->depth;
            starter_id = current->id;
        }
        
        //if (current->depth == max_depth) starter_id = current->id;
    }
}
 
int main()
{
    int n, xi, yi; // the number of adjacency relations
    cin >> n; cin.ignore();
    
    map<int, Node*> graph;
    
    for (int i = 0; i < n; i++) {
        // int xi; // the ID of a person which is adjacent to yi
        // int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        
        if (graph.find(xi) == graph.end())
            graph[xi] = create_node(xi);
            
        if (graph.find(yi) == graph.end())
            graph[yi] = create_node(yi);
        
        graph[xi]->edges.push_back(yi);
        graph[yi]->edges.push_back(xi);
    }
    
    starter_id = xi;

    BFS(graph, starter_id);
    BFS(graph, starter_id);
    
    //cerr << "max_depth = " << max_depth << endl;
    cout << ceil(max_depth / 2) << endl;
    
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++)
        delete graph[it->first];
}
