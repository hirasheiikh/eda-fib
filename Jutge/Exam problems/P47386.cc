#include <iostream>
#include <map>
using namespace std;

int main(){
    string op;
    map<string,string> liats;
    while (cin >> op){
        if (op == "liats"){
            string x,y;
            cin >> x >> y;
            if (liats[x] != "") liats[liats[x]] = "";
            liats[x] = y;
            if (liats[y] != "") liats[liats[y]] = "";
            liats[y] = x;
        }
        else if (op == "info"){
            cout << "PARELLES:" << endl;
            for (auto it = liats.begin(); it != liats.end(); ++it){
                if (it->second != "" and it->first < it->second) cout << it->first << ' ' << it->second << endl;
            }
            cout << "SOLS:" << endl;
            for (auto it= liats.begin(); it != liats.end(); ++it){
                if (it->second == "") cout << it->first << endl;
            }
            cout << string(10,'-') << endl;
        }
    }
}
