#include <iostream>
#include <map>
using namespace std;

int main(){
    cout.setf(ios::fixed);
    cout.precision(4);

    string comanda;
    map<int,int> m; // map<numero,times>
    double suma_total = 0.0;
    int count_total = 0;

    while (cin >> comanda){
        if (comanda == "number"){
            int num;
            cin >> num;
            ++m[num];
            suma_total += num;
            ++count_total;
        }
        else if (comanda == "delete"){
            if (!m.empty()){
                auto itmin = m.begin();
                int key = itmin->first;
                suma_total -= key;
                --count_total;
                if (--m[key] == 0) m.erase(key);
            }
        }

        if (m.empty()){
            cout << "no elements" << endl;
        }
        else {
            auto itmin = m.begin();
            auto itmax = prev(m.end());
            cout << "minimum: " << itmin->first
                 << ", maximum: " << itmax->first
                 << ", average: " << (suma_total / count_total) << endl;
        }
    }
}