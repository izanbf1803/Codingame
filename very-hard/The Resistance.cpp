#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string alphabet[] = { // ascii to morse
    ".-", "-...", "-.-.", "-..", ".", "..-.", 
    "--.", "....", "..", ".---", "-.-", ".-..", 
    "--", "-.", "---", ".--.", "--.-", ".-.", 
    "...", "-", "..-", "...-", ".--", "-..-", 
    "-.--", "--..",
};
unordered_map<string,int> times; // times morse codification appears among given words
ll dp[(int)1e5]; // memoization array
string seq; // morse sequence

string encode(const string& s)
{
    string r;
    for (char c : s) r += alphabet[c-'A'];
    return r;
}

ll cnt(int i)
{
    if (i == seq.size()) return 1;
    if (i > seq.size()) return 0;
    ll& mem = dp[i];
    if (mem == -1) {
        string s;
        mem = 0;
        for (int j = i; j <= i+80 and j < seq.size(); ++j) { 
            s += seq[j];
            auto it = times.find(s);
            if (it != times.end()) {
                mem += it->second * cnt(j+1);
            }
        }
    }
    return mem;
}

int main()
{
    memset(dp, 0xFF, sizeof(dp)); // fill dp[] with -1
    int n; // n of words in input
    cin >> seq;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        ++times[encode(word)];
    }
    cout << cnt(0) << endl;
}