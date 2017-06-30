#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef struct {
    int s, d; // start, duration
} Calc;

int main()
{
    unordered_map<int, int> calc_index;
    vector<Calc> calcs;
    int N;
    cin >> N; cin.ignore();
    
    calcs.reserve(N);
    
    for (int i = 0; i < N; i++) {
        Calc c;
        cin >> c.s >> c.d;
        if (calc_index.find(c.s) == calc_index.end()) {
            calc_index[c.s] = calcs.size();
            calcs.push_back(c);
        }
        else {
            int index = calc_index[c.s];
            if (calcs[index].d > c.d) calcs[index] = c;
        }
    }
    
    sort(calcs.begin(), calcs.end(), [](const Calc& a, const Calc& b) -> bool {
        return (a.s + a.d) < (b.s + b.d);
    });
    
    int lastEndTime = 0, count = 0;
    for (auto& c : calcs) {
        if (c.s >= lastEndTime) {
            count++;
            lastEndTime = c.s + c.d;
        }
    }
    
    cout << count << endl;
}