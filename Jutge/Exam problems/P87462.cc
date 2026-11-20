#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VCC;
typedef pair<int,int> Pos;

const vector<Pos> dir_pacman = {{0,1},{0,-1},{1,0},{-1,0}};
const vector<Pos> dir_fant = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

bool bfs(VCC& tauler, Pos& ini){
    if (tauler[ini.first][ini.second] == 'X') return false;
    queue<Pos> q;
    q.push(ini);
    tauler[ini.first][ini.second] = 'X';
    while (not q.empty()){
        Pos act = q.front();
        q.pop();
        Pos seg;
        for (int l = 0; l < 4; ++l){
            seg.first = act.first + dir_pacman[l].first;
            seg.second = act.second + dir_pacman[l].second;
            if (tauler[seg.first][seg.second] != 'X'){
                if (tauler[seg.first][seg.second] == 'B') return true;
                q.push(seg);
                tauler[seg.first][seg.second] = 'X';
            }
        }
    }
    return false;
}

int main(){
    int f,c;
    while (cin >> f >> c){
        VCC tauler(f,VC(c));
        Pos ini;
        queue<Pos> q_fant;
        for (int i = 0; i < f; ++i){
            for (int j = 0; j < c; ++j){
                cin >> tauler[i][j]; 
                if (tauler[i][j] == 'P') ini = {i,j};
                else if (tauler[i][j] == 'F') q_fant.push({i,j});
            }
        }
        while (not q_fant.empty()){
            Pos act = q_fant.front();
            q_fant.pop();
            for (int l = 0; l < 8; ++l){
                int x =  act.first + dir_fant[l].first;
                int y =  act.second + dir_fant[l].second;
                tauler[x][y] = 'X';
            }
        }
        if (bfs(tauler,ini)) cout << "si" << endl;
        else cout << "no" << endl;
    }
}
