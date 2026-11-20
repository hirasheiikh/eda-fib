#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Luka5Plus

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
  const vector<Dir> dir_viu = {Down, Right, Up, Left};
  const vector<Dir> dir_zombie = {Down, DR, Right, RU, Up, UL, Left, LD};
  const int infinit = 1000000000;

  struct Peticio {
    int id;
    Dir primer_pas;
    int valor;
    int dist;
    Pos objectiu;

    bool operator<(const Peticio& o) const {
      if (valor != o.valor) return valor > o.valor;
      return dist < o.dist;
    }
  };

  //BFS zombies (8 direccions). incloem les dead_units (preveu aparicions de zombies)
  vector<vector<int>> bfs_zombies() const {
    vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), infinit));
    queue<Pos> q;

    for (int z : zombies()) {
      Pos p = unit(z).pos;
      dist[p.i][p.j] = 0;
      q.push(p);
    }

    for (int pl = 0; pl < num_players(); ++pl) {
      for (int id : dead_units(pl)) {
        Unit u = unit(id);
        if (u.rounds_for_zombie >= 0 and u.rounds_for_zombie <= 2) {
          int retard = 1 + u.rounds_for_zombie;
          if (dist[u.pos.i][u.pos.j] > retard) {
            dist[u.pos.i][u.pos.j] = retard;
            q.push(u.pos);
          }
        }
      }
    }

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();
      for (Dir d : dir_zombie) {
        Pos np = p + d;
        if (pos_ok(np) and cell(np).type == Street) {
          if (dist[np.i][np.j] == infinit) {
            dist[np.i][np.j] = dist[p.i][p.j] + 1;
            q.push(np);
          }
        }
      }
    }
    return dist;
  }

  //BFS de les meves alive_units. (cel·la val més com més lluny meu estigui)
  vector<vector<int>> bfs_meves() const { 
    vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), infinit));
    queue<Pos> q;
    for (int id : alive_units(me())) {
      Pos p = unit(id).pos;
      dist[p.i][p.j] = 0;
      q.push(p);
    }
    while (!q.empty()) {
      Pos p = q.front();
      q.pop();
      for (Dir d : dir_viu) {
        Pos np = p + d;
        if (pos_ok(np) and cell(np).type == Street and dist[np.i][np.j] == infinit) {
          dist[np.i][np.j] = dist[p.i][p.j] + 1;
          q.push(np);
        }
      }
    }
    return dist;
  }

  //BFS unitats enemigues
  vector<vector<int>> bfs_enemics() const {
    vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), infinit));
    queue<Pos> q;

    for (int pl = 0; pl < num_players(); ++pl) {
      if (pl == me()) continue;
      for (int id : alive_units(pl)) {
        Pos p = unit(id).pos;
        dist[p.i][p.j] = 0;
        q.push(p);
      }
    }

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();
      for (Dir d : dir_viu) {
        Pos np = p + d;
        if (pos_ok(np) and cell(np).type == Street and dist[np.i][np.j] == infinit) {
          dist[np.i][np.j] = dist[p.i][p.j] + 1;
          q.push(np);
        }
      }
    }
    return dist;
  }

  //decidim si es millor atacar una unitat enemiga a distancia d
  int valor_atac(int my_str, int enemy_str, int dist, bool forced) const {
    int prob = (my_str == 0 and enemy_str == 0) ? 65 : (my_str + enemy_str <= 0 ? 30 : 30 + (70 * my_str) / (my_str + enemy_str));
    int valor = (50 * (2 * prob - 100)) / 100 + 146;             
    if (forced) valor += 35; //forces -> unitat ja en procés de zombi
    if (prob >= 65) valor += 25;               
    valor -= 8 * dist;
    if (prob < 45 and not forced) return -infinit;
    return valor;
  }

  vector<Peticio> buscar_objectius(int id, const vector<vector<int>>& dist_z, const vector<vector<int>>& dist_e, const vector<vector<int>>& dist_m, int factor_menjar) const {
    vector<Peticio> peticions;
    Unit u = unit(id);
    int my_str = strength(me());
    bool weak_state = (my_str < 22);
    bool urgent_zombie = (u.rounds_for_zombie != -1 and u.rounds_for_zombie <= 2);

    vector<vector<int>> vis(board_rows(), vector<int>(board_cols(), -1));
    queue<pair<Pos, Dir>> q;
    vis[u.pos.i][u.pos.j] = 0;

    for (Dir d : dir_viu) {
      Pos np = u.pos + d;
      if (!pos_ok(np) or cell(np).type == Waste) continue;
      Cell c = cell(np);

      if (c.id != -1) {
        Unit v = unit(c.id);
        if (v.type == Zombie or (v.type == Alive and v.player != me())) {
          int punts = -infinit;
          if (v.type == Zombie) punts = 240;
          else {
            int e = strength(v.player);
            bool forced = (u.rounds_for_zombie != -1);
            punts = valor_atac(my_str, e, 1, forced);
            if (v.rounds_for_zombie != -1 and my_str + 4 >= e) punts = max(punts, 165);
          }
          if (weak_state and v.type == Alive) punts -= 60;
          
          if (dist_z[u.pos.i][u.pos.j] <= 1) punts -= 230 / 3;
          else if (dist_z[u.pos.i][u.pos.j] == 2) punts -= 85 / 3;
          else if (dist_z[u.pos.i][u.pos.j] == 3) punts -= 25 / 3;
          
          if (punts > 0) peticions.push_back({id, d, punts, 1, np});
        }
        continue;
      }

      vis[np.i][np.j] = 1;
      q.push({np, d});
    }

    const int profunditat_max = 22;
    while (!q.empty()) {
      pair<Pos, Dir> actual = q.front();
      q.pop();
      Pos p = actual.first;
      Dir d0 = actual.second;
      int dist = vis[p.i][p.j];
      if (dist > profunditat_max) continue;

      Cell c = cell(p);
      int punts = 0;

      if (c.food) {
        int valor_base_m = (round() <= 70) ? 235 : 175;
        punts += (valor_base_m * factor_menjar) / 100;
        if (weak_state) punts += 85;
        if (urgent_zombie) punts -= 40;
      }
      
      if (c.owner != me()) {
        punts += 30 + (num_rounds() - round()) / 3;
        if (c.owner != -1) punts += 20;
      }
      
      for (int pl = 0; pl < num_players(); ++pl) {
        for (int did : dead_units(pl)) {
          Unit du = unit(did);
          if (du.rounds_for_zombie >= 0) {
            int ddist = abs(du.pos.i - p.i) + abs(du.pos.j - p.j);
            if (du.rounds_for_zombie <= 1 and ddist == 1) punts += 45;
            else if (du.rounds_for_zombie <= 2 and ddist == 1) punts += 22;
            else if (du.rounds_for_zombie <= 1 and ddist == 2) punts += 12;
          }
        }
      }
      
      punts -= 5 * dist;
      
      if (dist_z[p.i][p.j] <= 1) punts -= 230;
      else if (dist_z[p.i][p.j] == 2) punts -= 95;
      else if (dist_z[p.i][p.j] == 3) punts -= 32;
      
      for (Dir dir : dir_viu) {
        Pos np = p + dir;
        if (!pos_ok(np)) continue;
        int uid = cell(np).id;
        if (uid != -1) {
          Unit v = unit(uid);
          if (v.type == Alive and v.player != me()) {
            int e = strength(v.player);
            if (e >= my_str + 4) punts -= 75;
            else if (e + 6 >= my_str) punts -= 30;
          }
        }
      }

      if (dist <= 6) { //perdo si una unitat mes ja és més aprop
        int diff = dist - dist_m[p.i][p.j];
        if (diff > 0) punts -= min(diff * 2, 12);
      }

      if (c.food) {
        if (dist_e[p.i][p.j] < dist) punts -= 70;
        else if (dist_e[p.i][p.j] == dist) punts -= 35;
        else if (dist_e[p.i][p.j] == dist + 1) punts -= 15;
      }
      else if (c.owner != me()) {
        if (dist_e[p.i][p.j] < dist) punts -= 35;
        else if (dist_e[p.i][p.j] == dist) punts -= 17;
        else if (dist_e[p.i][p.j] == dist + 1) punts -= 7;
      }

      if (punts > 25) peticions.push_back({id, d0, punts, dist, p});

      for (Dir ds : dir_viu) {
        Pos np = p + ds;
        if (!pos_ok(np) or vis[np.i][np.j] != -1 or cell(np).type == Waste) continue;
        Cell nc = cell(np);

        if (nc.id != -1) {
          Unit v = unit(nc.id);
          if (v.type == Alive and v.player != me()) {
            int e = strength(v.player);
            bool forced = (u.rounds_for_zombie != -1);
            int patac = valor_atac(my_str, e, dist + 1, forced);
            if (weak_state) patac -= 50;
            if (patac > 30) peticions.push_back({id, d0, patac, dist + 1, np});
          }
          else if (v.type == Zombie) {
            int pz = 220 - 9 * (dist + 1);
            if (dist_e[np.i][np.j] < dist + 1) pz -= 35;
            else if (dist_e[np.i][np.j] == dist + 1) pz -= 17;
            else if (dist_e[np.i][np.j] == dist + 2) pz -= 7;
            
            if (pz > 30) peticions.push_back({id, d0, pz, dist + 1, np});
          }
          continue;
        }

        vis[np.i][np.j] = dist + 1;
        q.push({np, d0});
      }
    }

    return peticions;
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if (status(me()) >= 0.96) return;

    vector<vector<int>> dist_z = bfs_zombies();
    vector<vector<int>> dist_e = bfs_enemics();
    vector<vector<int>> dist_m = bfs_meves();
    vector<int> vius = alive_units(me());

    int my_str = strength(me());
    int max_forca_e = 0;
    for (int pl = 0; pl < num_players(); ++pl) {
      if (pl != me()) max_forca_e = max(max_forca_e, strength(pl));
    }
    
    int factor_menjar = 100;
    //mirar si el mejar té urgència o no: si som més forts -> millor pintar territori o caçar zombies
    if (my_str > max_forca_e + 30) factor_menjar = 35;
    else if (my_str > max_forca_e + 15) factor_menjar = 60;
    else if (my_str > max_forca_e + 5)  factor_menjar = 85;
    else if (my_str + 10 < max_forca_e) factor_menjar = 130;

    sort(vius.begin(), vius.end(), [&](int a, int b) {
      int ra = unit(a).rounds_for_zombie;
      int rb = unit(b).rounds_for_zombie;
      if (ra == -1) ra = infinit;
      if (rb == -1) rb = infinit;
      if (ra != rb) return ra < rb;
      return a < b;
    });

    set<int> moguts;
    set<Pos> objectius_atac;

    //1- atacs immediats
    for (int id : vius) {
      Dir millor_direccio = Up;
      Unit u = unit(id);
      int millor_valor = -infinit;
      bool trobat = false;

      for (Dir d : dir_viu) {
        Pos np = u.pos + d;
        if (!pos_ok(np)) continue;
        Cell c = cell(np);
        if (c.type == Waste or c.id == -1) continue;
        Unit v = unit(c.id);

        int val = -infinit;
        if (v.type == Zombie) {
          val = 280;
          if (dist_z[u.pos.i][u.pos.j] <= 1) val -= 230 / 3;
          else if (dist_z[u.pos.i][u.pos.j] == 2) val -= 85 / 3;
          else if (dist_z[u.pos.i][u.pos.j] == 3) val -= 25 / 3;
        }
        else if (v.type == Alive and v.player != me()) {
          int e = strength(v.player);
          bool forced = (u.rounds_for_zombie != -1);
          val = valor_atac(my_str, e, 1, forced);
          if (v.rounds_for_zombie != -1 and my_str + 4 >= e) val = max(val, 175);
        }

        if (val > millor_valor) {
          millor_valor = val;
          millor_direccio = d;
          trobat = true;
        }
      }
      
      if (trobat and millor_valor > 0) {
        Pos obj = unit(id).pos + millor_direccio;
        Cell c = cell(obj);
        if (c.id != -1 and unit(c.id).type == Zombie) {
          if (objectius_atac.count(obj)) continue;
        }
        move(id, millor_direccio);
        moguts.insert(id);
        objectius_atac.insert(obj);
      }
    }

    //2- llista d etotes les peticions. per cada unitat lliure
    vector<Peticio> totes_peticions;
    for (int id : vius) {
      if (moguts.count(id)) continue;
      vector<Peticio> p = buscar_objectius(id, dist_z, dist_e, dist_m, factor_menjar);
      totes_peticions.insert(totes_peticions.end(), p.begin(), p.end());
    }

    sort(totes_peticions.begin(), totes_peticions.end());
    set<Pos> caselles_ocupades;
    set<Pos> objectius_agafats = objectius_atac;

    for (const Peticio& r : totes_peticions) {
      if (moguts.count(r.id)) continue;
      Unit u = unit(r.id);
      Pos np = u.pos + r.primer_pas;
      if (!pos_ok(np) or cell(np).type == Waste) continue;
      Cell c = cell(np);

      bool es_atac = false;
      bool is_zombi = false;
      if (c.id != -1) {
        Unit v = unit(c.id);
        if (v.type == Zombie) { es_atac = true; is_zombi = true; }
        else if (v.type == Alive and v.player != me()) es_atac = true;
        else continue;
      }

      if (es_atac) {
        if (is_zombi and objectius_agafats.count(r.objectiu)) continue;
        if (!is_zombi and objectius_agafats.count(r.objectiu)) continue;
        move(r.id, r.primer_pas);
        moguts.insert(r.id);
        objectius_agafats.insert(r.objectiu);
      }
      else {
        if (objectius_agafats.count(r.objectiu) or caselles_ocupades.count(np)) continue;
        move(r.id, r.primer_pas);
        moguts.insert(r.id);
        caselles_ocupades.insert(np);
        objectius_agafats.insert(r.objectiu);
      }
    }

    //3- si una no s'ha mogut encara mirem de moure-la. quedar-se qiet sempre dolent
    for (int id : vius) {
      if (moguts.count(id)) continue;
      Unit u = unit(id);
      int max_sc = -infinit;
      Dir best_d = Up;
      bool ok = false;
      
      for (Dir d : dir_viu) {
        Pos np = u.pos + d;
        if (!pos_ok(np) or cell(np).type == Waste or caselles_ocupades.count(np) or cell(np).id != -1) continue;
        Cell c = cell(np);
        int sc = 0;
        if (c.food) sc += (130 * factor_menjar) / 100;  
        
        if (c.owner != me()) {
          sc += 30 + (num_rounds() - round()) / 3;
          if (c.owner != -1) sc += 20;
        }
        
        if (dist_z[np.i][np.j] <= 1) sc -= 230;
        else if (dist_z[np.i][np.j] == 2) sc -= 95;
        else if (dist_z[np.i][np.j] == 3) sc -= 32;
        
        for (Dir dir : dir_viu) {
          Pos nnp = np + dir;
          if (!pos_ok(nnp)) continue;
          int uid = cell(nnp).id;
          if (uid != -1) {
            Unit v = unit(uid);
            if (v.type == Alive and v.player != me()) {
              int e = strength(v.player);
              if (e >= my_str + 4) sc -= 75;
              else if (e + 6 >= my_str) sc -= 30;
            }
          }
        }
        
        Pos np2 = np + d;
        if (pos_ok(np2) and cell(np2).type == Street and dist_m[np2.i][np2.j] < infinit) {
          sc += min(dist_m[np2.i][np2.j], 6);
        }
        
        if (sc > max_sc) {
          max_sc = sc;
          best_d = d;
          ok = true;
        }
      }
      //acceptem moviments amb puntuacio negativa(millor moure's)
      if (ok) {
        move(id, best_d);
        caselles_ocupades.insert(u.pos + best_d);
      }
    }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);