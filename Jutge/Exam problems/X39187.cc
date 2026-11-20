#include <iostream>
#include <vector>
using namespace std;

// d = diners
// a = accions

void backtracking(string& sol, int n, int i, int d, int a){
    if (i == n) cout << sol << endl;
    else{
        if (d > 0){
            sol[i] = 'b';
            backtracking(sol,n,i+1,d-1,a+1);
        }
        if (a > 0){
            sol[i] = 's';
            backtracking(sol,n,i+1,d+1,a-1);
        }
    }

}

int main(){
    int n,c;
    cin >> n >> c;
    string s(n,'b');
    backtracking(s,n,0,c,0);
}