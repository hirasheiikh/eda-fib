#include <iostream>
#include <map>
using namespace std;

int main(){
    map<string,int> m; //string = paraula, int = times
    string comanda;
    while (cin >> comanda){
        if (comanda == "store"){
            string paraula;
            cin >> paraula;
            ++m[paraula];
        }
        else if (comanda == "delete"){
            string paraula;
            cin >> paraula;
            auto it = m.find(paraula);
            if (it != m.end()) --m[paraula];
            if (m[paraula] == 0) m.erase(paraula);
        }
        else if (comanda == "minimum?"){
            if (m.empty()) cout << "indefinite minimum" << endl;
            else{
                auto it = m.begin();
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        }
        else if (comanda == "maximum?"){
            if (m.empty()) cout << "indefinite maximum" << endl;
            else{
                auto it = m.end();
                --it; 
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
        }

    }


}