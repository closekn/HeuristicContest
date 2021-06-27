#include <bits/stdc++.h>
using namespace std;

int n, m;
string s[805];

const double BASE_POINT = 100000000.0;
const double TIME_LIMIT = 2.8;

double now_time(clock_t start, clock_t now) {
  return ((double)(now - start) / CLOCKS_PER_SEC);
}

char random_char() {
  int rd = rand() % 9;
  if ( rd == 8 ) { return '.'; }
  return 'A' + rd;
}

char random_char_alp() {
  return 'A' + (rand() % 8);
}

int random_pos() {
  return rand() % n;
}

struct STATE {
  string table[25];
  int num_d;
  double score;
};

void modify(STATE& state) {
  int i = random_pos();
  int j = random_pos();
  if ( state.score < BASE_POINT ) {
    state.table[i][j] = random_char_alp();
  } else {
    if ( state.table[i][j] != '.' ) {
      state.table[i][j] = '.';
      state.num_d += 1;
    }
  }
}

double calc_score(STATE& state) {
  int c = 0;

  for ( int si = 0; si < m; si++ ) {

    for ( int i = 0; i < n; i++ ) {
      for ( int j = 0; j < n; j++ ) {

        if ( s[si][0] != state.table[i][j] ) { continue; }

        bool in_row = true;
        bool in_line = true;
        for ( int k = 1; k < s[si].size(); k++ ) {
          if ( s[si][k] != state.table[i][(j+k)%n] ) { in_row = false; }
          if ( s[si][k] != state.table[(i+k)%n][j] ) { in_line = false; }
        }

        if ( in_row || in_line ) {
          c++;
          i = n;
          break;
        }

      }
    }

  }

  double point;
  if ( c == m ) {
    point = BASE_POINT / ( 2*n*n - state.num_d ) * 2*n*n;
  } else {
    point = BASE_POINT / m * c;
  }
  return round(point);

}

void init(STATE& state) {
  for ( int i = 0; i < n; i++ ) {
    state.table[i] = "";
    for ( int j = 0; j < n; j++ ) {
      state.table[i] += random_char_alp();
    }
  }

  state.num_d = 0;
  state.score = calc_score(state);
}

void mountain(STATE& state) {
  init(state);
  
  clock_t start = clock();
  while ( true ) {
    clock_t now = clock();
    if ( now_time(start, now) > TIME_LIMIT ) { break; }

    STATE new_state = state;
    modify(new_state);
    new_state.score = calc_score(new_state);

    if ( new_state.score > state.score ) {
      state = new_state;
    }
  }
}

int main() {
  // rand init
  srand(time(NULL));
  
  // input
  cin >> n >> m;
  for ( int i = 0; i < m; i++ ) {
    cin >> s[i];
  }

  // calc
  STATE ans;
  mountain(ans);

  // answer
  for ( int i = 0; i < n; i++ ) {
    cout << ans.table[i] << endl;;
  }

  return 0;
}
