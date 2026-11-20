#include <iostream>
#include <cmath>
using namespace std;


/*si no fessim servir pow
 --------------------------------------
    double power(double a, int n) {
        if (n == 0) return 1;

        double x = power(a, n / 2);
        if (n % 2 == 0) return (x * x);
        else return (x * x * a);
    }
 ---------------------------------------
*/

int n_dies(double m, double f, double r, int esq, int dre){
    int res= dre; //per defcte el valor serà el màxim númrto de dies
    while (esq <= dre){
        int mid = (dre+esq)/2;
        double cost_oak = m + f *mid;
        double cost_banc = m*pow(1.0+r,mid);
        if (cost_oak >= cost_banc) esq = mid + 1; //oak és més car o igual que el banc, volem comprovar si a la llarga el banc surt més a compte.
        //necessitem més dies per a que el banc es dispari
        else{
        //en aquest cas ja de primeres el cost del banc és menor, volem comprovar que no hi hagi un valor més petit de dies per al qual el cost
        //del banc ja sigui menor que el d'oak
            res = mid;
            dre = mid - 1;
        }
    }
    return esq; //si esq = dre vol dir que hi ha només 1 element (dia)
}


int main(){
    double m, f, r;
    while (cin >> m >> f >> r){
        r/=100.0; // passem el percentatge a decimal
        cout << n_dies(m, f, r, 1, 10000000) << endl;
    }
}