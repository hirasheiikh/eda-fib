#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Chiara4


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
  const vector<Dir> DIRECTIONS = {Down, Right, Up, Left};

  bool check_sum(int target, int b, int c) {
    return target == b + c;
  }

  bool find_combination(const vector<int>& nums, vector<bool>& mask, vector<int>& res, int current_count, int total_needed) {
    if (current_count == total_needed) return true;
    int pivot = -1;
    for (size_t i = 0; i < nums.size(); ++i) {
      if (!mask[i]) {
        pivot = i;
        break;
      }
    }
    if (pivot == -1) return false;
    mask[pivot] = true;
    for (size_t j = pivot + 1; j < nums.size(); ++j) {
      if (mask[j]) continue;
      for (size_t k = j + 1; k < nums.size(); ++k) {
        if (mask[k]) continue;
        bool match = check_sum(nums[pivot], nums[j], nums[k]) || 
                     check_sum(nums[j], nums[pivot], nums[k]) || 
                     check_sum(nums[k], nums[pivot], nums[j]);
        if (match) {
          mask[j] = true;
          mask[k] = true;
          res.push_back(pivot);
          res.push_back(j);
          res.push_back(k);
          if (find_combination(nums, mask, res, current_count + 1, total_needed)) return true;
          res.pop_back();
          res.pop_back();
          res.pop_back();
          mask[j] = false;
          mask[k] = false;
        }
      }
    }
    mask[pivot] = false;
    return false;
  }

  struct Request {
    int unit_id;
    Pos target_pos;
    int value;
    int distance;
    Dir first_move;
    
    bool operator<(const Request& other) const {
      if (value != other.value) return value > other.value;
      return distance < other.distance;
    }
  };

  bool is_enemy_soldier(int uid) {
    if (uid == -1) return false;
    Unit u = unit(uid);
    return u.player != me() && u.type == Soldier;
  }

  bool is_enemy_professor(int uid) {
    if (uid == -1) return false;
    Unit u = unit(uid);
    return u.player != me() && u.type == Professor;
  }
  
  vector<vector<int>> get_enemy_distances() {
    vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), 10000));
    queue<pair<Pos, int>> q;

    for (int pl = 0; pl < num_players(); ++pl) {
      if (pl == me()) continue;
      
      for (int id : soldiers(pl)) {
        Unit u = unit(id);
        if (u.is_alive()) {
          dist[u.pos.i][u.pos.j] = 0;
          q.push({u.pos, 0});
        }
      }
      
      int pid = professor(pl);
      if (pid != -1) {
        Unit u = unit(pid);
        if (u.is_alive()) {
          dist[u.pos.i][u.pos.j] = 0;
          q.push({u.pos, 0});
        }
      }
    }

    while (!q.empty()) {
      pair<Pos, int> curr = q.front();
      q.pop();
      Pos p = curr.first;
      int d = curr.second;

      if (d >= 60) continue;

      for (Dir dir : DIRECTIONS) {
        Pos next = p + dir;
        if (pos_ok(next) && cell(next).type != Wall && dist[next.i][next.j] > d + 1) {
          dist[next.i][next.j] = d + 1;
          q.push({next, d + 1});
        }
      }
    }
    return dist;
  }

  bool is_danger(Pos p) {
    for (int r = p.i - 1; r <= p.i + 1; ++r) {
      for (int c = p.j - 1; c <= p.j + 1; ++c) {
        Pos check(r, c);
        if (!pos_ok(check)) continue;
        int uid = cell(check).id;
        if (uid != -1) {
          Unit u = unit(uid);
          if (u.player != me() && u.type == Soldier && u.poison > 0) return true;
        }
      }
    }
    return false;
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    vector<int> my_soldiers = soldiers(me());
    int my_prof = professor(me());
    
    set<int> busy_units;
    set<pair<int,int>> taken_targets; 
    set<pair<int,int>> occupied_next_pos;
    
    vector<Request> requests;
    
    vector<vector<int>> enemy_dist = get_enemy_distances();

    for (int id : my_soldiers) {
       Unit u = unit(id);
       if (!u.is_alive()) continue;
       if (u.poison == 0 && available_poison(me()) > 0) {
          charge(id);
          busy_units.insert(id);
          occupied_next_pos.insert({u.pos.i, u.pos.j});
       }
    }
    
    if (my_prof != -1 && unit(my_prof).is_alive()) {
       Unit u = unit(my_prof);
       if (u.health < 60 && available_health(me()) > 0) {
          heal(my_prof);
          busy_units.insert(my_prof);
          occupied_next_pos.insert({u.pos.i, u.pos.j});
       }
    }

    for (int id : my_soldiers) {
       if (busy_units.count(id)) continue;
       Unit u = unit(id);
       if (!u.is_alive()) continue;
       
       if (u.poison > 0) {
          int best_uid = -1;
          int best_val = -1;
          Dir best_dir = Up; 

          for (Dir d : DIRECTIONS) {
             Pos adj = u.pos + d;
             if (pos_ok(adj)) {
                int uid = cell(adj).id;
                if (uid != -1 && unit(uid).player != me()) {
                   Unit target = unit(uid);
                   int val = (target.type == Professor) ? 1000 : 10; 
                   if (val > best_val) {
                      best_val = val;
                      best_uid = uid;
                      best_dir = d;
                   }
                }
             }
          }
          
          if (best_uid != -1) {
             move(id, best_dir);
             busy_units.insert(id);
             occupied_next_pos.insert({u.pos.i, u.pos.j});
          }
       }
    }

    for (int id : my_soldiers) {
      if (busy_units.count(id)) continue;
      Unit u = unit(id);
      if (!u.is_alive()) continue;

      queue<pair<Pos, Dir>> q;
      vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), -1));
      
      dist[u.pos.i][u.pos.j] = 0;
      
      vector<int> p = random_permutation(4);
      for (size_t k = 0; k < p.size(); ++k) {
        int idx = p[k];
        Dir d = DIRECTIONS[idx];
        Pos next = u.pos + d;
        if (pos_ok(next) && cell(next).type != Wall) {
           int uid = cell(next).id;
           if (uid != -1) {
              Unit target = unit(uid);
              if (target.player != me()) {
              }
              continue;
           }
           
           dist[next.i][next.j] = 1;
           q.push({next, d});
        }
      }

      int max_depth = 80; 
      
      while(!q.empty()) {
        pair<Pos, Dir> curr = q.front();
        q.pop();
        Pos p_curr = curr.first;
        Dir d0 = curr.second;
        int d = dist[p_curr.i][p_curr.j];
        
        if (d > max_depth) break;

        Cell c = cell(p_curr);
        int score = 0;

        if (c.money > 0) {
           score = max(score, c.money * 2500); 
        }
        if (c.poison_kit && u.poison < 20) {
           score = max(score, 5000);
        }
        
        if (score > 0) {
           if (d < enemy_dist[p_curr.i][p_curr.j]) {
               int value = score - (d * 80);
               if (value > 0) {
                 requests.push_back({id, p_curr, value, d, d0});
               }
           }
           else {
               int value = (score / 5) - (d * 80);
               if (value > 0) {
                   requests.push_back({id, p_curr, value, d, d0});
               }
           }
        }

        for (size_t k = 0; k < p.size(); ++k) {
           int idx = p[k];
           Dir dir = DIRECTIONS[idx];
           Pos next = p_curr + dir;
           if (pos_ok(next) && cell(next).type != Wall && dist[next.i][next.j] == -1) {
              if (cell(next).id != -1) continue;
              
              dist[next.i][next.j] = d + 1;
              q.push({next, d0});
           }
        }
      }
    }

    if (my_prof != -1 && unit(my_prof).is_alive()) {
       Unit u = unit(my_prof);
       
       bool opened = false;
       for (Dir d : DIRECTIONS) {
         Pos adj = u.pos + d;
         if (pos_ok(adj) && cell(adj).box != -1) {
            vector<int> hints = safety_box_hints(cell(adj).box);
            vector<bool> mask(hints.size(), false);
            vector<int> solution;
            if (find_combination(hints, mask, solution, 0, hints.size()/3)) {
               open(my_prof, solution, d);
               busy_units.insert(my_prof);
               occupied_next_pos.insert({u.pos.i, u.pos.j});
               opened = true;
               break;
            }
         }
       }

       if (!opened) {
         queue<pair<Pos, Dir>> q;
         vector<vector<int>> dist(board_rows(), vector<int>(board_cols(), -1));
         dist[u.pos.i][u.pos.j] = 0;
         
         vector<int> p = random_permutation(4);
         for (size_t k = 0; k < p.size(); ++k) {
            int idx = p[k];
            Dir d = DIRECTIONS[idx];
            Pos next = u.pos + d;
            if (pos_ok(next) && cell(next).type != Wall) {
               int uid = cell(next).id;
               if (uid != -1) continue;
               if (is_danger(next)) continue;

               dist[next.i][next.j] = 1;
               q.push({next, d});
            }
         }
         
         int max_depth = 120;
         while(!q.empty()) {
            pair<Pos, Dir> curr = q.front();
            q.pop();
            Pos p_curr = curr.first;
            Dir d0 = curr.second;
            int d = dist[p_curr.i][p_curr.j];
            if (d > max_depth) break;
            
            Cell c = cell(p_curr);
            int score = 0;
            if (c.box != -1) score = 2000000;
            if (c.gold) score = 2000000;
            if (c.money > 0) score = max(score, c.money * 2500);
            if (c.health_kit) {
               if (u.health < 30) score = max(score, 1000000);
               else if (u.health < 80) score = max(score, 5000);
            }
            
            if (score > 0) {
               if (d < enemy_dist[p_curr.i][p_curr.j]) {
                   int value = score - (d * 80);
                   if (value > 0) requests.push_back({my_prof, p_curr, value, d, d0});
               }
               else {
                   int value = (score / 5) - (d * 80);
                   if (value > 0) requests.push_back({my_prof, p_curr, value, d, d0});
               }
            }
            
            for (size_t k = 0; k < p.size(); ++k) {
               int idx = p[k];
               Dir dir = DIRECTIONS[idx];
               Pos next = p_curr + dir;
               if (pos_ok(next) && cell(next).type != Wall && dist[next.i][next.j] == -1) {
                  if (cell(next).id != -1) continue;
                  if (is_danger(next)) continue;
                  dist[next.i][next.j] = d + 1;
                  q.push({next, d0});
               }
            }
         }
       }
    }

    sort(requests.begin(), requests.end()); 

    for (const auto& req : requests) {
       if (busy_units.count(req.unit_id)) continue;
       
       if (taken_targets.count({req.target_pos.i, req.target_pos.j})) {
          bool is_enemy = false;
          if (pos_ok(req.target_pos)) {
             int uid = cell(req.target_pos).id;
             if (uid != -1 && unit(uid).player != me()) is_enemy = true;
          }
          
          if (!is_enemy) continue; 
       }
       
       Unit u = unit(req.unit_id);
       Pos next_pos = u.pos + req.first_move;
       if (occupied_next_pos.count({next_pos.i, next_pos.j})) {
           continue;
       }
       
       move(req.unit_id, req.first_move);
       busy_units.insert(req.unit_id);
       taken_targets.insert({req.target_pos.i, req.target_pos.j});
       occupied_next_pos.insert({next_pos.i, next_pos.j});
    }

    for (int id : my_soldiers) {
       if (busy_units.count(id)) continue;
       Unit u = unit(id);
       if (!u.is_alive()) continue;
       
       vector<int> p = random_permutation(4);
       bool moved = false;
       for (size_t k = 0; k < p.size(); ++k) {
          int idx = p[k];
          Dir d = DIRECTIONS[idx];
          Pos next = u.pos + d;
          if (pos_ok(next) && cell(next).type != Wall && cell(next).id == -1) {
             if (!occupied_next_pos.count({next.i, next.j})) {
                 move(id, d);
                 occupied_next_pos.insert({next.i, next.j});
                 moved = true;
                 break;
             }
          }
       }
       if (!moved) {
           occupied_next_pos.insert({u.pos.i, u.pos.j});
       }
    }
    
    if (my_prof != -1 && !busy_units.count(my_prof)) {
       Unit u = unit(my_prof);
       if (u.is_alive()) {
          vector<int> p = random_permutation(4);
          bool moved = false;
          for (size_t k = 0; k < p.size(); ++k) {
             int idx = p[k];
             Dir d = DIRECTIONS[idx];
             Pos next = u.pos + d;
             if (pos_ok(next) && cell(next).type != Wall && cell(next).id == -1 && !is_danger(next)) {
                if (!occupied_next_pos.count({next.i, next.j})) {
                    move(my_prof, d);
                    occupied_next_pos.insert({next.i, next.j});
                    moved = true;
                    break;
                }
             }
          }
          if (!moved) occupied_next_pos.insert({u.pos.i, u.pos.j});
       }
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
