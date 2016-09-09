#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void insert(string tel);

typedef struct Node{
    map<char, Node*> child;
} Node;

Node* head;
int node_count;

int main()
{
    int N;
    head = new Node{};
    node_count = 0;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        cerr << telephone << endl;
        insert(telephone);
    }
    cout << node_count << endl;
}

void insert(string tel) {
    Node* node = head;
    for (int i = 0; i < tel.length(); i++) {
        if (node->child.find(tel[i]) == node->child.end()) {
            node->child[tel[i]] = new Node{};
            node_count++;
        }
        node = node->child[tel[i]];
    }
}