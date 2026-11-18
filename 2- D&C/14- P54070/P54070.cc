#include <iostream>
#include <vector>
using namespace std;



int i_mes_a_la_dreta(int x, const vector<double>& v, int l, int r){
    if (l > r) return r+1; //ja que r sempre serà el tamany del segment del vector -1.
    int m = (l+r)/2;
    if (v[m] == x){
        if (v[m+1] == x and m < r) return i_mes_a_la_dreta(x,v,m+1,r); //busquem a la segona meitat si n'hi ha algun num igual més a la dreta
        return m+1; //en cas que no
    }
    else if (v[m] < x) return i_mes_a_la_dreta(x,v,m+1,r);
    return i_mes_a_la_dreta(x,v,l,m-1); // v[m] > x
}


int mes_a_la_dreta(double x, const vector<double>& v){
    return i_mes_a_la_dreta(x,v,0,v.size()-1);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << mes_a_la_dreta(x, V) << endl;
        }
    }
}
