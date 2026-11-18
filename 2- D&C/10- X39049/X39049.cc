#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Permutacio;

Permutacio multiplica(Permutacio& A, Permutacio& B){
    int n = A.size();
    Permutacio res(n);
    for (int i = 0; i < n; ++i){
        res[i] = A[B[i]];
    }
    return res;
}

Permutacio potencia(Permutacio& p, int k){
    int n = p.size();
    if (k == 0){
        //Cas base: Permutació identitat: {0,1,2} pos 0 = 0; pos 1 = 1; pos 2 = 2...
        Permutacio id(n);
        for (int i = 0; i < n; ++i) id[i] = i;
        return id;
    }
    Permutacio aux = potencia(p, k/2);
    Permutacio res = multiplica(aux,aux);

    if (k%2 != 0) res = multiplica(res,p);

    return res;

}

int main(){
    int n;
    while (cin >> n){
        Permutacio p(n);
        for (int i = 0; i < n; ++i){
            cin >> p[i];
            //--p[i]; //fem aquesta resta ja que els índex a c++ comencen a 0 i observem que els n nombres van de 1 a n
        }
        
        int k;
        cin >> k;

        Permutacio resultat = potencia(p,k);
        for (int i = 0; i < n; ++i){
            if (i > 0) cout << " ";
            cout << resultat[i];
        }
        cout << endl; 
    }
    
}