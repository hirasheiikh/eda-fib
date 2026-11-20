#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VCC;
typedef pair<int,int> Pos;
const vector<Pos> Coordenades = {{0,1},{0,-1},{1,0},{-1,0}};

void imprimeix(const VC& cami){
    for (int i = 0; i < cami.size(); ++i) cout << cami[i];
    cout << endl;
}

bool pos_ok(const VCC& tauler, const Pos& act){
    int n = tauler.size();
    int m = tauler[0].size();
    return act.first >= 0 and act.first < n and act.second >= 0 and act.second < m; 
}

void backtracking(const VCC& tauler, const Pos& ini, const Pos& fi, VC& cami, vector<vector<bool>>& vis){
    if (ini == fi) imprimeix(cami);
    else{
        for (int l = 0; l < 4; ++l){
            int i = ini.first + Coordenades[l].first;
            int j =  ini.second + Coordenades[l].second;
            Pos act = {i,j};
            if (pos_ok(tauler,act) and vis[i][j] == false){
                cami.push_back(tauler[i][j]);
                vis[i][j] = true;
                backtracking(tauler,act,fi,cami,vis);
                cami.pop_back();
                vis[i][j] = false;
            }
        }
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    VCC tauler(n,VC(m));
    VC cami;
    vector<vector<bool>> vis(n,vector<bool>(m,false));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> tauler[i][j];
    }
    int ini_f,ini_s,fi_f,fi_s;
    cin >> ini_f >> ini_s >> fi_f >> fi_s;
    Pos ini = {ini_f,ini_s};
    Pos fi = {fi_f,fi_s};
    cami.push_back(tauler[ini_f][ini_s]);
    vis[ini_f][ini_s] = true;
    backtracking(tauler,ini,fi,cami,vis);
}