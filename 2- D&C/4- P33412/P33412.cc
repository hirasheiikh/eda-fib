#include <iostream>
#include <vector>
using namespace std;


bool i_resistant_search(double x, const vector<double>& v, int l, int r){
    if (l > r) return false;
    int m = (l + r)/2;
    
    //si trobem que x es troba a la posició m o a m-1 o a m+1 retornem true.
    if (v[m] == x) return true;
    if (m > l and v[m - 1] == x) return true;
    if (m < r and v[m + 1] == x) return true;

    //en cas que no trobem la posicio de x mirem cap on buscar tenint en compte
    //que hem mirat m-1 i m+1 ja
    if (v[m] < x) return i_resistant_search(x,v,m+2,r);
    else return i_resistant_search(x,v,l,m-2); 

}

//pre: v està casi ordenat no decreixentment, és a dir, de manera creixent amb possibles valors repetits.
//hem de tenir en compte que el fet que estigui CASI ordenat vol dir que no ho està del tot 
//cada element pot estar com a màxim a distància 1 de la seva posició correcta.
bool resistant_search(double x, const vector<double>& v){
    return i_resistant_search(x,v,0,v.size()-1);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << resistant_search(x, V) << endl;
        }
    }
}