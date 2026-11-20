#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VCC;
typedef pair<int,int> Pos; 
const vector<Pos> Coordenades = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1}};
int n, r;

void imprimeix(VCC& tauler){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j) cout << tauler[i][j];
        cout << endl;
    }
    cout << string(10,'-') << endl;
}

bool puc_posar(VCC& tauler, int i, int j, int nkings){
    for (int l = 0; l < 8; ++l){
        int primer = i + Coordenades[l].first;
        int segon = j + Coordenades[l].second;
        if (primer >= 0 and primer < n and segon >= 0 and segon < n and tauler[primer][segon] == 'K') return false;
    }
    return true;
}

void backtracking(VCC& tauler, int i, int j, int nkings){
    if (nkings == r) imprimeix(tauler);
    else if (i == n) return;
    else if (j == n) backtracking(tauler,i+1,0,nkings);
    else{
        if (puc_posar(tauler,i,j,nkings)){
            tauler[i][j] = 'K';
            backtracking(tauler,i,j+1,nkings+1);
            tauler[i][j] = '.';
        } 
        backtracking(tauler,i,j+1,nkings);
    }
}


int main(){
    cin >> n >> r;
    VCC tauler(n,VC(n,'.'));
    backtracking(tauler,0,0,0);
}

