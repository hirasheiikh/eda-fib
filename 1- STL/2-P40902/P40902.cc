#include <iostream>
#include <map>
using namespace std;

int main(){
    map<string,int> casino;
    string name;
    while (cin >> name){ //clau = name; contingut = money 
        string command;
        cin >> command;
        if (command == "enters"){
            auto it = casino.find(name);
            if (it != casino.end()) cout << name << " is already in the casino" << endl;
            else casino.insert({name,0});
        }
        else if (command == "wins"){
            int money;
            cin >> money; // sempre que la comanda es wins llegeix els diners guanyats
            auto it = casino.find(name);
            if (it == casino.end()) cout << name << " is not in the casino" << endl;
            else casino[name] += money;
        }
        else if (command == "leaves"){
            auto it = casino.find(name);
            if (it == casino.end()) cout << name << " is not in the casino" << endl;
            else if (it != casino.end()){
                auto it = casino.find(name);
                cout << name << " has won " << it->second << endl;
                casino.erase(it);
            }
        }
    }
    cout << "----------" << endl;
    if (not casino.empty()){
        auto it = casino.begin();
        while (it != casino.end()){
            cout << it->first << " is winning " << it->second;
            if (it != casino.end()) cout << endl;
            ++it;
        }
    }
}