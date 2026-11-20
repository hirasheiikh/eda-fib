#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> Matriu; //distancies
typedef pair<int,int> Pos;
const vector<Pos> dir = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

bool pos_ok(int i, int j, int n, int m){
    return i >= 0 and i < n and j >= 0 and j < m;
}

int busca_objectiu(Pos ini, Pos fin, int n, int m){
    if (ini == fin) return 0;
    Matriu dist(n, vector<int>(m,-1));
    queue<Pos> Q;

    Q.push(ini);
    dist[ini.first][ini.second] = 0;

    while (not Q.empty()){
        Pos act = Q.front();
        Q.pop();

        for (int i = 0; i < dir.size(); ++i){
            int x = act.first + dir[i].first;
            int y = act.second + dir[i].second;

            if (pos_ok(x,y,n,m) and dist[x][y] == -1){
                dist[x][y] = dist[act.first][act.second]+1;
                if (Pos(x,y) == fin) return dist[x][y];
                Q.push({x,y});
            }
        }
    }
    return -1;
}

int pmax(int n, int m, const vector<Pos>& obj, int k, int W, int L){ //funcio per a calcular els punts màxims
    int max = 0;
    int pact = 0; //punts actuals
    for (int i = 0; i < k; ++i){
        int dist = busca_objectiu(obj[i], obj[i+1],n,m);
        if (dist == -1) return max;
        pact += W - (L*dist);
        if (pact > max) max = pact;
    }
    return max;
}

int main(){
    int n,m,W,L;
    while(cin >> n >> m >> W >> L){
        int k;
        cin >> k;
        vector<Pos> obj(k+1); //hem de guardar la posició inicial també
        obj[0] = {0,0};
        for (int i = 0; i < k; ++i){
            Pos p;
            cin >> p.first >> p.second;
            obj[i+1] = p;
        }
        cout << pmax(n,m,obj,k,W,L) << endl;
    }
}