#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef struct Node {
    int id;
    map<int, Node*> child;
    map<int, Node*> parents;
} Node;

Node* create_node(int id)
{
    Node* node = new Node;
    node->id = id;
    return node;
}

void next_generation (
    map<int, Node*>& graph,
    int& longest,
    Node* c, // Current node
    int steps)
{
    if (c->child.size() == 0 && steps > longest) {
        longest = steps;
        return;
    }
    
    for (map<int, Node*>::iterator it = c->child.begin(); it != c->child.end(); it++)
        next_generation(graph, longest, it->second, steps + 1);
}

int main()
{
    map<int, Node*> graph;
    int n; // the number of relationships of influence
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        int x; // a relationship of influence between two people (x influences y)
        int y;
        cin >> x >> y; cin.ignore();
        
        if (graph.find(x) == graph.end())
            graph[x] = create_node(x);
            
        if (graph.find(y) == graph.end())
            graph[y] = create_node(y);
            
        graph[x]->child[y] = graph[y];
        graph[y]->parents[x] = graph[x];
    }

    int longest = 0;
    vector<Node*> roots;
    
    for (map<int, Node*>::iterator it = graph.begin(); it != graph.end(); it++) {
        if (it->second->parents.size() == 0)
            roots.push_back(it->second);
    }
    
    for (int i = 0; i < roots.size(); i++)
        next_generation(graph, longest, roots[i], 1);
    
    cout << longest << endl;
}
