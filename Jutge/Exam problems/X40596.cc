#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<bool> VB;


void print(VI&  sol){
    cout << '(';
    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i];
        if (i != sol.size() -1) cout << ',';
    }
    cout << ')' << endl;
}

void backtracking(const VI& nums, VI& sol, VB& vis, int n, int d, int i){
    if (i == n){
        print(sol);
        return;
    }
    for (int j = 0; j < n; ++j){
        if (not vis[j] and (sol.empty() or abs(sol[i-1] - nums[j]) <= d)){
            vis[j] = true;
            sol.push_back(nums[j]);
            backtracking(nums,sol,vis,n,d,i+1);
            sol.pop_back();
            vis[j] = false;
        }
    }
     
}


int main(){
    int n,d;
    cin >> n >> d;
    VI nums(n);
    for (int i = 0; i < n; ++i){
        nums[i] = i+1;
    }
    VI sol; //el contingut del vector va des d'1 a n
    VB vis(n);
    backtracking(nums,sol,vis,n,d,0);
    
}