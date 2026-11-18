#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool i_es_pot_casar(int V, const vector<int>& diamants, int l, int r){
    int n = diamants.size();
    if (n < 2) return false;
    while(l < r){
        int suma = diamants[l] + diamants[r];
        if (suma == V) return true; //hem trobat 2 valors del vectror per als qual la suma ja dona V
        else if (suma < V) ++l; //si el valor de la suma és más petit que v vol dir que necessitem que la l sigui més gran
        else --r; //el mateix pero al revés 
    }
    return false;
    
    
}


bool es_pot_casar(int V, vector<int>& diamants){
    //ordenem el vector fent servir sort
    sort(diamants.begin(),diamants.end());
    return i_es_pot_casar(V,diamants,0,diamants.size() - 1);
}


int main(){
    int V,n;
    while (cin >> V >> n){
        if (V != 0 and n != 0){
            vector<int> diamants(n);
            for (int i = 0; i < n; ++i) cin >> diamants[i];
        
            if (es_pot_casar(V,diamants)) cout << "married" << endl;
            else cout << "single" << endl;
        }
    }
}