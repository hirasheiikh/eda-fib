#include <iostream>
#include <vector>
using namespace std;


typedef vector<int> Fila;
typedef vector<Fila> Matriu;
Matriu Identitat = {{1,0},{0,1}};


Matriu multiplica(Matriu& A, Matriu& B, int m){
    Matriu res(2,vector<int>(2));
    res[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0])%m;
    res[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1])%m;
    res[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0])%m;
    res[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1])%m;

    return res;
}



Matriu potencia(Matriu& M, int n, int m){
    if (n == 0) return Identitat;
    Matriu aux = potencia(M,n/2,m); //dividir la matriu en submatrius perque sigui més fàcil
    Matriu res = multiplica(aux,aux,m);

    if (n%2) res = multiplica(res,M,m);
    return res;
}



int main(){
    Matriu M(2,Fila(2));
    
    while (cin >> M[0][0] >> M[0][1] >> M[1][0] >> M[1][1]){
        int n,m;
        cin >> n >> m;

        Matriu res = potencia(M,n,m);
        cout << res[0][0] << ' ' << res[0][1] << endl;
        cout << res[1][0] << ' ' << res[1][1] << endl;
        cout << string(10,'-') << endl;
    }
}