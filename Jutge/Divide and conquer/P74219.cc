#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriu;

// hi ha una propietat matemàtica que relaciona Fibonacci amb les potències d'una matriu específica
Matriu Inicial = {{1,1},{1,0}};
Matriu Identitat = {{1,0},{0,1}};

Matriu multiplica(const Matriu& A, const Matriu& B, int m){
    int N = 2;
    Matriu res(2, Fila(2));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            res[i][j] = 0;
            for (int k = 0; k < N; ++k){
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % m;
            }
        }
    }
    return res;
}


Matriu potencia(const Matriu& M,int n, int m){
    if (n == 0) return Identitat; //que tenen 0 a la pos [0][0] i [1][1]
    Matriu aux = potencia(M,n/2,m);
    Matriu res = multiplica(aux,aux,m);
    if (n%2) res = multiplica(res,M,m);
    return res;


}

int main(){
    int n, m;
    while (cin >> n >> m){
        if (n == 0) cout << 0 << endl;
        else{
            Matriu res = potencia(Inicial,n,m);
            /* propietat:
                [1 1]^n      [F(n+1)  F(n)  ]
                [1 0]    =   [F(n)    F(n-1)]
            Per tant, F(n) està a la posició [0][1] (o [1][0])
            */
           cout << res[0][1] << endl; //res[1][0]
        }
    }
}