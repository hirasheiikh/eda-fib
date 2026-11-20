#include <iostream>
#include <vector>
using namespace std;

const string abc = "abcdefghi";

void bt(string& sol, int i, int n, vector<bool>& used) {
    if (i == n) cout << sol << endl;
    else {
        for (int j = 0; j < n; ++j) {
            if (not used[j] and (j == 0 or sol[i-1] != abc[j-1])) {
                sol[i] = abc[j];
                used[j] = true;
                bt(sol, i+1, n, used);
                used[j] = false;
            } 
        }
    }
}

int main() {
    int n;
    cin >> n;
    string sol(n, ' ');
    vector<bool> used(n,false);
    bt(sol, 0, n,used);
}