#include <iostream>
#include <vector>

using namespace std;

const vector<pair<int,int>> dirs = {{-2,1},{-2,-1},
				    {-1,2},{-1,-2}};

bool pos_ok (int i, int j, const vector<vector<int>>& M) {
  int n = M.size();
  int m = M[0].size();
  return i >= 0 and i < n and j >= 0 and j < m;
}

int monedes (const vector<vector<int>>& M, vector<vector<bool>>& sol, int i, int j, int monedes_actuals) {
  if (i == int(M.size())) return monedes_actuals;
  else {
    if (j == int(M[0].size())) return monedes(M,sol,i+1,0,monedes_actuals);
    bool possible = true;
    for (auto d : dirs) { // es podria tallar si possible ja es fals
      int n_i = i + d.first;
      int n_j = j + d.second;
      if (pos_ok(n_i,n_j,M) and sol[n_i][n_j]) possible = false; 
    }

    // No poso cavall
    sol[i][j] = false;
    int possib_1 = monedes(M,sol,i,j+1,monedes_actuals);

    // Poso cavall
    int possib_2 = 0;
    if (possible) {
      sol[i][j] = true;
      possib_2 = monedes(M,sol,i,j+1,monedes_actuals+M[i][j]);
    }

    return max(possib_1,possib_2);
  }
}

int monedes (const vector<vector<int>>& M) {
  vector<vector<bool>> sol(M.size(),vector<bool>(M[0].size()));
  int i = 0, j = 0;
  int monedes_actuals = 0;
  return monedes(M,sol,i,j,monedes_actuals);
}

int main ( ){
  int n, m;
  while (cin >> n >> m){
    vector<vector<int>> M(n,vector<int>(m));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
	cin >> M[i][j];
    cout << monedes(M) << endl;
  }
}
