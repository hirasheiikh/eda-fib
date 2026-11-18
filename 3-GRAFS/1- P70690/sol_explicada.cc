#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definim àlies per fer el codi més llegible
typedef vector<char> Col;
typedef vector<Col> Board;       // Matriu de caràcters per al mapa
typedef pair<int, int> Pos;      // Coordenades (fila, columna)
typedef vector<Pos> Positions;   // Llista de posicions

// Retorna un vector amb les 4 posicions adjacents (moviments possibles)
Positions adjacents(Pos p) {
  Positions pos;
  pos.push_back({p.first+1, p.second});    // Abaix
  pos.push_back({p.first, p.second+1});    // Dreta
  pos.push_back({p.first-1, p.second});    // Dalt
  pos.push_back({p.first, p.second-1});    // Esquerra
  return pos;
}

// Comprova si una posició és vàlida per moure's-hi
bool pos_ok(Pos p, const Board& board) {
  // Comprovem que estigui dins dels límits del tauler
  // i que no sigui un obstacle ('X')
  if (0 <= p.first and p.first < board.size()
      and 0 <= p.second and p.second < board[0].size()
      and board[p.first][p.second] != 'X') return true;
  else return false;
}

// Algorisme de Cerca en Amplada (BFS) per trobar un tresor
bool BFS(Pos src, const Board& board) {
  // Matriu per recordar si ja hem visitat una casella (inicialment tot fals)
  vector<vector<bool> > vis(board.size(), vector<bool>(board[0].size(), false));
  
  vis[src.first][src.second] = true;  // Marquem l'origen com a visitat
  queue<Pos> q;
  q.push(src);    // Afegim la posició inicial a la cua

  // Bucle principal: mentre quedin caselles pendents d'explorar
  while (not q.empty()) {
    Pos p = q.front(); // Agafem la primera posició de la cua
    q.pop();           // L'eliminem de la cua

    // Si la casella actual és un tresor, hem acabat (èxit)
    if (board[p.first][p.second] == 't') return true;

    // Obtenim els veïns (Abaix, Dreta, Dalt, Esquerra)
    Positions adjacent = adjacents(p);
    for (auto pos : adjacent) {
      // Si la posició és vàlida (dins límits, no obstacle) i NO l'hem visitat encara
      if (pos_ok(pos, board) and not vis[pos.first][pos.second]) {
        vis[pos.first][pos.second] = true; // La marquem com a visitada
        q.push(pos);                       // L'afegim a la cua per explorar-la després
      }
    }
  }

  return false;    // Si buidem la cua sense trobar tresor, no hi ha camí
}

int main() {
  int n, m;
  cin >> n >> m;

  // Llegim el tauler
  Board board(n, Col(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> board[i][j];

  // Llegim la posició inicial
  int r, c;
  cin >> r >> c;

  // Cridem al BFS. Restem 1 a 'r' i 'c' perquè l'entrada comença per 1 
  // però els vectors de C++ comencen per 0.
  if (BFS(Pos({r-1, c-1}), board)) cout << "yes" << endl;
  else cout << "no" << endl;
}