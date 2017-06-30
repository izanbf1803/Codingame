#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool contains(const string& source, char key)
{
    for (int i = 0; i < source.size(); i++) {
        if (source[i] == key) return true;   
    }
    return false;
}

int main()
{
    int W, H, N; // width of the building.
    cin >> W >> H; cin.ignore();
    cin >> N; cin.ignore();
    int x, y;
    cin >> x >> y; cin.ignore();
    
    vector<vector<bool> > table(W, vector<bool>(H, false));
    int x0 = 0;
    int x1 = W;
    int y0 = 0;
    int y1 = H;
    
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        cerr << x << ' ' << y << endl;
        cerr << x0 << ' ' << x1 << endl;
        cerr << y0 << ' ' << y1 << endl;

        if (contains(bombDir, 'U')) 
            y1 = y;
        else if (contains(bombDir, 'D')) 
            y0 = y;
            
        if (contains(bombDir, 'L')) 
            x1 = x;
        else if (contains(bombDir, 'R')) 
            x0 = x;
            
        x = x0 + (x1 - x0) / 2;
        y = y0 + (y1 - y0) / 2;

        cout << x << ' ' << y << endl;
    }
}
