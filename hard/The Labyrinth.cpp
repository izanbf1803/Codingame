#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define N 0
#define S 1
#define E 2
#define W 3

static int R; // number of rows.
static int C; // number of columns.
static int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.

typedef struct point_t {
    int x, y;
    point_t() : x(-1), y(-1) {}
    point_t(int _x, int _y) : x(_x), y(_y) {}
} Point;

int ptoi(Point p) { return C * p.y + p.x; }
Point itop(int n) { return Point(n % C, n / C); }

bool operator==(const Point& a, const Point& b) { return a.x == b.x and a.y == b.y; }
bool operator!=(const Point& a, const Point& b) { return a.x != b.x or a.y != b.y; }
Point operator+(const Point& a, const Point& b) { return Point(a.x + b.x, a.y + b.y); }
Point operator-(const Point& a, const Point& b) { return Point(a.x - b.x, a.y - b.y); }

const Point null_point = Point(-1, -1);
const array<Point, 4> dirs = {{
    Point(0, -1), // N
    Point(0, 1),  // S
    Point(1, 0),  // E
    Point(-1, 0), // W
}};

char point_diff_to_dir(Point diff) 
{
    for (char i = 0; i < 4; i++)
        if (dirs[i] == diff) return i;
    return -1; // This shouldn't happen
}

void reconstruct_path(
    stack<char>& path,
    unordered_map<int, int>& from,
    Point cp
) {
    int last = ptoi(cp);
    int p = last;
    while (from.find(p) != from.end()) {
        p = from[p];
        Point diff = itop(p) - itop(last);
        path.push(point_diff_to_dir(diff));
        last = p;
    }
}

bool BFS_find(
    stack<char>& path,
    vector<vector<char>>& map,
    Point k,
    char target
) {
    unordered_set<int> visited;
    unordered_map<int, int> from;
    queue<Point> q;
    
    visited.insert(ptoi(k));
    q.push(k);
    
    while (not q.empty()) {
        Point cp = q.front(); // current point
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            Point np = cp + dirs[i];
            
            if (visited.find(ptoi(np)) != visited.end())
                continue;
                
            if (map[np.y][np.x] == '#' or (target != '?' and map[np.y][np.x] == '?'))
                continue;
            
            visited.insert(ptoi(np));
            from[ptoi(np)] = ptoi(cp);
            q.push(np);
            
            if (map[np.y][np.x] == target) {
                reconstruct_path(path, from, np);
                return true; // Path was succesfully found
            }
        }
    }
    return false; // Any path found
}
    

int main()
{
    cin >> R >> C >> A; cin.ignore();
    
    vector<vector<char>> map(R, vector<char>(C, '?'));
    Point _T = null_point, _C = null_point;
    bool C_reached = false;
    
    while (1) {
        Point k; // kirk pos
        cin >> k.y >> k.x; cin.ignore();
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                char c;
                cin >> c;
                if (map[i][j] == '?')
                    map[i][j] = c;

                if (map[i][j] == 'T') _T = Point(j, i);
                if (map[i][j] == 'C') _C = Point(j, i);
            }
        }
        
        stack<char> path;
        
        if (k == _C)
            C_reached = true;
        
        if (path.empty()) {
            if (C_reached) {
                BFS_find(path, map, k, 'T');
            }
            else {
                if (_C == null_point)
                    BFS_find(path, map, k, '?');
                else {
                    bool found = BFS_find(path, map, k, 'C');
                    if (not found)
                        BFS_find(path, map, k, '?');
                }
            }
        }
        
        char dir = path.top();
        path.pop();
        
        switch (dir) {
            case S:
                cout << "UP" << endl;
                break;
            case N:
                cout << "DOWN" << endl;
                break;
            case E:
                cout << "LEFT" << endl;
                break;
            case W:
                cout << "RIGHT" << endl;
                break;
            default:
                return 1;
        }
    }
}
