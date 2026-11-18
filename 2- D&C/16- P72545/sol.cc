#include <iostream>
#include <vector>
#include <climits> // Necessari per utilitzar INT_MAX

using namespace std;

// Funció auxiliar recursiva per trobar l'element k-èssim
// k: element relatiu que busquem
// i: índex actual d'inici del vector v1
// j: índex actual d'inici del vector v2
int cerca_k_essim(int k, const vector<int>& v1, const vector<int>& v2, int i, int j) {
    // Casos base: si un dels vectors ja no té elements rellevants,
    // la resposta ha d'estar necessàriament a l'altre vector.
    if (i >= v1.size()) {
        return v2[j + k - 1];
    }
    if (j >= v2.size()) {
        return v1[i + k - 1];
    }

    // Cas base: si busquem el 1r element, és el més petit dels dos actuals
    if (k == 1) {
        if (v1[i] < v2[j]) {
            return v1[i];
        } else {
            return v2[j];
        }
    }

    // Pas recursiu: intentem descartar la meitat de k elements
    int meitat = k / 2;

    // Obtenim els valors a comparar.
    // Si l'índex surt fora del vector, assignem INT_MAX (infinit)
    // per assegurar que descartem l'altre vector.
    
    int val1;
    if (i + meitat - 1 < v1.size()) {
        val1 = v1[i + meitat - 1];
    } else {
        val1 = INT_MAX;
    }

    int val2;
    if (j + meitat - 1 < v2.size()) {
        val2 = v2[j + meitat - 1];
    } else {
        val2 = INT_MAX;
    }

    // Comparació i descart
    if (val1 < val2) {
        // La meitat esquerra de v1 és més petita, per tant segur que
        // l'element k-èssim no es troba allà. La descartem.
        // Restem 'meitat' a k perquè hem descartat aquests elements.
        return cerca_k_essim(k - meitat, v1, v2, i + meitat, j);
    } else {
        // El mateix però descartant la part de v2.
        return cerca_k_essim(k - meitat, v1, v2, i, j + meitat);
    }
}

// Funció principal demanada per l'enunciat
int select(int k, const vector<int>& v1, const vector<int>& v2) {
    // Iniciem la cerca recursiva des dels índexs 0
    return cerca_k_essim(k, v1, v2, 0, 0);
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> A(n);
        for (int i = 0; i < n; ++i) cin >> A[i];
        
        int m;
        cin >> m;
        vector<int> B(m);
        for (int i = 0; i < m; ++i) cin >> B[i];

        int t;
        cin >> t;
        while (t--) {
            int k;
            cin >> k;
            cout << select(k, A, B) << endl;
        }
    }
    return 0;
}