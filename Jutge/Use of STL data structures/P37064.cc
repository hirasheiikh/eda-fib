#include <iostream>
#include <set>
using namespace std;

int main(){
    string paraula;
    set<string> s;
    auto it = s.end();
    while (cin >> paraula and paraula != "END"){
        s.insert(paraula);
        int n = s.size(); 
        if (n == 1) it = s.begin(); 
        if (n%2 != 0){ //si es impar
            if (*it < paraula) ++it; 
        }
        else if (*it > paraula) --it;
        cout << *it << endl;

    }
}