#include <iostream>
#include <map>
using namespace std;
const int MAX = 100000000;

int main(){
    int x,y,n;
   
    
    while (cin >> x >> y >> n){
        map<int,int> m; //n, posicio 
        bool cicle = false;
        int pos_ini = 0;
        int pos_fi = 0;
        int i = 0;
        while (n <= MAX and not cicle){
            auto it = m.find(n);
            if (it != m.end()){ //si ja està vol dir que comencem un cicle
                pos_fi = i;
                pos_ini = m[n];
                cicle = true;
                
            }
            else m.insert({n,i});

            if (n%2 == 0) n = n/2 + x; //n parell
            else n = 3*n+y; //n senar
            ++i;
        }
        if (n < MAX) cout << pos_fi - pos_ini << endl;
        else cout << n << endl;
    }
}
