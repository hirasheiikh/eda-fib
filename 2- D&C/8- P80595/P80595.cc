#include <iostream>
#include <vector>
using namespace std;


//volem trobar el numero de parelles en posicion i i j desordenades entre elles (que si s'intercanvien passa a estar ordenat el segment) --> xi > xj
//per fer-ho de manera eficient fem servir l'algorisme MERGESORT ja que tenim la condició 1 <= i < j <= n i que xi > xj. Cada índex pertany a una meitat

int merge(vector<int>& v, int l, int m, int r){
    vector<int> M(r - l + 1); //vector auxiliar on guardem els elements ordenats
    int i = l, j = m+1, k = 0, count = 0;
    //i = índex inicial de la primera meitat
    //j = índex inicial de la segona meitat
    //k = índex inicial del vector auxiliar

    while(i <= m and j <= r){
        if (v[i] <= v[j]) M[k++] = v[i++]; //guardem el valor v[i] a M[k] i fem ++i i ++k
        else{
            M[k++] = v[j++];
            // AQUI ESTÀ LA CLAU:
            // Si agafem de la dreta, saltem per sobre de tots els que queden a l'esquerra
            count += m  + 1 - i; //hem de tenir en compte a quina i ens trobem 
        }
    }
    while (i <= m) M[k++] = v[i++];
    while (j <= r) M[k++] = v[j++];

    for (int k = 0; k < M.size(); ++k) v[l+k] = M[k];


    return count;
}


int mergeSort(vector<int>& v, int l, int r){
    int count = 0;
    if (l < r){
        int m =(l + r)/2;
        count = mergeSort(v,l,m);
        count += mergeSort(v,m+1,r);
        count += merge(v,l,m,r);
    }
    return count;
}

int main(){
    int n;
    while (cin >> n){
        vector<int> v(n);
        for (int i = 0; i < n; ++i){
            cin >> v[i];
        }
        cout << mergeSort(v,0,v.size()-1) << endl;
    }
}