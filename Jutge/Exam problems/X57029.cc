#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<char> VC;
typedef vector<pair<int,int>> VII;
typedef pair<int,int> Pos;
//VII Dir{{0,1},{0,-1},{1,0},{-1,0}};
//si y = 0 no podem anar cap abaix. y ha de ser com a mínim 1

void write(VC& sol){
    //sort(sol.begin(),sol.end());
    for (int i = 0; i < sol.size(); ++i){
        cout << sol[i];
    }
    cout << endl;
}


void backtracking(VC& sol, int pos_ver, int i, int n){
    if (i == n){
        write(sol);
        return;
    }
    else{
        if (pos_ver > 0){
            sol.push_back('d');
            backtracking(sol,pos_ver-1,i+1,n);
            sol.pop_back();
        }
        sol.push_back('h');
        backtracking(sol,pos_ver,i+1,n);
        sol.pop_back();
        sol.push_back('u');
        backtracking(sol,pos_ver+1,i+1,n);
        sol.pop_back();
    }
}

int main(){
    int n;
    cin >> n;
    VC sol;
    int pos_ver = 0;
    backtracking(sol,pos_ver,0,n);

}