#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define EXIT -1

struct Room {
    int id;
    int money;
    int top;
    int right;
};

static vector<Room> rooms;
static vector<int> results_memoized;

int DFS(int index)
{
    if (results_memoized[index] != -1) {
        return results_memoized[index];
    }
    
    Room& c = rooms[index];
    int result;
    
    if (c.top != EXIT and c.right != EXIT) {
        result = c.money + max(DFS(c.top), DFS(c.right));
    }
    else {
        if (c.top != EXIT) {
            result = c.money + DFS(c.top);   
        }
        else if (c.right != EXIT) {
            result = c.money + DFS(c.right);
        }
        else {
            result = c.money;
        }
    }

    results_memoized[index] = result;
    return result;
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    
    rooms = vector<Room>(N, {-1, 0, EXIT, EXIT });
    
    for (int i = 0; i < N; ++i) {
        string edgeT, edgeR;
        Room& r = rooms[i];
        cin >> r.id >> r.money >> edgeT >> edgeR;
        
        if (edgeT != "E") r.top = stoi(edgeT);
        if (edgeR != "E") r.right = stoi(edgeR);
    }
    
    results_memoized = vector<int>(N, -1);
    int max_money = DFS(0);
    
    cout << max_money << endl;
}
