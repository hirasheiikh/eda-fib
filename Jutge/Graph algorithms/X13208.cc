#include <iostream>
#include <vector>
#include <queue> //priority queue perquè volem agafar el camí més petit per arribar.
using namespace std;

typedef vector<vector<int>> Mapa;
typedef pair<int,int> Pos;
typedef pair<int,Pos> DP; // first = distancia, second = posicio

const int infinit = 1e9;
const vector<Pos> dir = {{-1,0},{0,1},{1,0},{0,-1}};

bool es_periferia(int x, int y, int n){
    return x == 0 or y == 0 or x == n - 1 or y == n -1;   
}

int coste_min(const Mapa &t, int n){
    Mapa dist(n, vector<int>(n,infinit));
    Mapa vis(n, vector<int>(n,0));
    priority_queue<DP, vector<DP>,greater<DP>> PQ; //ordenar de mínimo a máximo
    int c = n/2; // volem començar a recorre el mapa pel mig
    PQ.push({t[c][c], {c,c}}); // guardem el valor n/2
    dist[c][c] = t[c][c];

    while (not PQ.empty()){
        Pos act = PQ.top().second;
        PQ.pop();

        int x_act = act.first;
        int y_act = act.second;
        if (vis[x_act][y_act] == 0){
            vis[x_act][y_act] = 1;
        }

        if (es_periferia(x_act, y_act, n)) return dist[x_act][y_act];

        for (Pos d:dir){
            int x = x_act + d.first;
            int y = y_act + d.second;

            if (dist[x][y] > dist[x_act][y_act] + t[x][y]){
                dist[x][y] = dist[x_act][y_act] + t[x][y]; 
                PQ.push({dist[x][y], {x,y}});
            }
        }
    }
    return 0;
}



int main(){
    int n;
    while (cin >> n){
        Mapa t(n, vector<int>(n));
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                cin >> t[i][j];
            }
        }
        cout << coste_min(t,n) << endl;
    }
}