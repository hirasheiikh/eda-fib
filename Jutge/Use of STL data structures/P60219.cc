#include <iostream>
#include <set>
using namespace std;


struct cmp{
    //retorna true si a va abans que b i false si b va abans que a. 
    bool operator()(const string& a, const string& b) const{
        if (a.length() != b.length()) return a.length() < b.length(); //si les mides son dif retornem el mes peque primer
        return a < b;  //si les mides son iguals retornem el que sigui més petit lexicogràficament parlant
    }
};

int main(){
    int game = 1;
    string s;

    while (s != "QUIT"){
        set<string> HAS;
        set<string,cmp> HAD;
        
        while (cin >> s and s != "END" and s != "QUIT"){
            auto it = HAS.find(s);
            
            if (it == HAS.end()){ //no està la paraula
                HAS.insert(s);
                if (HAD.find(s) != HAD.end()) HAD.erase(s); //nomes poden haver-hi paraules que ja no hi son a HAS
            }
            else{ //la paraula si que està
                HAS.erase(s);
                HAD.insert(s);
            }
        } 
        if (game > 1) cout << endl;
        cout << "GAME #" << game << endl << "HAS:" << endl;
        for (auto it = HAS.begin(); it != HAS.end(); ++it) cout << (*it) << endl;

        cout << endl << "HAD:" << endl;
        for (auto it = HAD.begin(); it != HAD.end(); ++it) cout << (*it) << endl;

        ++game;
    }
}