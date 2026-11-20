#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Player_HP

struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  const vector<Dir> dir_mag = {Down, Right, Up, Left};
  const vector<Dir> dir_fantasma = {Down, DR, Right, RU, Up, UL, Left, LD};

  bool esta_voldemort(Pos p){
    for (int i = -3; i < 4; ++i) {
      for (int j = -3; j < 4; ++j) {
        if (p + Pos(j,j) == pos_voldemort()) return true;
      }
    }
    return false; 
  }

  void mov_mag(const int& id){
    Pos pos = unit(id).pos;
    vector<vector<int>> vis(board_rows(),vector<int>(board_cols(),-1));
    queue<pair<Pos,Dir>> movements;
    vis[pos.i][pos.j] = 0;

    for (Dir d : dir_mag) { 
      /*for (int i = 0; i < dir_mag.size(); ++i) {
        Dir d = dir_mag[i];*/
      Pos new_pos = pos + d; // comprovar que no estic dins del rang del Voldemort
     
      if (pos_ok(new_pos) and (not esta_voldemort(new_pos)) and cell(new_pos).type != Wall and vis[new_pos.i][new_pos.j] == -1) {
        if (cell(new_pos).id == -1) {
          movements.push({new_pos, d});
          vis[new_pos.i][new_pos.j] = vis[pos.i][pos.j] + 1;
        }
        if (cell(new_pos).book) { //hay libro (el bool retorna true)
          //leo libro y se suman puntos o conquista (auto) 
          move(id,d);
          return;
        }
        else if (cell(new_pos).id != -1 and unit(cell(new_pos).id).player != me()) { // puntos
          if (magic_strength(me()) >= magic_strength(unit(cell(new_pos).id).player) and (not unit(cell(new_pos).id).is_in_conversion_process())) {
            move(id,d);
            return;
          }
          else if (unit(cell(new_pos).id).type == Ghost and unit(cell(new_pos).id).rounds_pending == 0) {
            move(id,d);
            return;
          }
        }
        else if (cell(new_pos).id != -1 and cell(new_pos).owner != me()){
            move(id,d);
            return;
        }
      }
    }

  while (not movements.empty()){
        Pos pos_siguiente = movements.front().first;
        Dir dir_siguiente = movements.front().second;
        movements.pop();

        for (Dir d : dir_mag) { 
          /*for (int i = 0; i < dir_mag.size(); ++i) {
            Dir d = dir_mag[i];*/
          Pos new_pos = pos_siguiente + d;
         if (pos_ok(new_pos)and not esta_voldemort(new_pos) and cell(new_pos).type != Wall and vis[new_pos.i][new_pos.j] == -1 and not unit(id).is_in_conversion_process()) {
          if (cell(new_pos).book) { //hay libro (el bool retorna true)
            //leo libro y se suman puntos o conquista (auto) 
            move(id,dir_siguiente);
            return;
          }
          if (cell(new_pos).id == -1) {
            movements.push({new_pos, dir_siguiente});
            vis[new_pos.i][new_pos.j] = vis[pos_siguiente.i][pos_siguiente.j] + 1;
          }
          else if (cell(new_pos).id != -1 and unit(cell(new_pos).id).player != me()) { // puntos
            if (magic_strength(me()) >= magic_strength(unit(cell(new_pos).id).player) and (not unit(cell(new_pos).id).is_in_conversion_process())) {
              move(id,d);
              return;
            }
            else if (unit(cell(new_pos).id).type == Ghost and unit(cell(new_pos).id).rounds_pending == 0) {
              move(id,d);
              return;
            }
          }
          else if (cell(new_pos).id != -1 and cell(new_pos).owner != me()){
            move(id,d);
            return;
          }
        }
      }
    }
  }

  void mov_fantasma(const int& id){
    Pos pos = unit(id).pos;
    vector<vector<int>> vis(board_rows(),vector<int>(board_cols(),-1));
    queue<pair<Pos,Dir>> movements;
    vis[pos.i][pos.j] = 1;


    for (Dir d : dir_fantasma) { 
      /*for (int i = 0; i < dir_mag.size(); ++i) {
        Dir d = dir_mag[i];*/
      Pos new_pos = pos + d; // comprovar que no estic dins del rang del Voldemort
     
      if (pos_ok(new_pos)and not esta_voldemort(new_pos) and cell(new_pos).type != Wall and vis[new_pos.i][new_pos.j] == -1) {
        if (cell(new_pos).id == -1) {
          movements.push({new_pos, d});
          vis[new_pos.i][new_pos.j] = 1;
        }
        if (cell(new_pos).book) { //hay libro (el bool retorna true)
          //leo libro y se suman puntos o conquista (auto) 
          move(id,d);
          return;
        }
      }
    }
    

    while (not movements.empty()){
        Pos pos_siguiente = movements.front().first;
        Dir dir_siguiente = movements.front().second;
        movements.pop();

        for (Dir d : dir_fantasma) { 
          /*for (int i = 0; i < dir_mag.size(); ++i) {
            Dir d = dir_mag[i];*/
          Pos new_pos = pos_siguiente + d;
         if (pos_ok(new_pos)and not esta_voldemort(new_pos) and cell(new_pos).type != Wall and vis[new_pos.i][new_pos.j] == -1) {
          if (cell(new_pos).id == -1) {
            movements.push({new_pos, dir_siguiente});
            vis[new_pos.i][new_pos.j] = 1;
          }
          if (cell(new_pos).book) { //hay libro (el bool retorna true)
            //leo libro y se suman puntos o conquista (auto) 
            move(id,dir_siguiente);
            return;
          }
        }
      }
    }
  }

  //encantament

vector<int> resultat_spell(const vector<int>& ingredients) {
    int sum = 0;
    for (int ingredient : ingredients) {
        sum += ingredient;
    }

    int total = sum / 5;

    int grup = 0;
    vector<int> resultat(15, -1);

    for (int i = 0; i < 15; ++i) {
      if (resultat[i] == -1){
        for (int j = i + 1; j < 15; ++j){
          if (resultat[i] == -1 and resultat[j] == -1){
            for (int k = j + 1; k < 15; ++k){
              if (resultat[i] == -1 and resultat[j] == -1 and resultat[k] == -1 and ingredients[i] + ingredients[j] + ingredients[k] == total){
                //if (grup < 5){
                  resultat[i] = grup;
                  resultat[j] = grup;
                  resultat[k] = grup;
                  ++grup;
                //}
              }
            }
          }
        }
      }
    }
  return resultat;
  }



  /**
   * Play method, invoked once per each round.
   */
  virtual void play() {
    vector<int> magos = wizards(me()); 
    for (int id : magos) {
       mov_mag(id);  
    }

    int fantasma_id = ghost(me());
    Unit fantasma = unit(fantasma_id); 
    bool sp = false;
    int rondes_falten_spell = fantasma.rounds_pending; 
    if (rondes_falten_spell == 0 and round() >= 50 and round() <= 150){ //només podem encantar apartir de la ronda 50
        vector<int> ingredients = spell_ingredients();
        vector<int> resultat = resultat_spell(ingredients);
        if (not ingredients.empty() and not resultat.empty()) {
            spell(fantasma_id, resultat); 
            sp = true;
        }
    }
    if (not sp) mov_fantasma(fantasma_id);
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);


