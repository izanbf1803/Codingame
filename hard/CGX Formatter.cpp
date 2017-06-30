#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    bool inside_literal = false;
    bool new_line;
    bool added_new_line;
    int ident_level = 0;
    int ident_level_change;
    string cgx, line, r; // r -> result text
    int N;
    cin >> N; cin.ignore();
    
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        for (char c : line) {
            if (c == '\'')
                inside_literal = !inside_literal;
            if (inside_literal or (c != ' ' and c != '\t'))
                cgx += c;
        }
    }
    
    for (int i = 0; i < cgx.size(); i++) {
        char c = cgx[i];
        string x(1, c);
        ident_level_change = 0;
        added_new_line = false;
        
        if (!inside_literal) {
            switch (c) {
                case '(':
                    if (i < cgx.size() - 1 and cgx[i+1] != ')')
                        x = "(\n";
                    else
                        x = "(";
                    ident_level_change = 1;
                    added_new_line = true;
                    break;
                    
                case ')':
                    r += "\n";
                    x = ")";
                    ident_level--;
                    new_line = true;
                    break;
                    
                case '=':
                    if (i < cgx.size() - 1 and cgx[i+1] == '(') {
                        r += "=";
                        x = "\n";
                        added_new_line = true;
                    }
                    break;
                    
                case ';':
                    x = ";\n";
                    added_new_line = true;
                    break;
                    
                case '\'':
                    inside_literal = true;
                    break;
            }
        }
        else if (c == '\'') {
            inside_literal = false;
        }
        
        if (new_line)
            for (int i = 0; i < ident_level; i++) r += "    ";
        r += x;
        
        ident_level += ident_level_change;
        new_line = added_new_line;
    }
    
    cout << r << endl;
}
