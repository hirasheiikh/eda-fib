#include <iostream>
#include <vector>
#include <climits>
using namespace std;


int cerca_k_essim(int k, const vector<int>& v1, const vector<int>& v2, int i, int j){
    //Cas base 1: un del vectors no té elements -> la resposta és l'element k-èssim de l'altre vector 
    if (i >= v1.size()) return v2[j+k-1]; //fem -1 perquè si observem l'enunciat veiem que k comença a 1
    if (j >= v2.size()) return v1[i+k-1]; 

    //Cas base 2: si k = 1 (primer element) llavors serà el mínim entre i i j.
        // ja que tot i que no els fusionem perquè és massa costós el que fem és cercar a cada vector
    if (k == 1){
        if (v1[i] < v2[j]) return v1[i];
        else return v2[j];
    }

    //Pas recursiu: cerca dicotòmica

    int meitat = k/2;
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

//Pre:  The vectors @v1@ and @v2@ are sorted in nondecreasing order. 
    //  The index k is correct, that is, it is between 1 and @v1.size()@ + @v2.size()@. 
    //  Therefore, at least one of the vectors is not empty.
int select(int k, const vector<int>& v1, const vector<int>& v2){
  return cerca_k_essim(k,v1,v2,0,0);
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
