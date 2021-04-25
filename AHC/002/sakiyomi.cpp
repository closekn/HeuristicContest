#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 50;
string DIR[4] = {"U", "D", "L", "R"};

int depth;

int si, sj;
int t[MAX_LEN][MAX_LEN], p[MAX_LEN][MAX_LEN];



int next_sim(int i, int j, bool visited[], int num) {
  if ( num == 0 ) { return p[i][j]; }

  bool *now_visited;
  now_visited = new bool[2500];
  memcpy(now_visited, visited, sizeof(visited));
  now_visited[t[i][j]] = true;

  int sim_p = 0;

  if ( i > 0 && (! visited[t[i-1][j]]) && p[i-1][j] > sim_p ) {
    int tmp = next_sim(i-1, j, now_visited, num-1);
    if ( tmp > sim_p ) { sim_p = tmp; }
  }
  if ( i < MAX_LEN-1 && (! visited[t[i+1][j]]) && p[i+1][j] > sim_p ) {
    int tmp = next_sim(i+1, j, now_visited, num-1);
    if ( tmp > sim_p ) { sim_p = tmp; }
  }
  if ( j > 0 && (! visited[t[i][j-1]]) && p[i][j-1] > sim_p ) {
    int tmp = next_sim(i, j-1, now_visited, num-1);
    if ( tmp > sim_p ) { sim_p = tmp; }
  }
  if ( j < MAX_LEN-1 && (! visited[t[i][j+1]]) && p[i][j+1] > sim_p ) {
    int tmp = next_sim(i, j+1, now_visited, num-1);
    if ( tmp > sim_p ) { sim_p = tmp; }
  }

  delete[] now_visited;
  return p[i][j] + sim_p;
}

int sakiyomi(int i, int j, bool visited[]) {
  int sim_p = next_sim(i, j, visited, depth);

  return sim_p;
}

int next_dir(int i, int j, bool visited[]) {
  int ret  = 4;
  int sim_p = -1;

  if ( i > 0 && (! visited[t[i-1][j]]) ) {
    int tmp = sakiyomi(i-1, j, visited);
    if ( tmp > sim_p ) { ret = 0; sim_p = tmp; }
  }
  if ( i < MAX_LEN-1 && (! visited[t[i+1][j]]) ) {
    int tmp = sakiyomi(i+1, j, visited);
    if ( tmp > sim_p ) { ret = 1; sim_p = tmp; }
  }
  if ( j > 0 && (! visited[t[i][j-1]]) ) {
    int tmp = sakiyomi(i, j-1, visited);
    if ( tmp > sim_p ) { ret = 2; sim_p = tmp; }
  }
  if ( j < MAX_LEN-1 && (! visited[t[i][j+1]]) ) {
    int tmp = sakiyomi(i, j+1, visited);
    if ( tmp > sim_p ) { ret = 3; sim_p = tmp; }
  }

  return ret;
}

void update_pos(int* i, int* j, int next) {
  if ( next == 0 ) { *i -= 1; }
  if ( next == 1 ) { *i += 1; }
  if ( next == 2 ) { *j -= 1; }
  if ( next == 3 ) { *j += 1; }
}

string calc() {
  string ans = "";
  int max_p = p[si][sj];
  
  for ( depth = 0 ; depth < 30; depth++ ) {
    bool visited[2500] = {};
    string now_ans = "";
    int point = 0;

    int i = si;
    int j = sj;
    visited[t[i][j]] = true;
    point = p[i][j];

    while ( true ) {
      int next = next_dir(i, j, visited);
      if ( next == 4 ) { break; }
      now_ans += DIR[next];
      update_pos(&i, &j, next);
      visited[t[i][j]] = true;
      point += p[i][j];
    }

    if ( point > max_p ) {
      max_p = point;
      ans = now_ans;
    }
  }

  return ans;
}

int main() {
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

  cout << calc() << endl;
  return 0;
}
