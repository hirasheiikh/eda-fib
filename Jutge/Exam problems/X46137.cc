#include <iostream>
#include <vector>
using namespace std;


void backtracking(int n,int i,string& sol, int count_a, int count_b){
    if (abs(count_a - count_b) > 2) return;
    else if (i == n){
        cout << sol << endl;
        return;
    } 
    else{
        sol[i] = 'a';
        backtracking(n,i+1,sol,count_a+1, count_b);
        sol[i] = 'b';
        backtracking(n,i+1,sol,count_a,count_b+1);
    }

}

int main(){
    int n;
    cin >> n;
    string s(n,' ');
    backtracking(n,0,s,0,0);
}