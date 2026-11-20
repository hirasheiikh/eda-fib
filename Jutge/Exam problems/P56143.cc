#include<iostream>
#include<queue>
#include <vector>
#include<stack>
using namespace std;

typedef pair<int,int> Pos;
typedef vector<Pos> VI;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<VI> VVI;

const vector<Pos> Coordenades = {{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};

bool pos_ok(VVC& mapa, Pos& pos){
    int n = mapa.size();
    int m = mapa[0].size();
    if (pos.first >= 0 and pos.second >= 0 and pos.first < n and pos.second < m) return true;
    return false;
}

bool bfs(VVC& mapa, VVI& rec, Pos ini, stack<Pos>& path){
    queue<Pos> Q;
    Q.push(ini);
    mapa[ini.first][ini.second] = 'X';

    while (not Q.empty()){
        Pos act = Q.front();
        Q.pop();

        for (int i = 0; i < 8; ++i){
            int x = act.first + Coordenades[i].first;
            int y = act.second + Coordenades[i].second;

            Pos p = {x,y};

            if (pos_ok(mapa,p) and mapa[x][y] != 'X'){
                rec[x][y] = act;
                if (mapa[x][y] == 'F'){
                    Pos curr = {x,y};
                    while (curr != ini){
                        path.push(curr);
                        curr = rec[curr.first][curr.second];
                    }
                    path.push(ini);
                    return true;
                }
                mapa[x][y]= 'X';
                Q.push({x,y});
            }
        }
    }
    return false;
}

int main(){
    int n,m;
    while (cin >> n >> m){
        VVC mapa(n, VC(m));
        Pos ini;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                cin >> mapa[i][j];
                if (mapa[i][j] == 'K') ini = {i,j};
            }
        }
        stack<Pos> path;
        VVI rec(n,VI(m)); //rectangle
        bool b = bfs(mapa,rec,ini,path);
        if (not b) cout << 0 << endl;
        else{
            cout << path.size();
            while (not path.empty()){
                cout << "  " << path.top().first << ' ' << path.top().second;
                path.pop();
            }
            cout << endl;
        }
    }
}