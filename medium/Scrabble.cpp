#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<char, int> letter_val;

bool possible(const map<char, int>& pieces, const string& word)
{
    map<char, int> pieces_left = pieces;
    bool possible = true;
    int n;
        
    for (int j = 0; j < word.size(); j++) { // Check if word is possible with pieces
        if (pieces_left.find(word[j]) != pieces_left.end()) {
            n = --pieces_left[ word[j] ];
            if (n >= 0) continue;
        }
        //cerr << word << " " << word[j] << " " << n << endl;
        possible = false;
        break;
    }
    
    return possible;
}

int main()
{
    letter_val['e'] = 1;
    letter_val['a'] = 1;
    letter_val['i'] = 1;
    letter_val['o'] = 1;
    letter_val['n'] = 1;
    letter_val['r'] = 1;
    letter_val['t'] = 1;
    letter_val['l'] = 1;
    letter_val['s'] = 1;
    letter_val['u'] = 1;
    
    letter_val['d'] = 2;
    letter_val['g'] = 2;
    
    letter_val['b'] = 3;
    letter_val['c'] = 3;
    letter_val['m'] = 3;
    letter_val['p'] = 3;
    
    letter_val['f'] = 4;
    letter_val['h'] = 4;
    letter_val['v'] = 4;
    letter_val['w'] = 4;
    letter_val['y'] = 4;
    
    letter_val['k'] = 5;
    
    letter_val['j'] = 8;
    letter_val['x'] = 8;
    
    letter_val['q'] = 10;
    letter_val['z'] = 10;
    
    int N;
    cin >> N; cin.ignore();
    
    vector<string> words;
    
    for (int i = 0; i < N; i++) {
        string w;
        getline(cin, w);
        words.push_back(w);
    }
    
    map<char, int> pieces;
    string letters;
    getline(cin, letters);
    
    for (int i = 0; i < letters.size(); i++) {
        if (pieces.find(letters[i]) == pieces.end())
            pieces[ letters[i] ] = 0;
        pieces[ letters[i] ]++;
    }

    int index;
    int max_val = 0;
    
    for (int i = 0; i < words.size(); i++) {
        if (possible(pieces, words[i])) {
            int val = 0;
            
            for (int j = 0; j < words[i].size(); j++) // Calculate score of word
                val += letter_val[ words[i][j] ];
            
            if (val > max_val) {
                index = i;
                max_val = val;
            }
        }
    }

    if (max_val == 0) cout << "invalid word" << endl;
    else cout << words[index] << endl;
}
