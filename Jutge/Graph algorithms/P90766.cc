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
    queue<Pos> q;
    q.push(ini);
    tauler[ini.first][ini.second] = 'X';
    int count = 0;
    while (!q.empty()){
        Pos act = q.front();
        q.pop();
        Pos seg;
        for (int i = 0; i < 4; ++i){
            seg.first = act.first + Coordenades[i].first;
            seg.second = act.second + Coordenades[i].second;
            if (pos_ok(tauler,seg) and tauler[seg.first][seg.second] != 'X'){
                if (tauler[seg.first][seg.second] == 't') ++count;
                tauler[seg.first][seg.second] = 'X';
                q.push(seg);
            }
        }
    }
    return count;
}

int main(){
    int n, m;
    cin >> n >> m;
    VCC tauler(n,VC(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> tauler[i][j];
    }
    int f, c;
    cin >> f >> c;
    --f;
    --c;
    Pos ini = {f,c};
    int num_t = bfs(tauler,ini);
    cout << num_t << endl;
}