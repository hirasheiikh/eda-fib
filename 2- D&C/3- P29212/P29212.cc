#include <iostream>
using namespace std;


int expoMod(int n,int k,int m){
    if (k == 0) return 1; //n*0 = 1;
    if (n == 0) return 0; //0^k = 0;

    int res;
    //propietat 1: (a*b) mod m = [(a mod m) * (b mod m)] mod m;
    if (k%2 == 0){
        //propietat 2.1: si k és parell llavors: n^k mod m = [(n^(k/2))*(n^(k/2))] mod m;
        res = expoMod(n,k/2,m);
        res = (res*res)%m; //aquesta propietat ens serveix per no haver de calcular n^k, té un cost molt menor fer n*n k/2 vegades
                           // i després multiplicar res*res
    }
    else{
        //propietat 2.2: si k és senar llavors: n^k mod m = [(n^(k-1)*n)] mod m; (n = n^1);
            //apliquem propietat 1
        res = n%m;
        res = (res * expoMod(n,k-1,m)%m)%m;
    }
    //propietat 3: si hem de retornar el mòdul d'un numero res negatiu el valor absolut del qual és menor que m 
        // (res + m)%m
        /*És una eina de seguretat.
            Si el número és negatiu, el suma per fer-lo positiu.
            Si el número ja era positiu, el deixa igual (matemàticament equivalent).*/
    return (res + m) % m; 
}



int main(){
    int n, k, m;
    while (cin >> n >> k >> m){
        //per a què el codi sigui eficient hem de fer servir l'algorisme d'exponenciació ràpida.
        //aquest algorisme té un cost de O(log(n))

        //també hem d'aplicar les propietats dels mòduls que puguem, com la distributiva:
            /*  (a×b)(modm)=((a(modm))×(b(modm)))(modm) --> en el nostre cas com fem n*n k vegades ho podem aplicar */
        cout << expoMod(n,k,m) << endl;
        
    }
}