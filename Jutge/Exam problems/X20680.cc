#include <iostream>
#include <vector>
using namespace std;



void bt(string& sol, int n, int c, int i, int count_x, int count_y, int count_z){
    if (i == n) cout << sol << endl;
    else{
        if (count_x < c){
            sol[i] = 'x';
            bt(sol,n,c,i+1,count_x+1,0,0);
        }
        if (count_y < c){
            sol[i] = 'y';
            bt(sol,n,c,i+1,0,count_y+1,0);
        }
        if (count_z < c){
            sol[i] = 'z';
            bt(sol,n,c,i+1,0,0,count_z+1);
        }

    }
}

int main(){
    int n,c;
    while (cin >> n >> c){
        string str(n,'x');
        bt(str,n,c,0,0,0,0);
        cout << string(20,'-') << endl;
    }
}