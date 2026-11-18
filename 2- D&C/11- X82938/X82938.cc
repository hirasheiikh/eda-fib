#include <iostream>
#include <vector>
using namespace std;



int trobar_pos_pic(const vector<int>& v){
    int n = v.size();
    if (n == 1) return 0;
    int esq = 0;
    int dre = n - 1;
    while(esq < dre){
        int m = (esq + dre)/2;
        if (v[m] < v[m+1]){
            //ens trobem pujant per trobar el pic
            esq = m + 1;
        }
        else{
            dre = m;
            //ens trobem baixant --> o estem al pic o ja l'hem passat, volem tornar cap enrere
        }
    }
    return esq; 
}

bool cerca_part_creixent(int x, const vector<int>& v, int esq, int dre){
    while (esq <= dre){
        int m = (esq + dre) /2;
        if (v[m] == x) return true;
        else if (v[m] < x) esq = m + 1;
        else dre = m -1;
    }
    return false;
}
 
bool cerca_part_decreixent(int x, const vector<int>& v, int esq, int dre){
    while (esq <= dre){
        int m = (esq + dre)/2;
        if (v[m] == x) return true;
        else if (v[m] > x) esq = m + 1; // invertit --> en cas que v[m] sigui major que x vol dir que si som a la part decreixent trobarem la seva posició més cap a la dreta
        else dre = m - 1;
    }
    return false;
}


bool search(int x, const vector<int>& v){
    int n = v.size();
    //cas base:
    if (n == 0) return false;
    if (n == 1) return v[0] == x;

    //trobem pic
    int pic = trobar_pos_pic(v);

    if (v[pic] < x) return false;

    //cerquem a la part creixent [0,pic]
    if (cerca_part_creixent(x,v,0,pic)) return true;

    //cerquem a la part decreixent [pic+1, n-1]
    if (cerca_part_decreixent(x,v,pic+1,v.size()-1)) return true;

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