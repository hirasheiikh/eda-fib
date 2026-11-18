#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream> //MALAMENT! you'll be given words one by one!!! 
using namespace std;

bool cmp(const string &a, const string &b){
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b; 
}

int main(){
    string linia;
    string paraula;
    set<string> has;
    set<string> had;
    vector<string> had_BO;
    bool gameover = false;
    bool retirada = false;
    int i_game = 1;
    while (not retirada and getline(cin,linia)){ 
        stringstream ss(linia);
        while(not retirada and ss >> paraula){
            if (paraula == "END") gameover = true;
            else if (paraula == "QUIT") retirada = true;
            else{
                auto it = has.find(paraula); 
                if (it == has.end()){ //si no està al set l'afegim
                    has.insert(paraula);
                    auto it2 = had.find(paraula);
                    if (it2 != had.end()) had.erase(paraula);
                }
                else if (it != has.end()){ //si ja estava l'eliminem de has i l'afegim a had
                    has.erase(paraula);
                    had.insert(paraula);
                }
            }
    
            if (gameover or retirada){
                cout << "GAME #" << i_game << endl;
                //imprimim llistes
                cout << "HAS:" << endl;
                for (auto it = has.begin(); it != has.end(); ++it){
                    cout << *it << endl; 
                    //anem imprimint la llista HAS
                }
                cout << endl;
                
                cout << "HAD:" << endl;
                for (auto it = had.begin(); it != had.end(); ++it){
                    had_BO.push_back(*it);
                }
                sort(had_BO.begin(),had_BO.end(),cmp); // reordenem el vector HAD
                for (int i = 0; i < had_BO.size(); ++i){
                    cout << had_BO[i] << endl; 
                }
                cout << endl;
                ++i_game;
                 gameover = 0;
                 //buidar sets i vector
                 has.clear();
                 had.clear();
                 had_BO.clear();
            }
        }
            
    }

}