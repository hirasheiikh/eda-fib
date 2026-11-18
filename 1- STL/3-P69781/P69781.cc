#include <iostream>
#include <map>
using namespace std;
const int MAX = 100000000;



int main(){
    int x, y, n;
    while (cin >> x >> y >> n){
        map<int,int> v;
        bool cicle = false;
        int pos_ini = 0;
        int pos_fi = 0;
        int i = 0;
        while (n <= MAX and not cicle){
            auto it = v.find(n);
            if (it != v.end()){   
                pos_fi = i;
                pos_ini = v[n];
                cicle = true;
            }
            else{ // si entra una n que no estava
                v.insert({n,i}); //guardem el numero i la seva posició
            }
            if (n%2 == 0) n = n/2 + x;
            else n = 3*n + y;  
            ++i;
        }
        //pos_ini = v[n];
        if (n < MAX ) cout << pos_fi - pos_ini << endl;
        else cout << n << endl;
    }
}