#include <iostream>
#include <vector>
using namespace std;

int first_ocu(double x, const vector<double>& v, int l, int r){
    if (l > r) return -1;
    int m = (l + r)/2;
    if (v[m] == x){
        if (m == l or v[m-1] != x) return m;
        else return first_ocu(x,v,l,m-1);
    }
    else if (v[m] > x) return first_ocu(x, v, l, m-1);
    else // (v[m] < x) 
        return first_ocu(x,v,m+1,r);
}

int first_occurrence(double x, const vector<double>& v){
    return first_ocu(x,v,0,v.size()-1);
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
            cout << first_occurrence(x, V) << endl;
        }
    }
}
