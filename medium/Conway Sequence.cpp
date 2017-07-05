#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int R, L;
    cin >> R >> L;

    vector<int> digits = { R }; // Digits

    for (int k = 0; k < L - 1; k++) {
        vector<int> ndigits; // new Digits 
        
        int ldigit = digits[0]; // last digit
        int count = 1;
        
        const auto push_current = [&ndigits, &count, &ldigit]() {
            ndigits.push_back(count);
            ndigits.push_back(ldigit); 
            count = 1;
        };
        
        for (int i = 1; i < digits.size(); i++) {
            if (digits[i] == ldigit) {
                count++;
            }
            else {
                push_current();
                ldigit = digits[i];
            }
        }
        
        push_current();
        digits = ndigits;   
    }
    
    cout << digits[0];
    for (int i = 1; i < digits.size(); i++)
        cout << ' ' << digits[i];
    cout << endl;
}
