#include <iostream>
#include <vector>
using namespace std;


void escribir(vector<int>& v, int n){
    for (int i = 0; i < v.size(); ++i){
        if (i != 0) cout << ' ';
        cout << v[i];
    }
    cout << endl;
}


void zerouns(int n, vector<int>& sol, int i){
    if (i == n) escribir(sol,n);
    else{
        sol[i] = 0;
        zerouns(n,sol,i+1);

        sol[i] = 1;
        zerouns(n,sol,i+1);
    }

}


int main(){
    int n;
    cin >> n;
    vector<int> sol(n);
    zerouns(n,sol,0);
}