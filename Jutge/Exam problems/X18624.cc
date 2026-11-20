#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<char> VC;
//typedef map<char,int> MCI;

void print(VC& sol){
    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i];
    }
    cout << endl;
}

void backtracking(VC& lletres, VC& sol, int n, int m, int i){
    if (i == n){
        print(sol);
        return;
    }
    //cas tenim vocal, només consonants dps
    for (int j = 0; j < m; ++j){
        if (sol.empty() or (sol[i-1] != 'a' and sol[i-1] != 'e' and sol[i-1] != 'i' and sol[i-1] != 'o' and sol[i-1] != 'u')){
            sol.push_back(lletres[j]);
            //++vis[lletres[j]];
            backtracking(lletres,sol,n,m,i+1);
            sol.pop_back();
            //--vis[lletres[j]];
        }
        else if (sol[i-1] == 'a' or sol[i-1] == 'e' or sol[i-1] == 'i' or sol[i-1] == 'o' or sol[i-1] == 'u'){
            if (lletres[j] != 'a' and lletres[j] != 'e' and lletres[j] != 'i' and lletres[j] != 'o' and lletres[j] != 'u'){
                sol.push_back(lletres[j]);
                //++vis[lletres[j]];
                backtracking(lletres,sol,n,m,i+1);
                sol.pop_back();
                //--vis[lletres[j]];
            }
        }
    }
}

int main(){
    int n,m;
    while (cin >> n >> m){
        VC lletres(m);
        for (int i = 0; i < m; ++i){
            cin >> lletres[i];
        } 
        sort(lletres.begin(),lletres.end());
        VC sol;
        //MCI vis;
        backtracking(lletres,sol,n,m,0);
        cout << string(10,'-') << endl;
    }
}