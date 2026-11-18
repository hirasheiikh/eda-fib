#include <iostream>
#include <vector>
using namespace std;


typedef vector<int> Fila;
typedef vector<Fila> Matriu;
Matriu Identitat = {{1,0},{0,1}};
/* Matriu Id
1 0
0 1
*/

Matriu multiplica(const Matriu& A, const Matriu& B, int m){
    Matriu res(2,vector<int>(2)); //mida 2 i a cada posició podem un vector de mida 2 també. 
    res[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % m; //fila 0 d'A * columna 0 de B
    res[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % m; //fila 0 d'A * columna 1 de B
    res[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % m; //fila 1 d'A * columna 0 de B
    res[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % m; //fila 1 d'A * columna 1 de B
    return res;
}

/*alternativa amb bucles
// N és la mida de la matriu (ex: 2)
    for (int i = 0; i < N; i++) {       // Recorre fila d'A
        for (int j = 0; j < N; j++) {   // Recorre columna de B
        res[i][j] = 0;
            for (int k = 0; k < N; k++) { // Producte punt
            res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % m;
            }
        }
    }
*/

//Funció exponenciació modular
    //apliquem l'algorisme d'exponienciació modular, essent M^n mod m
        /*
            CAS BASE: n = 0 --> M^n = I (I == matriu identitat)
            CAS RECURSIU:
                -Si n parell --> (M^(n/2) * M^(n/2))
                -Si n senar --> (M * (M^(n/2)))
        */
Matriu potencia(const Matriu& M, int n, int m){

    //  Cas base: 
    if (n == 0) return Identitat;

    //Pas recursiu: Cas n parell -> calculem M^(n/2)
    Matriu aux = potencia(M, n/2, m);

    //Multipliquem M^(n/2)*M^(n/2)
    Matriu res = multiplica(aux,aux,m);

    //en cas que n sigui senar multipliquem per M 
    if (n%2) res = multiplica(res,M,m);

    return res;
}

int main(){
    Matriu M(2, Fila(2));
    int n,m;

    //llegim els valors de la matriu
    while(cin >> M[0][0] >> M[0][1] >> M[1][0] >> M[1][1]){
        int n,m;
        cin >> n >> m;

        Matriu res = potencia(M,n,m);
        cout << res[0][0] << ' ' << res[0][1] << endl;
        cout << res[1][0] << ' ' << res[1][1] << endl;
        cout << "----------" << endl;
    }
}