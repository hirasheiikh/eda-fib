#include <iostream>
#include <set>
using namespace std;

int main(){
    set<string> s;
    string paraula;
    auto med = s.end();
    while (cin >> paraula and paraula != "END"){
        s.insert(paraula);
        if (s.size() == 1) med = s.begin();
        if (s.size()%2){ //si el size es impar
            if (*med < paraula) ++med;
        }
        else if (*med > paraula) --med;
        cout << *med << endl;
    }
}