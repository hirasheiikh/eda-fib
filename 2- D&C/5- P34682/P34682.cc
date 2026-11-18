#include <iostream>
#include <vector>
using namespace std;



int cerca_dico(const vector<int>&S, int a, int l, int r){
    if (l > r) return -1;
    int m = (l + r)/2;

    //TENIM EN COMPTE QUE S[m] és el valor però que m+1 és la posició i.
        //m+1 és la posició perquè comencem a comptar quan i = 1 (ens ho diu l'enunciat)
    if (S[m] + a == m+1){ //fa(i) = i;
        //hem trobat que a la posició m tenim un punt fix.
        //l'enunciat ens demana que en cas de trobar-ne un hem d'assegurar-nos que no n'hi ha cap de més petit
        int prev = cerca_dico(S,a,l,m-1);
        if (prev != -1) return prev;
        return m+1;
    }
    else if ((S[m] + a) > m + 1) return cerca_dico(S,a,l,m-1);
    else return cerca_dico(S,a,m+1,r); //en cas que el resultat sigui menor
}


//  essent fa(i) = xi + a hem de comprovar si algun valor de la
//  seqüencia S té algun valor a una posició i el qual fa(i) = i 
//  ÉS A DIR: xi + a = i
int trobar_punt_fix(const vector<int>& v, int a){
    return cerca_dico(v,a,0,v.size()-1);

}



//input: numero n, seqüència S de mida n, numero m, seq de m numeros 
int main(){
    int n;
    int n_seq = 1;
    while (cin >> n){
        vector<int> S(n);
        for (int i = 0; i < n; ++i){
            cin >> S[i];
        }
        cout << "Sequence #" << n_seq << endl;
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j){
            int a;
            cin >> a;
            int punt_fix = trobar_punt_fix(S,a);
            if (punt_fix == -1) cout << "no fixed point for " << a << endl;
            else cout << "fixed point for " << a << ": " << punt_fix << endl;
        }
        ++n_seq;
        cout << endl; //separador de seqüències

    }
}


