#include <iostream>
#include <vector>
using namespace std;

void backtracking(int x, int n, const vector<int>& monedes, int sum_tot, int i, vector<int>& usats, int& maneres){
    if (sum_tot == x){
        ++maneres;
        return;
    }
    if (sum_tot > x or i >= n) return;
    for (int usat = 0; usat < 2; ++usat){
        int sum_act = (usat+1)*monedes[i];
        if (sum_tot + sum_act <= x){
            ++usats[i];
            backtracking(x,n,monedes,sum_tot+sum_act,i+1,usats,maneres);
            --usats[i];
        }
    }
    backtracking(x,n,monedes,sum_tot,i+1,usats,maneres);
}


int main(){
    int x,n;
    while (cin >> x >> n){
        vector<int> coins(n), usats(n,0);
        for (int i = 0; i < n; ++i) cin >> coins[i];
        int maneres = 0;
        backtracking(x,n,coins,0,0,usats,maneres);
        cout << maneres << endl;
    }
}