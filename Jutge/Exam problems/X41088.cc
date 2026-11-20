#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;

void print(VI& sol){
    cout << '(';
    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i];
        if (i != sol.size()-1) cout << ',';
    }
    cout << ')' << endl;
}

void backtracking(VI& sol, VI& nums, VI& vis, int n, int i){
    if (i == n){
        print(sol);
        return;
    }
    for (int j = 0; j < n; ++j){
        if (not vis[j]){
            if (sol.size() < 2 or (sol[i-2] + nums[j] <= 2*sol[i-1])){
                vis[j] = true;
                sol.push_back(nums[j]);
                backtracking(sol,nums,vis,n,i+1);
                sol.pop_back();
                vis[j] = false;
            }
        }
    }
}


int main(){
    int n;
    cin >> n;
    VI sol;
    VI nums(n);
    for (int i = 0; i < n; ++i){
        nums[i] = i+1;
    }
    VI vis(n,0);
    backtracking(sol,nums,vis,n,0);
}