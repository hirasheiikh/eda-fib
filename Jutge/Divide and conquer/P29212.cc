#include <iostream>
using namespace std;

int exp_modular(int n, int k,int m){
    if (k == 0) return 1;
    int aux = exp_modular(n,k/2,m);
    int res = (aux*aux)%m;
    if (k%2 != 0) res = res*n;
    return res%m;
}


int main(){
    int n,k,m;
    while (cin >> n >> k >> m){
        cout << exp_modular(n,k,m) << endl;
    }
}