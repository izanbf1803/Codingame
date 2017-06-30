#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stack>

using namespace std;

void print_num(const vector<string>& nums, long long n, int L, int H)
{
    stack<int> digits;
    while (n >= 20)
    {
        digits.push(n % 20);
        n /= 20;
    }
    digits.push(n % 20);
    
    while (not digits.empty()) {
        for (int i = 0; i < H; i++)
            cout << nums[digits.top()].substr(i * L, L) << endl;   
        digits.pop();
    }
}

int line_to_digit(const vector<string>& nums, const string& n) 
{   
    for (int i = 0; i < 20; i++) {
        if (n == nums[i]) return i;
    }
}

long long parse_num(const vector<string>& nums, const string& n, int size)
{
    long long res = 0;
    for (int i = 0; i < n.size() / size; i++) {
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] == n.substr(i * size, size)) 
                res += j * pow(20, (n.size() / size) - i - 1);
        }
    }
    
    return res;
}

int main()
{
    int L;
    int H;
    int size;
    cin >> L >> H; cin.ignore();
    
    size = L * H;
    
    vector<string> nums(20);
    string num1, num2;
    
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        
        for (int j = 0; j < 20; j++)
            nums[j].append(numeral.substr(j*L, L));
    }
    
    int S1;
    cin >> S1; cin.ignore();
    
    for (int i = 0; i < S1; i++) {
        string num1Line;
        cin >> num1Line; cin.ignore();
        num1.append(num1Line);
    }
    
    int S2;
    cin >> S2; cin.ignore();
    
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        num2.append(num2Line);
    }
    
    char operation;
    cin >> operation; cin.ignore();
    
    long long res, n1, n2;
    
    n1 = parse_num(nums, num1, size);
    n2 = parse_num(nums, num2, size);
    
    switch (operation) {
        case '+':
            res = n1 + n2;
            break;
        case '-':
            res = n1 - n2;
            break;
        case '*':
            res = n1 * n2;
            break;
        case '/':
            res = n1 / n2;
            break;
    }
    
    print_num(nums, res, L, H);
}
