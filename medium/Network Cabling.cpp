#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    cin >> N; cin.ignore();
    
    vector<int> x(N), y(N);
    
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i]; cin.ignore();
    
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    
    int median_y = y.size() % 2 ? y[y.size()/2] : (y[y.size()/2-1] + y[y.size()/2]) / 2;
    int delta_x = (x[N-1] - x[0]);
    unsigned long long sum_of_diff_to_median_y = 0;
    
    for (int i = 0; i < N; i++) sum_of_diff_to_median_y += abs(y[i] - median_y);
    
    cout << sum_of_diff_to_median_y + delta_x << endl;
}
