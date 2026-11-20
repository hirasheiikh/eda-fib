#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Permutacio;

Permutacio multiplica(Permutacio& a, Permutacio& b){
    int n = a.size();
    Permutacio res(n);
    for (int i = 0; i < n; ++i){
        res[i] =  a[b[i]];
    }
    return res;
    
}

Permutacio potencia(Permutacio& p, int k){
    int n = p.size();
    if (k == 0){
        //cas base -> permutacio identitat on i = 0 amb valor 0 i = 1 -> valor 1 etc
        Permutacio id(n);
        for (int i = 0; i < n; ++i) id[i] = i;
        return id;
    }
    Permutacio aux = potencia(p, k/2);
    Permutacio res = multiplica(aux,aux);

    if (k%2) res = multiplica(res,p);
    return res;
}



int main(){
    int n;
    while (cin >> n){
        Permutacio p(n);
        for (int i = 0; i < n; ++i){
            cin >> p[i];
        }
        int k;
        cin >> k;

        Permutacio resultat = potencia(p,k);
        for (int i = 0; i < n; ++i){
            if (i > 0) cout << ' ';
            cout << resultat[i];
        }
        cout << endl;
    }
}