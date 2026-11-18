#include <iostream>
#include <vector>
#include <algorithm>    //pel sort
#include <sstream>
using namespace std;


int main(){
    string linia;
    while (getline(cin, linia)){
        vector<int> v;
        stringstream ss(linia);
        int num;
        while(ss >> num) v.push_back(num);

        if (v.empty()) cout << 0 << endl;
        else{ 
            sort(v.begin(),v.end());    //ordenem el vector
            int longitud = 1; //longitud comença a 1 perquè tenim en compte l'element anterior.
            int anterior = v[0];
            for (int i = 1; i < v.size(); ++i){ //comencem a 1 perquè i = 0 és "anterior"
                if (v[i] > anterior and (v[i]%2) != (anterior%2)){  //la paritat de l'anterior és diferent a la de l'actual
                    ++longitud; 
                    anterior = v[i];
                }
            }
            cout << longitud << endl;

        }
    }
}