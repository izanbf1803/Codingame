#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    vector<vector<int> > map(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> map[i][j];
        }   
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
    cin >> EX; cin.ignore();

    // game loop
    while (1) {
        int x;
        int y;
        string pos;
        cin >> x >> y >> pos; cin.ignore();
        
        cerr << x << ' ' << y << ' ' << pos << endl;
        cerr << map[y][x] << endl;
        switch (map[y][x]) {
            case 1:
            case 3:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                y++;
                break;
            case 2:
            case 6:
                x += (pos == "LEFT" ? 1 : -1);
                break;
            case 4:
                if (pos == "TOP") x--;
                else y++;
                break;
            case 5:
                if (pos == "TOP") x++;
                else y++;
                break;
            case 10:
                x--;
                break;
            case 11:
                x++;
                break;
        }
        
        cout << x << ' ' << y << endl;
    }
}
