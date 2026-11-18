#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<int,string>& a, const pair<int,string> &b){
    if (a.first != b.first) return a.first > b.first; //imprimim el jugador amb major elo
    return a.second < b.second; //si tenen el mateix elo imprimim el menor ordenat alfetogràficament
}
int main(){
    string comanda;
    string jugador;
    string jugador2;
    map<string,pair<int,bool>> m;
    while (cin >> comanda){
        if (comanda == "LOGIN"){
            cin >> jugador;
            auto it = m.find(jugador);
            if (it == m.end()) m[jugador] = {1200,1}; //m<jugador,1>
            else if (it->second.second == 0) m[jugador].second = 1; //no hem de matxacar els punts del jugadors que han fet login, logout i login
            //si el jugador no hi és o ha tancat la sessió
        }
        else if (comanda == "LOGOUT"){
            cin >> jugador;
            auto it = m.find(jugador);
            if (it != m.end() and it->second.second == 1) m[jugador].second = 0; //m<jugador,{elo,0}>
            //si el jugador está i té la sessió iniciada
        }
        else if (comanda == "PLAY"){
            cin >> jugador >> jugador2;
            auto itj1 = m.find(jugador);
            auto itj2 = m.find(jugador2);
            if (itj1 != m.end() and itj2 != m.end() and itj1->second.second == 1 and itj2->second.second == 1){
                itj1->second.first += 10;
                itj2->second.first -= 10;
                if (itj2->second.first < 1200) itj2->second.first = 1200; 
            }
            else cout << "jugador(s) no connectat(s)" << endl;
        }
        else if (comanda == "GET_ELO"){
            cin >> jugador;
            auto it = m.find(jugador);
            cout << jugador << " " << it->second.first << endl;
        }
    }
    cout << endl;
    cout << "RANKING" << endl;

    //creem un vector per guardar els elo's i noms de tots els jugadors i poder 
    //ordenar-lo
    vector<pair<int,string>> ranking;
    for (auto it = m.begin(); it != m.end(); ++it){
        ranking.push_back({it->second.first, it->first});
    }

    sort(ranking.begin(),ranking.end(),cmp);

    for (int i = 0; i < ranking.size(); ++i){
        cout << ranking[i].second << ' ' << ranking[i].first << endl;
    }

}