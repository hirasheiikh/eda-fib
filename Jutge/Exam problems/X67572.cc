#include <iostream>
#include <vector>
#include <string> 
using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;


void print(const VS& sol){
    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i];
    }
    cout << endl;
}


void backtracking(VS& sol, VS& paraules, VI& vis, int n, int i){
    if (i == n){
        print(sol);
        return;
    }
    for (int j = 0; j < n; ++j){
        if (not vis[j]){
            if (sol.empty() or (sol[i-1][sol[i-1].size()-1] != paraules[j][0])){
                sol.push_back(paraules[j]);
                vis[j] = true;
                backtracking(sol,paraules,vis,n,i+1);
                sol.pop_back();
                vis[j] = false;                                                                                                                            
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    VS paraules(n);
    for (int i = 0; i < n; ++i){
        cin >> paraules[i];
    }
    VS sol;
    VI vis(n);
    backtracking(sol,paraules,vis,n,0);
    
}


