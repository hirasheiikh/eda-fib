#include <iostream>
#include <vector>
using namespace std;

//mejor hacer un DFS
typedef vector<vector<int>> Grafo;

int num_vertices(const Grafo& G, int act, vector<bool>& vis){
    vis[act] = true;
    int num = 1;

    //adyacentes
    for (int v: G[act]){ //for (int i = 0; i < G[act].size(); ++i) int v = G[act][i];
        if (not vis[v]){
            num += num_vertices(G, v, vis);
        }
    }
    return num;

}

pair<int, int> comp_min_max(const Grafo& G){
    int n = G.size();
    vector<bool> vis(n,false);
    
    int max = 0;
    int min = 1e9;

    for (int i = 0; i < n; ++i){
        if (not vis[i]){
            int num = num_vertices(G,i,vis);
            //num es el numero de vertices de la componente conexa que tiene el vertice i
            if (num > max) max = num;
            if (num < min) min = num;
        }
    }
    return {min,max};
}


int main(){
    int n,m; // n = vértices, m = aristas
    while(cin >> n >> m){
        Grafo G(n);
        for (int i = 0; i < m; ++i){
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        pair<int,int> res = comp_min_max(G); //first = minimo, second = maximo
        cout << res.first << ' ' << res.second << endl;
    }
}