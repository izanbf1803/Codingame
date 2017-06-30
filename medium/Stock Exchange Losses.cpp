#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n; cin.ignore();
    
    vector<int> v(n); // Values
    
    for (int i = 0; i < n; i++) cin >> v[i]; cin.ignore();
    
    int max_loss = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (v[i] > v[j]) {
                int loss = v[i] - v[j];
                if (loss > max_loss) max_loss = loss;
            }
            else break;
        }
    }
    
    cout << -max_loss << endl;
}
