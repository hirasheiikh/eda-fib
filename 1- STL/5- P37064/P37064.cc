#include <iostream> 
#include <set>
using namespace std;

int main(){
    string paraula;
    set<string> s;
    int i = 0;
    while(cin >> paraula and paraula != "END"){
        s.insert(paraula); //adeu bye hola
        int n = s.size(); // 3
        int pos = (n+1)/2; // 3+1/2= 2 --> volem treure bye que està a la posició 1-> pos-1 
        auto it = s.begin(); // adeu. i = 0 
        while (i < pos - 1){ // i = 0 -> hola ++i --> bye = 1 = pos de bye.
            ++it;
            ++i;
        }
        cout << *it << endl;
        i = 0;
    }
}