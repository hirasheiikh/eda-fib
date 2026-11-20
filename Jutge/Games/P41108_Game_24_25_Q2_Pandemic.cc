#include "Player.hh"
#include <functional>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Player_Pandemic


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
  static Dir idx2dir(int idx) {
    switch (idx) {
      case 0: return BOTTOM;
      case 1: return RIGHT;
      case 2: return TOP;
      default: return LEFT; // idx==3
    }
  }

  pair<Dir,int> bfs(Pos src, int goal_type, const vector<char>& own_city, const vector<char>& own_path) {
    int R = rows();
    int C = cols();
    static vector<vector<int> > dist;
    static vector<vector<Dir> > first;
    if ((int)dist.size() != R) {
      dist.assign(R, vector<int>(C, INT_MAX));
      first.assign(R, vector<Dir>(C, NONE));
    }
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        dist[i][j] = INT_MAX;
        first[i][j] = NONE;
      }
    }

    queue<Pos> q;
    dist[src.i][src.j] = 0;
    q.push(src);

    while (!q.empty()) {
      Pos p = q.front();
      q.pop();

      if (!(p == src)) {
        const Cell& cc = cell(p);
        bool ok = false;
        if (goal_type == 0) {
          ok = cc.mask;
        }
        else if (goal_type == 1) {
          if (cc.type == CITY && !own_city[cc.city_id]) ok = true;
        }
        else if (goal_type == 2) {
          if (cc.type == PATH && !own_path[cc.path_id]) ok = true;
        }
        if (ok) return make_pair(first[p.i][p.j], dist[p.i][p.j]);
      }

      for (int k = 0; k < 4; ++k) {
        Dir d = idx2dir(k);
        Pos np = p + d;
        if (pos_ok(np)) {
          const Cell& nc = cell(np);
          if (nc.type != WALL && dist[np.i][np.j] == INT_MAX) {
            dist[np.i][np.j] = dist[p.i][p.j] + 1;
            if (p == src) first[np.i][np.j] = d;
            else first[np.i][np.j] = first[p.i][p.j];
            q.push(np);
          }
        }
      }
    }
    return make_pair(NONE, INT_MAX);
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    int my_id = me();
    int NC = nb_cities();
    vector<char> own_city(NC, 0);
    for (int cid = 0; cid < NC; ++cid) {
      if (city_owner(cid) == my_id) own_city[cid] = 1;
    }

    int NP = nb_paths();
    vector<char> own_path(NP, 0);
    for (int pid = 0; pid < NP; ++pid) if (path_owner(pid) == my_id) own_path[pid] = 1;

    vector<int> my = my_units(my_id);

    for (size_t uidx = 0; uidx < my.size(); ++uidx) {
      int uid = my[uidx];
      Unit u = unit(uid);
      Pos  p = u.pos;

      bool moved_flag = false;

      for (int k = 0; k < 4 && !moved_flag; ++k) {
        Dir d = idx2dir(k);
        Pos q = p + d;
        if (pos_ok(q)) {
          const Cell& c = cell(q);
          if (c.unit_id != -1) {
            Unit v = unit(c.unit_id);
            if (v.player != my_id) {
              move(uid, d);
              moved_flag = true;
            }
          }
        }
      }

      if (!moved_flag) {
        pair<Dir,int> res = bfs(p, 1, own_city, own_path);
        if (res.first != NONE) {
          move(uid, res.first);
          moved_flag = true;
        }
      }

      if (!moved_flag) {
        pair<Dir,int> res = bfs(p, 2, own_city, own_path);
        if (res.first != NONE) {
          move(uid, res.first);
          moved_flag = true;
        }
      }

      if (!moved_flag) {
        vector<int> perm = random_permutation(4);
        size_t idx = 0;
        while (idx < 4 && !moved_flag) {
          Dir d = idx2dir(perm[idx]);
          Pos q = p + d;
          if (pos_ok(q)) {
            const Cell& c = cell(q);
            if (c.type != WALL && c.unit_id == -1) {
              move(uid, d);
              moved_flag = true;
            }
          }
          ++idx;
        }
        if (!moved_flag) {
          move(uid, NONE);
        }
      }
    }
  }
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
