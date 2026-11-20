#include <iostream>
#include <map>
using namespace std;


int main(){
    cout.setf(ios::fixed);
    cout.precision(4);
    string comanda;
    map<int,double> m; //num que guardem, vegades que el guardem
    double res = 0, i = 0; 
    while (cin >> comanda){
        if (comanda == "number"){
            int n;
            cin >> n;
            auto it = m.find(n);
            if (it == m.end()) m.insert({n,1}); //si no hi és l'afegim amb una aparició
            else ++m[n]; //si sí que hi és sumem una aparició més

            res += n;
            ++i; //quantitat de numeros
        }
        else if (comanda == "delete"){
            if (not m.empty()){
                auto it = m.begin();
                --m[it->first];
                res -= it->first;
                --i;
                if (it->second == 0) m.erase(it);

            }
        }

        if (not m.empty()){
            int min, max;
            auto it = m.begin();
            min = it->first; //guardem el número més petit
    
            /*for (auto it2 = m.begin(); it2 != m.end(); ++it2){
                res += it2->first*it2->second; //anem guardant el total de numeros*aparicions a res.
                i += it2->second;
            }*/

            auto it2 = prev(m.end());
            max = it2->first; //quan sortim del for it2 apuntarà a m.end() - 1
            cout << "minimum: " << min << ", " << "maximum: " << max << ", " << "average: " << res/i << endl; //decimals
        }
        else cout << "no elements" << endl;
    }
}