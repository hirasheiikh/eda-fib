#include <iostream>
#include <vector>
using namespace std;


bool search(int x, const vector<int>& v){
    int n = v.size();
    //cas base 
    if (n == 0) return false;
    int esq = 0;
    int dre = n -1;

    while (esq <= dre){
        int mid = (esq + dre)/2;

        if (v[mid] == x) return true;

        //hem de determinar quina és la meitat que es troba ordenada.
        if (v[esq] <= v[mid]){ //en aquest cas la meitat esquerra es troba ordenada. 
            if (x >= v[esq] and x < v[mid]) dre = mid - 1; //x es troba dins del rag
            else esq = mid + 1; // vol dir que x es troba a la part dreta (la que es troba invertida)
        }
        else{ //en aquest cas suposem que la meitat dreta és la que es troba ordenada
            if (x > v[mid] and x <= v[dre]) esq = mid + 1;
            else dre = mid - 1; //si no es troba en el rang ordenat (dreta) vol dir que es troba dins del rang de l'esquerra
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
