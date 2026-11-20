#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> VC;

void calcnext(int i, int j, int m, int& ni, int& nj) {
    ni = i;       // D'entrada, suposem que ens quedem a la mateixa fila
    nj = j + 1;   // I ens movem una columna a la dreta

    // Ara comprovem: ens hem passat del límit de columnes?
    // Recorda que si hi ha m columnes, els índexs van de 0 a m-1.
    // Si nj val m, vol dir que hem sortit de la fila.
    if (nj == m) {
        ++ni;     // Passem a la fila següent
        nj = 0;   // Tornem a la primera columna (índex 0)
    }
}


int calclol(VC& sol, int i, int j, int n, int m, int num){
    if (i == n) return num;
    int ni,nj;
    calcnext(i,j,m,ni,nj);

    sol[i][j]= 'O';
    int num_o = calclol(sol,ni,nj,n,m,num); //num de LOL's màxim  que es poden generar a la posicio i,j

    sol[i][j] = 'L';
    int count = 0;
    //comprovem si hi ha LOL horitzontal
    if (j >= 2 and sol[i][j-2] == 'L' and sol[i][j-1] == 'O') ++count;

    //LOL vertical
    if (i >= 2 and sol[i-1][j] == 'O' and sol[i-2][j] == 'L') ++count;

    //diagonal adalt-dreta
    if (i >= 2 and j + 2 < m and sol[i-1][j+1] == 'O' and sol[i-2][j+2] == 'L') ++count;

    //diagonal adalt-esquerra
    if (i >= 2 and j >= 2 and sol[i-1][j-1] == 'O' and sol[i-2][j-2] == 'L') ++count;

    int num_l = calclol(sol,ni,nj,n,m,num+count);
    return max(num_o,num_l);
}



int main(){
    int n, m;
    while (cin >> n >> m){
        VC vc(n,vector<char>(m));
        cout << calclol(vc,0,0,n,m,0) << endl;
    }
}