#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

typedef struct {
    int x, y;
} Point;

Point operator+(Point a, Point b) { return (Point){a.x + b.x, a.y + b.y}; }

const array<Point, 4> dirs = {{
    {0, -1}, // N
    {0, +1}, // S
    {+1, 0}, // E
    {-1, 0}, // W
}};

inline int id(Point a) { return a.x * 1000000 + a.y; }

int flood_fill(const vector<vector<char>>& grid, Point start, int H, int L)
{
    if (grid[start.y][start.x] == '#') return 0;
    
    int area = 1;
    unordered_set<int> visited;
    queue<Point> q;

    q.push(start);
    visited.insert(id(start));
    
    while (not q.empty()) {
        Point p = q.front(); q.pop();
        
        for (Point dir : dirs) {
            Point np = p + dir;
            
            bool invalid = (np.x < 0 or np.y < 0 or np.x >= L or np.y >= H);
            
            if (invalid) continue;
            
            invalid |= (visited.find(id(np)) != visited.end());
            invalid |= (grid[np.y][np.x] == '#');
            
            if (invalid) continue;
                
            q.push(np);
            visited.insert(id(np));
            area++;
        }
    }
    
    return area;
}

int main()
{
    int L, H, N;
    cin >> L >> H;
    
    vector<vector<char>> grid(H, vector<char>(L));
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            cin >> grid[i][j];   
        }
    }
    
    cin >> N;
    for (int i = 0; i < N; i++) {
        Point point;
        cin >> point.x >> point.y;
        cout << flood_fill(grid, point, H, L) << endl;
    }
}
