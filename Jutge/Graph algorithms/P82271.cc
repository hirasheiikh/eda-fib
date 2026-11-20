#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool dfs (int v, vector<int>& col, const vector<vector<int>>& G) {
  for (int u : G[v]) {
    if (col[u] == -1) {
      col[u] = 1-col[v]; // use other color
      bool ok = dfs(u,col,G);
      if (not ok) return false;
    }
    else if (col[u] == col[v]) return false; // neighbors with the same color
  }
  return true;
}

void festa (const vector<string>& idx2name, const vector<vector<int>>& G) {
  int n = G.size();
  vector<int> col(n,-1); // -1 means no color

  bool ok = true;
  for (int v = 0; v < n and ok; ++v) { // for each connected component, fix color and propagate doing DFS
    if (col[v] == -1) { // not painted
      col[v] = 0; // fix color for person v
      ok = dfs(v,col,G);
    }
  }
  if (not ok) cout << "NO" << endl;
  else {
    cout << "SI";
    for (int i = 0; i < n; ++i)
      if (col[i] == 0) cout << " " << idx2name[i];
    cout << endl;
  }
}

int main () {
  int n;
  while (cin >> n) {
    map<string,int> M; // use the map to avoid working with strings [name --> idx]
    vector<string> idx2name; // reverse direction idx --> name [starting from 0]

    for (int i = 0; i < n; ++i) {
      string name; cin >> name;
      M[name] = i;
      idx2name.push_back(name);
    }
    
    vector<vector<int>> G(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
      string n1, n2;
      cin >> n1 >> n2;
      int id1 = M[n1];
      int id2 = M[n2];
      G[id1].push_back(id2);
      G[id2].push_back(id1);
    }

    festa(idx2name,G);
  }
}
