#include <iostream>
#include <vector>
using namespace std;



int i_first_occurrence(double x, const vector<double>& v, int l, int r){
        if (l > r) return -1;
        int m = (l + r)/2;
        if (v[m] < x){
            if (m > l and v[m-1] == x) return m-1;
            return i_first_occurrence(x,v,m+1,r);
        }
        else{ //v[m] >= x
            int p_esq = i_first_occurrence(x,v,l,m-1);
            if (p_esq != -1) return p_esq;
            else if (v[m] == x) return m;
            else if (m < r and v[m+1] == x) return m+1;
            return -1;
        }
    }



 int first_occurrence(double x, const vector<double>& v){
    return i_first_occurrence(x,v,0,v.size() - 1);
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
