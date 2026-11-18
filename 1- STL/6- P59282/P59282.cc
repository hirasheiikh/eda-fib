#include <iostream>
#include <map>
using namespace std;

int main(){
    cout.setf(ios::fixed);
    cout.precision(4);
    string comanda;
    map<int,int> m; // map<numero,times>
    double suma = 0.0;
    int count = 0;

    while (cin >> comanda){
        if (comanda == "number"){
            int num;
            cin >> num;
            ++m[num];
            suma += num;
            ++count;
        }
        if (comanda == "delete"){
            if (not m.empty()){
                auto it = m.begin();
                int min = it->first;
                suma -= min;
                --count;
                --m[min];
                if (m[min] == 0) m.erase(min);
            }
        }
        if (not m.empty()){
            auto min = m.begin();
            auto max = m.end();
            --max;
            cout << "minimum: " << min->first << ", " << "maximum: " << max->first << ", " << "average: " << suma/count << endl;
        }
        else cout << "no elements" << endl;
    }
    
}