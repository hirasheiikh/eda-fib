#include <iostream>
#include <vector>
using namespace std;



bool cerca_part_creix(int x, const vector<int>& v, int l, int r){
    if (l > r) return false;
    int m = (l+r)/2;
    if (v[m] == x) return true;
    else if (v[m] > x) return cerca_part_creix(x,v,l,m-1);
    else return cerca_part_creix(x,v,m+1,r);
}

bool cerca_part_decreix(int x, const vector<int>& v, int l, int r){
    if (l > r) return false;
    int m = (l+r)/2;
    if (v[m] == x) return true;
    else if (v[m] > x) return cerca_part_decreix(x,v,m+1,r);
    else return cerca_part_decreix(x,v,l,m-1);
}


int trobar_pos_pic(const vector<int>& v){
    int n = v.size();
    if (n == 1) return 0;
    int l = 0;
    int r = n - 1;
    
    while (l < r){
        int m = (l+r)/2;
        if (v[m] < v[m+1]){
            l = m+1; //estem pujant per trobar el pic
        }
        else r = m; //vol dir que hem passat el pic o que estem en ell
    }
    return l;
}



bool search(int x, const vector<int>& v){
    //cas bas
    int n = v.size();
    if (n == 0) return false;
    if (n == 1) return (v[n - 1] == x);


    //trobem el pic
    int pic = trobar_pos_pic(v);
    if (v[pic] < x) return false; //vol dir que no està ja que v[pic] és el valor més gran del vector
    if (cerca_part_creix(x,v,0,pic)) return true;
    if (cerca_part_decreix(x,v,pic+1,v.size()-1)) return true;

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
