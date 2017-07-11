#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int factorial(int n)
{
    int r = 1;
    for (; n > 1; r *= n, n--);
    return r;
}

void gen_permutations(
    vector<vector<string>>& dest,
    vector<string>& input,
    int N
) {    
    if (N == 0) {
        dest.push_back(input);
        return;
    }
    
    for (int i = N - 1; i >= 0; i--) {
        swap(input[i], input[N-1]);
        gen_permutations(dest, input, N - 1);
        swap(input[i], input[N-1]);
    }
}

int main()
{
    int N, sum = 0;
    cin >> N; cin.ignore();
    vector<string> s(N);
    
    for (int i = 0; i < N; i++) {
        cin >> s[i];
        sum += s[i].size();
    }
        
    vector<vector<string>> perms;
    perms.reserve(factorial(N));
    
    sort(s.begin(), s.end());
    gen_permutations(perms, s, N);
    
    string bestRes;
    
    for (const vector<string>& p : perms) {
        bool valid = true;
        string res;
        res.reserve(64);
        res += p[0];
        
        for (int i = 1; i < N; i++) {
            int index = -1;
            
            for (int j = 0; j < res.size(); j++) {
                bool found = true;
                for (int k = 0; k < p[i].size() and j+k < res.size(); k++) {
                    if (res[j+k] != p[i][k]) {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    index = j;
                    break;
                }
            }
            
            if (index == -1) {
                res += p[i];
                continue;
            }
            
            int dif = index + p[i].size() - res.size();
            if (dif > 0)
                res += p[i].substr(p[i].size() - dif, dif);
        }
    
        if (valid and (bestRes.size() == 0 or res.size() < bestRes.size()))
            bestRes = res;
    }
    
    cout << bestRes.size() << endl;
}
