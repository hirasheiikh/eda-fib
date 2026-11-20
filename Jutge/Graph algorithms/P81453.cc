#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef vector<set<int>> Graf;

void escriure(const vector<int>& v, int act){
    if (act != -1){
            escriure(v, v[act]);
            if (act != 0) cout << ' ';
            cout << act;
        }
}

void cami_curt(const Graf &G, vector<int>& cami){
    int n = G.size();
    vector<int> vis(n,0);
    queue<int> Q;
    Q.push(0);
    vis[0] = 1;


    while (not Q.empty()){
        int u = Q.front();
        Q.pop();

        for (auto it = G[u].begin(); it != G[u].end(); ++it){
            int v = *(it);
            if (v == n - 1){
                cami[v] = u; //últim vèrtex
                return;
            }
            else if (vis[v] == 0){
                vis[v] = 1;
                cami[v] = u;
                Q.push(v);
            }
        }

    
    }
}

int main(){
    int n,m;
    while (cin >> n >> m){
        Graf G(n);
        for (int i = 0; i < m; ++i){
            int u,v;
            cin >> u >> v;
            G[u].insert(v);
        }
        vector<int> cami(n,-1);
        cami_curt(G,cami);
        escriure(cami,n-1);
        cout << endl;
    }
}