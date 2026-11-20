#include <iostream>
#include <vector>
using namespace std;

const string adn = "ACGT";


void backtracking(int i, string& sol, int n){
    if (i == n) cout << sol << endl;
    else{
        for (int l = 0; l < 4; ++l){
            sol[i] = adn[l];
            backtracking(i+1,sol,n);
            sol[i] = ' ';
        }
    }
    
}

int main(){
    int n;
    cin >> n;
    string sol(n,' ');
    backtracking(0,sol, n);
}
