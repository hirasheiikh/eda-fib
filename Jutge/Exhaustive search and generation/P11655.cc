#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> VI;


void escriu(const VI& x, const VI& vis){
    cout << '{';
    bool primer = true;
    for (int i = 0; i < x.size(); ++i){
        if (vis[i] == 1){
            if (!primer) cout << ',';
            cout << x[i];
            primer = false;
        }
    }
    cout << '}' << endl;

}


void particions(const VI& x, VI& vis,int s, int n,int sum_total, VI& sum_acumulada,int i){
    if (sum_total > s) return; //poda, ens hem passat de l'objectiu
    if (sum_total + sum_acumulada[i] < s) return; //si sumant tot el que queda no arribem a s descartem seguir.
    if (i == n){ //arribem al final de la llista x
        if (sum_total == s) escriu(x,vis); //tenim la suma exacta. imprimim només els que tenen vis = 1.
        return;
    }
    //agafem x[i]
    vis[i] = true; 
    //fem la crida recursiva sumant a sum_total x[i]
    particions(x,vis,s,n,sum_total + x[i],sum_acumulada,i+1);
    //no agafem x[i]
    vis[i] = false;
    //no sumem res, sum_total es queda igual
    particions(x,vis,s,n,sum_total,sum_acumulada,i+1);
}




int main(){
    int s,n;
    cin >> s >> n;
    VI x(n);
    for (int i = 0; i < n; ++i){
        cin >> x[i];
    }
    VI sum_acumulada(n+1,0);
    for (int i = n - 1; i >= 0; --i){
        sum_acumulada[i] = sum_acumulada[i+1] + x[i]; 
    }
    VI vis(n,0);
    particions(x,vis,s,n,0,sum_acumulada,0);

}