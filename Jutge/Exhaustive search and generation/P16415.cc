#include <iostream>
#include <vector>

using namespace std;

typedef vector<bool> VB;

int reinas(int n, int i, VB& col, VB& d1, VB& d2){ //si las declaramos como flobales no hace falta pasarlo por parámetro
    if (i == n) return 1;
    else {
        int count = 0;
        for (int j = 0; j < n; ++j){
            if (not col[j] and not d1[i+j] and not d2[i-j+n-1]){
                col[j] = true;
                d1[i+j] = true;
                d2[i-j+n-1] = true;
                count += reinas(n, i + 1, col, d1, d2);
                col[j] = false;
                d1[i+j] = false;
                d2[i-j+n-1] = false;
            }
        }
        return count;
    }

}

int main(){
    int n;
    cin >> n;

    VB col(n,false);
    VB d1(2*n-1,false);
    VB d2(2*n-1,false);

    cout << reinas(n,0,col,d1,d2) << endl;
}