#include <iostream>
#include <vector>
using namespace std;



int i_mes_a_la_dreta(double x, const vector<double>& v, int l, int r){
    if (l > r) return r+1;
    int m = (l+r)/2;
    if (v[m] == x){
        if (v[m+1] == x and m < r) return i_mes_a_la_dreta(x,v,m+1,r);
        return m+1;
    }
    else if (v[m] > x) return i_mes_a_la_dreta(x,v,l,m-1);
    else return i_mes_a_la_dreta(x,v,m+1,r);

}


int mes_a_la_dreta(double x, const vector<double>& v){
    return i_mes_a_la_dreta(x,v,0,v.size()-1);
}

/*
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
*/