#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define radians (M_PI/180.0)
#define degrees (180.0/M_PI)
#define magic_number_1 1.0
#define magic_number_2 2.0
#define max_h_speed (20.0 - magic_number_1)
#define max_v_speed (40.0 - magic_number_2)
#define gravity (3.711)
#define stop_fall_angle ((int)(acos(gravity / 4.0) * degrees))
#define security_distance (max_v_speed / (gravity-3.0))

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point a, b, c;
} LZ; // Landing zone

LZ lz;

inline bool overLZ(Point a) { return a.x >= lz.a.x and a.x <= lz.b.x; }
inline int dirToLZ(Point a) { return a.x < lz.c.x ? 1 : -1; }
inline int direction(int hSpeed) { return hSpeed > 0 ? 1 : -1; }
inline int r2decelerate(int hSpeed, int vSpeed) 
{   
    return asin((double) hSpeed / sqrt(hSpeed*hSpeed + vSpeed*vSpeed)) * degrees;
}

int main()
{
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    vector<Point> points;
    Point last = {0, 0};
    
    
    for (int i = 0; i < surfaceN; i++) {
        Point p;
        cin >> p.x >> p.y; cin.ignore();
        
        if (p.y == last.y and p.x - last.x >= 1000)
            lz = {last, p, {p.x/2 + last.x/2, p.y}};
        
        last = p;
        points.push_back(p);
    }

    while (1) {
        Point a;
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int r = 0, rotate; // the rotation angle in degrees (-90 to 90).
        int p = 0, power; // the thrust power (0 to 4).
        cin >> a.x >> a.y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();
        
        if (overLZ(a)) {
            if (a.y < lz.c.y + security_distance) {
                // cerr << "a" << endl;
                r = 0;
                p = 3;
            }
            else if (abs(hSpeed) < max_h_speed and abs(vSpeed) < max_v_speed) {
                // cerr << "b" << endl;
                r = 0;
                p = 2;
            }
            else {
                // cerr << "c" << endl;
                r = r2decelerate(hSpeed, vSpeed);
                p = 4;
            }
        }
        else {
            if (abs(hSpeed > 0) and direction(hSpeed) != dirToLZ(a) or abs(hSpeed) > max_h_speed * 4) {
                // cerr << "d" << endl;
                r = -stop_fall_angle * -direction(hSpeed);
                cerr << r << endl;
                p = 4;
            }
            else if (abs(hSpeed) < max_h_speed * 2) {
                // cerr << "e" << endl;
                r = -stop_fall_angle * dirToLZ(a);
                p = 4;   
            }
            else {
                // cerr << "f" << endl;
                r = 0;
                if (vSpeed < 0) p = 4;
                else p = 3;
            }
        }
    
        cout << r << " " << p << endl;
    }
}
