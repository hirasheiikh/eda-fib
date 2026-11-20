#include <iostream>
#include <map>
using namespace std;



int main(){
    map<string,int> m;
    string op;
    while (cin >> op){
        if (op == "store"){
            string paraula;
            cin >> paraula;
            if (m.empty()) m.insert({paraula,1});
            else{
                auto it = m.find(paraula);
                if (it == m.end()) m.insert({paraula,1});
                else ++m[paraula];
            }
        }
        else if (op == "delete"){
            string paraula;
            cin >> paraula;
            if (!m.empty()){
                auto it = m.find(paraula);
                if (it != m.end()){
                    --m[paraula];
                    if (it->second == 0) m.erase(paraula);
                }
            }
        }
        else if (op == "minimum?"){
            if (!m.empty()){
                auto it = m.begin();
                cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
            else cout << "indefinite minimum" << endl;
        }
        else{
            if (!m.empty()){
                auto it = m.end();
                --it;
                cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
            }
            else cout << "indefinite maximum" << endl;
        }
    }
}