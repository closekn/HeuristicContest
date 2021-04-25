#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 50;
string DIR[5] = {"U", "D", "L", "R", ""};
int dir2int(char c) {
  if ( c == 'U' ) { return 0; }
  if ( c == 'D' ) { return 1; }
  if ( c == 'L' ) { return 2; }
  if ( c == 'R' ) { return 3; }
  return 4;
}
void move(int* i, int* j, int dir) {
  if ( dir == 0 && *i > 0 ) { *i -= 1; }
  if ( dir == 1 && *i < MAX_LEN-1 ) { *i += 1; }
  if ( dir == 2 && *j > 0 ) { *j -= 1; }
  if ( dir == 3 && *j < MAX_LEN-1 ) { *j += 1; }
}
int si, sj;
int t[MAX_LEN][MAX_LEN], p[MAX_LEN][MAX_LEN];

const double TIME_LIMIT = 1.8;
const int INF = 2147483647;
double now_time(clock_t start, clock_t now) {
  return ((double)(now - start) / CLOCKS_PER_SEC);
}

int next_dir(int i, int j, bool visited[]) {
  int ret = 4;
  int next_p = -1;
 
  if ( i > 0 && (! visited[t[i-1][j]]) && p[i-1][j] > next_p ) { ret = 0; next_p = p[i-1][j]; }
  if ( i < MAX_LEN-1 && (! visited[t[i+1][j]]) && p[i+1][j] > next_p ) { ret = 1; next_p = p[i+1][j]; }
  if ( j > 0 && (! visited[t[i][j-1]]) && p[i][j-1] > next_p ) { ret = 2; next_p = p[i][j-1]; }
  if ( j < MAX_LEN-1 && (! visited[t[i][j+1]]) && p[i][j+1] > next_p ) { ret = 3; next_p = p[i][j+1]; }
 
  return ret;
}

int next_dir_2(int i, int j, bool visited[]) {
  int ret = 4;
  int next_p = -1;
 
  if ( i > 0 && (! visited[t[i-1][j]]) && p[i-1][j] > next_p ) { ret = 0; next_p = p[i-1][j]; }
  if ( i < MAX_LEN-1 && (! visited[t[i+1][j]]) && p[i+1][j] > next_p ) { ret = 1; next_p = p[i+1][j]; }
  if ( j > 0 && (! visited[t[i][j-1]]) && p[i][j-1] > next_p ) { ret = 2; next_p = p[i][j-1]; }
  if ( j < MAX_LEN-1 && (! visited[t[i][j+1]]) && p[i][j+1] > next_p ) { ret = 3; next_p = p[i][j+1]; }
 
  return ret;
}

struct STATE {
  string route;
};

void init(STATE& state) {
  state.route = "";
  int i = si, j = sj;
  bool visited[2500] = {};
  visited[t[i][j]] = true;

  // 貪欲
  while ( true ) {
    int next = next_dir(i, j, visited);
    if ( next == 4 ) { break; }
    state.route += DIR[next];
    move(&i, &j, next);
    visited[t[i][j]] = true;
  }
}

void modify(STATE& state) {
  string mod_route = "";
  int i = si;
  int j = sj;
  bool visited[2500] = {};
  visited[t[i][j]] = true;

  int use_len = rand() % state.route.size();
  for ( int k = 0; k < use_len; k++ ) {
    mod_route += state.route[k];
    move(&i, &j, dir2int(state.route[k]));
    visited[t[i][j]] = true;
  }

  // randに変更
  int r = rand() % 4;
  mod_route += DIR[r];
  move(&i, &j, r);
  visited[t[i][j]] = true;

  // それ以降貪欲
  while ( true ) {
    int next = next_dir(i, j, visited);
    if ( next == 4 ) { break; }
    mod_route += DIR[next];
    move(&i, &j, next);
    visited[t[i][j]] = true;
  }

  state.route = mod_route;
}

int calc_score(STATE& state) {
  int point = p[si][sj];
  int i = si;
  int j = sj;
  bool visited[2500] = {};
  visited[t[i][j]] = true;
  for ( int k = 0; k < state.route.size(); k++ ) {
    move(&i, &j, dir2int(state.route[k]));
    point += p[i][j];
    if ( visited[t[i][j]] ) { return 0; }
    visited[t[i][j]] = true;
  }
  return point;
}

void mountain(STATE& state) {
  init(state);
  int max_score = calc_score(state);
  STATE pre_state = state;

  double start_temp = 30;
  double end_temp = 10;
  clock_t start = clock();
  while ( true ) {
    clock_t now = clock();
    if ( now_time(start, now) > TIME_LIMIT ) { break; }

    STATE new_state = pre_state;
    modify(new_state);

    int new_score = calc_score(new_state);
    int pre_score = calc_score(pre_state);

    if ( new_score > max_score ) {
      max_score = new_score;
      state = new_state;
    }

    double temp = start_temp + (end_temp - start_temp) * (double)(now-start) / TIME_LIMIT;
    double prob = exp((new_score-pre_score)/temp);

    if (prob > (rand()%INF)/(double)INF) {
      pre_state = new_state;
    }
  }
}

int main() {
  srand(time(NULL));
  cin >> si >> sj;

  for ( int i = 0; i < MAX_LEN; i++ ) {
    for ( int j = 0; j < MAX_LEN; j++ ) {
      cin >> t[i][j];
    }
  }
  for ( int i = 0; i < MAX_LEN; i++ ) {
    for ( int j = 0; j < MAX_LEN; j++ ) {
      cin >> p[i][j];
    }
  }

  STATE ans;
  mountain(ans);
  cout << ans.route << endl;
  return 0;
}
