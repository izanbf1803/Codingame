#include <bits/stdc++.h>
using namespace std;

#define D(x) cerr << #x << " = " << (x) << ", "
#define REP(i, k) for(int i = 0; i < (k); ++i)
#define RREP(i, k) for(int i = (k)-1; i >= 0; --i)

typedef unsigned int uint;
typedef unsigned long ul;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;

template<typename T> using V = vector<T>;
template<typename T, typename U> using umap = unordered_map<T,U>;
template<typename T> using uset = unordered_set<T>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

struct light {
    int d, t;
};

const ld frac_10_36 = 10.0/36.0;
int n, maxkmh;
V<light> lights;

int main()
{
    ios::sync_with_stdio(0);
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