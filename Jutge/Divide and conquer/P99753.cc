#include <iostream>
#include <vector>
using namespace std;



bool search(int x, const vector<int>& v){
    int n = v.size();
    if (n == 0) return false; //cas base
    int l = 0;
    int r = n - 1;
    while (l <= r){
        int m = (l+r)/2;
        if (v[m] == x) return true;
        if (v[l] <= v[m]){
            if (v[l] <= x and v[m] >= x) r = m - 1; //vol dir que x és dins el rang
            else l = m + 1;
        }
        else{
            if (x > v[m] and x <= v[r]) l = m + 1;
            else r = m - 1;
        }
    }
    return false;

}


int main() {
    int n;
    while (cin >> n) {
        vector<int> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int m;
        cin >> m;
        while (m--) {
          int x;
          cin >> x;
          cout << ' ' << search(x, V);
        }
        cout << endl;
    }
}
