#include <iostream>
#include <set>
using namespace std;

struct classcomp{
    //retorna true si a va abans que b i false va abans que a 
    bool operator()(const string& a, const string& b) const{
        if (a.length() != b.length()) return a.length() < b.length(); //en aquest cas retornem en ordre alfabetogràfic
        return a < b; //en aquest cas tornem segons el size de la paraula;
    }
};

int main(){
    int game = 1; //comptador de games;
    string s; //recordem que les paraules les anem rebent una a una

    while (s != "QUIT"){
        set<string> HAS;
        set<string,classcomp> HAD; //estem indicant amb el struct com volem que s'ordeni el set
        while(cin >> s and s != "END" and s != "QUIT"){
            auto it = HAS.find(s);
            if (it == HAS.end()){ //si la paraula no existeix prèviament.
                HAS.insert(s);
                if(HAD.find(s) != HAD.end()) HAD.erase(s); // important tenir en compte que es pot fer així.
            }
            else{ //en cas que la paraula ja existeixi d'abans.
                HAS.erase(s);
                HAD.insert(s); //no hem de comprovar que ja hi sigui perquè només afegim al set HAS quan ens assegurem que no hi és a HAS
            }
        }
        if (game > 1) cout << endl; //separador entre GAMES.
        
        cout << "GAME #" << game << endl << "HAS:" << endl;
        for (auto it = HAS.begin(); it != HAS.end(); ++it) cout << *it << endl;

        cout << endl << "HAD:" << endl;
        for (auto it = HAD.begin(); it != HAD.end(); ++it) cout << *it << endl;

        ++game;

    }

}