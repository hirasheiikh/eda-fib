#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Col;
typedef vector<Col> Board;
typedef pair <int,int> Pos; //coordenades <fila,columna>
typedef vector<Pos> Positions;

Positions adjacents(Pos p){
    Positions pos; //exemple: ens trobem a la pos{2,2}
    pos.push_back({p.first-1, p.second}); //ADALT: {1,2}
    pos.push_back({p.first+1, p.second}); //ABAIX: {3,2}
    pos.push_back({p.first, p.second-1}); //ESQUERRA: {2,1}
    pos.push_back({p.first, p.second+1}); //DRETA: {2,3}
    return pos;
}

//comprovem si la posició a la que ens volem moure és correcta
bool pos_ok(Pos p, const Board& board){
    //Hem de comprovar que ens trobem dins dels límits del tauler i que la posició a la que ens movem no sigui una X
    if (0 <= p.first and p.first < board.size() 
        and 0 <= p.second and p.second < board[0].size()
        and board[p.first][p.second] != 'X') return true;
    else return false;
}

//Algorisme BFS (cerca en amplada)
bool BFS(Pos src, const Board& board){
    //matriu de visitats: per guardar les caselles visitades
    vector<vector<bool>> vis(board.size(),vector<bool>(board[0].size(),false));

    vis[src.first][src.second] = true; //marquem la posició origen com a visitat
    queue<Pos> q; 
    q.push(src); //guardem la posició inicial a la cua

    //Bucle prinicipal --> executem mentres quedin caselles pendents d'explorar
    while (not q.empty()){
        Pos p = q.front(); //agafem la primera posicio de la cua
        q.pop(); //l'eliminem

        //comprovem per si es tracta d'un tresor, si és així retornem ja TRUE
        if(board[p.first][p.second] == 't') return true;
        
        //en cas de que la casella en la qual ens trobem no sigui un tresor ja:
        Positions adjacent = adjacents(p); //mirem les posicions adjacents
        for (auto pos : adjacent){
            /*for (int i = 0; i < adjacent.size(); i++){
                    Pos pos = adjacent[i];*/
            if (pos_ok(pos,board) and not vis[pos.first][pos.second]){
                vis[pos.first][pos.second] = true;
                q.push(pos);
            }
        }
    }
    return false; //si no hi ha cap tresor retornem false
}


int main(){
    int n,m;
    cin >> n >> m;

    Board board(n,Col(m));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) cin >> board[i][j];
    }

    int r,c;
    cin >> r >> c;
    //Cridem al BFS i restem 1 a r i c perquè l'entreda comença per 1 però els vector de C++ comencen per 0
    if (BFS(Pos({r-1,c-1}),board)) cout << "yes" << endl;
    else cout << "no" << endl;
}