#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool pot_casar(int V, vector<int>& diamants) {
    int n = diamants.size();
    if (n < 2) return false;
    
    // Ordenem el vector amb sort (O(n log n))
    sort(diamants.begin(), diamants.end());
    
    // Algorisme de dos punters (O(n))
    int esq = 0;
    int dre = n - 1;
    
    while (esq < dre) {
        int suma = diamants[esq] + diamants[dre];
        
        if (suma == V) {
            return true; // Trobat!
        } else if (suma < V) {
            esq++; // Necessitem una suma més gran
        } else {
            dre--; // Necessitem una suma més petita
        }
    }
    
    return false; // No hem trobat cap parella
}

int main() {
    int V, n;
    while (cin >> V >> n && (V != 0 || n != 0)) {
        vector<int> diamants(n);
        for (int i = 0; i < n; ++i) {
            cin >> diamants[i];
        }
        
        if (pot_casar(V, diamants)) {
            cout << "married" << endl;
        } else {
            cout << "single" << endl;
        }
    }
    
    return 0;
}