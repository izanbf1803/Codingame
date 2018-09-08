#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
template<typename T> using V = vector<T>;

struct light {
    int d, t;
};

const ld frac_10_36 = 10.0/36.0;
int n, maxkmh;
V<light> lights;

int main()
{
    cin >> maxkmh >> n;
    for (int i = 0; i < n; ++i) {
        light l;
        cin >> l.d >> l.t;
        lights.push_back(l);
    }
    int kmh;
    for (kmh = maxkmh; kmh > 0; --kmh) {
        ld s = frac_10_36 * kmh;
        bool ok = true;
        for (const light& l : lights) {
            ld t = l.d / s;
            ld k = t / l.t;
            int c = k; // floor(k)
            if (abs(c-k) > 0.999999) ++c; // Precision error patch
            if (c & 1) {
                ok = false;
                break;
            }
        }
        if (ok) break;
    }
    cout << kmh << endl;
}
