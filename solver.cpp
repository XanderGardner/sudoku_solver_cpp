#include <exception>
#include <limits>
#include <new>
#include <typeinfo>
#include <stdexcept>
#include <utility>
#include <functional>
#include <memory>
#include <string>
#include <locale>
#include <stdlib.h>

#include <complex>
#include <numeric>
#include <valarray>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <array>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <stack>
#include <iterator>
#include <list>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <math.h>
#include <limits.h>

#include <chrono>
#include <thread>

using namespace std;

vector<vector<int>> board;
double delay = 1;

void print_board() {
  for (auto row : board) {
    for (auto num : row) {
      cout << num << ' ';
    }
    cout << '\n';
  }
  cout << "===============================\n";
}

bool valid(int row, int col) {
  // valid row
  for (int j = 0; j < 9; j++) {
    if (j == col) continue;
    if (board[row][col] == board[row][j]) return false; 
  }

  // valid col
  for (int i = 0; i < 9; i++) {
    if (i == row) continue;
    if (board[row][col] == board[i][col]) return false;
  }

  // valid box
  for (int i = 3 * int(row / 3); i < 3 * int((row+3)/3); i++) {
    for (int j = 3 * int(col/3); j < 3 * int((col+3)/3); j++) {
      if (i == row && j == col) continue;
      if (board[row][col] == board[i][j]) return false;
    }
  }
  return true;
}

bool solve() {
  // get next 0
  int row, col;
  for (int i = 0; i <= 9; i++) {
    if (i==9) return true;
    for (int j = 0; j < 9; j++) {
      if (!board[i][j]) {
        row = i;
        col = j;
        goto after0;
      }
    }
  }

  after0:
  for (int i = 1; i <= 9; i++) {
    board[row][col] = i;
    print_board();
    this_thread::sleep_for(5ms);
    if (valid(row, col) && solve()) return true;
  }
  board[row][col] = 0;
  return false;
}

int main() {
  // read board in
  for (int row = 0; row < 9; row++) {
    vector<int> curr_row;
    for (int col = 0; col < 9; col++) {
      int num; cin >> num;
      curr_row.push_back(num);
    }
    board.push_back(curr_row);
  }
  cout << "===============================\n";

  if (solve()) {
    cout << "solved:\n";
    print_board();
  } else {
    cout << "unsolvable\n";
  }
}
