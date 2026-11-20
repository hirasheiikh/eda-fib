#include <iostream>
#include <map>
using namespace std;

int main(){
    string name,op;
    map <string,int> m; // name,diners
    while (cin >> name >> op){
        if (op == "enters"){
            auto it = m.find(name);
            if (it == m.end()) m.insert({name,0}); //si el jugador no hi és ja l'insertem
            else cout << name << " is already in the casino" << endl;
        }
        else if (op == "wins"){
            int diners;
            cin >> diners;
            auto it = m.find(name);
            if (it != m.end()) it->second += diners; //el jugador està
            else cout << name << " is not in the casino" << endl;
        }
        else if (op == "leaves"){
            auto it = m.find(name);
            if (it != m.end()){
                cout << name << " has won " << it->second << endl;
                m.erase(it);
            }
            else cout << name << " is not in the casino" << endl;
        }
    }
    cout << string (10,'-') << endl;
   
    for (auto it = m.begin(); it != m.end(); ++it){
        cout << it->first << " is winning " << it->second << endl;
    }
}