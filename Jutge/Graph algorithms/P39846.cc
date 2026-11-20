#include <iostream>
#include <vector>
#include <queue>
using namespace std;


typedef vector<char> Col;
typedef vector<Col> Graf;
typedef pair<int,int> Pos;

const vector<Pos> Coordenades = {{0,1},{0,-1},{1,0},{-1,0}};

bool pos_ok(Graf&G, Pos& p){
    int n = G.size();
    int m = G[0].size();
    return (p.first >= 0 and p.first < n and p.second >= 0 and p.second < m);
}

int bfs(Graf G, Pos& p){
    queue<pair<Pos,int>> q;
    Pos ini = p;
    Pos act;
    Pos seg;

    q.push({ini,0}); //pos p, 0 passos
    G[ini.first][ini.second] = 'X'; //marquem la posició inicial com visitada
    int dist_max = 0;

    while (not q.empty()){
        act = q.front().first;
        int d = q.front().second;
        q.pop();
        for (int i = 0; i < 4; ++i){
            seg.first = act.first + Coordenades[i].first;
            seg.second = act.second + Coordenades[i].second;
            if (pos_ok(G,seg) and G[seg.first][seg.second] != 'X'){
                if (G[seg.first][seg.second] == 't'){
                    if (dist_max < d + 1) dist_max = d + 1; //d + 1 perque es la distància desde la següent posició
                }
                q.push({seg,d+1});
                G[seg.first][seg.second] = 'X';
            }
        }
    }
    return dist_max;
}

int main(){
    int n, m;
    cin >> n >> m;
    Graf G(n,Col(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            cin >> G[i][j];
        }
    }
    int f,c;
    cin >> f >> c; 
    --f;
    --c;
    Pos p ={f,c};
    int max = bfs(G,p);
    if (max == 0) cout << "no es pot arribar a cap tresor" << endl;
    else cout << "distancia maxima: " << max << endl;
}