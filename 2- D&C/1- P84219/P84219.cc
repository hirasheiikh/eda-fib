#include <iostream>
#include <vector>
using namespace std;


int i_first_occurrence(int l, int r, const vector<double>& v, int x){
    if (l == r){
        if (v[l] == x) return l;
        return -1;
    }
    if (l > r) return -1;
    int m = (l + r)/2; 
    if (v[m] >= x) return i_first_occurrence (l,m,v,x);
    else if (v[m] < x) return i_first_occurrence(m+1,r,v,x);
}

//pre: el vector està ordenada d'una manera no decreixent --> és a dir, creixent amb possibles valors repetits
int first_occurrence(double x, const vector<double>& v){
    //si ho volem fer de manera eficient --> cerca dicotòmica (cost(log(n))). si fem un recorregut normal ens dona EE (cost (n));
    return i_first_occurrence(0,v.size()-1,v,x);
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
