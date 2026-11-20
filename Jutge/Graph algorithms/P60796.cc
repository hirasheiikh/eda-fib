#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VCC;
typedef pair<int,int> Pos;

const vector<Pos> Coordenades = {{0,1},{0,-1},{1,0},{-1,0}};



bool pos_ok(const VCC& tauler, const Pos& seg){
    int n = tauler.size();
    int m = tauler[0].size();
    return seg.first >= 0 and seg.first < n and seg.second >= 0 and seg.second < m;
}

int bfs(VCC& tauler, Pos& ini){
    queue<pair<Pos,int>> q;
    q.push({ini,0});
    tauler[ini.first][ini.second] = 'X';
    Pos act;
    Pos seg;

    while (not q.empty()){
        int dist = q.front().second;
        act = q.front().first;
        q.pop();
        for (int i = 0; i < 4; ++i){
            seg.first = act.first + Coordenades[i].first;
            seg.second = act.second + Coordenades[i].second;

            if (pos_ok(tauler,seg) and tauler[seg.first][seg.second]!= 'X'){
                if (tauler[seg.first][seg.second] == 't') return dist+1;
                else{
                    q.push({seg,dist+1});
                    tauler[seg.first][seg.second] = 'X';
                }
            }
        }
    }
    return -1;
}

int main(){
    int n,m;
    cin >> n >> m;
    VCC tauler(n,VC(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> tauler[i][j];
    }
    int f,c;
    cin >> f >> c;
    --f;
    --c;
    Pos ini = {f,c};
    int min = bfs(tauler,ini);
    if (min == -1) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia minima: " << min << endl;
}