#include <array>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;

struct Marker {
  int visited, structure, guard;
  vector<int> direction;

  Marker(bool structures, bool guards, vector<int> directions = {})
      : visited(0), structure(structures), direction(directions),
        guard(guards) {}
};

int uniqueId = 100;

void findGuard(vector<vector<Marker>> &rows, int &y, int &x) {
  for (int i = 0; i < rows.size(); i++) {
    for (int j = 0; j < rows[0].size(); j++) {
      if (rows[i][j].guard) {
        x = j;
        y = i;
        return;
      }
    }
  }
}

void direct(int m[2], int direction) {
  switch (direction) {
  case 0:
    m[0] = -1;
    m[1] = 0;
    break;
  case 1:
    m[0] = 0;
    m[1] = 1;
    break;
    break;
  case 2:
    m[0] = 1;
    m[1] = 0;
    break;
  case 3:
    m[0] = 0;
    m[1] = -1;
    break;
  }
}

int guardRoute(vector<vector<Marker>> &rows, size_t y, size_t x) {
  size_t uniq = 0, direction = 0, y_size = rows.size(), x_size = rows[0].size();
  uniqueId++;
  int m[2];
  direct(m, direction);
  while (true) {
    // sets visited so that we know if a square is unique
    if (rows[y][x].visited != uniqueId) {
      rows[y][x].visited = uniqueId;
      rows[y][x].direction.clear();
      uniq++;
    } else {
      for (int i : rows[y][x].direction) {
        if (direction == i) {
          return -1;
        }
      }
    }
    // checks to see if we've been on the same square going in the same
    // direction IE if we're looping
    rows[y][x].direction.push_back(direction);
    y += m[0];
    x += m[1];
    if (x < 0 || y < 0 || y >= y_size || x >= x_size) {
      return uniq;
    }
    if (rows[y][x].structure) {
      y -= m[0];
      x -= m[1];
      direction++;
      direction %= 4;
      direct(m, direction);
    }
  }
  return uniq;
}

int blockade(vector<vector<Marker>> rows, int guard_y, int guard_x) {
  int amount = 0;
  guardRoute(rows, guard_y, guard_x);
  vector<array<int, 2>> visits;

  for (int i = 0; i < rows.size(); i++) {
    for (int j = 0; j < rows[i].size(); j++) {
      if (rows[i][j].visited) {
        int arr[2] = {i, j};
        visits.emplace_back(array<int, 2>{i, j});
      }
    }
  }

  for (const array<int, 2> &i : visits) {
    rows[i[0]][i[1]].structure = true;
    if (guardRoute(rows, guard_y, guard_x) == -1) {
      amount++;
    }
    rows[i[0]][i[1]].structure = false;
  }

  return amount;
}

int main() {
  vector<vector<Marker>> rows;

  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;

  while (getline(file, line)) {
    vector<Marker> procLine = {};
    for (char x : line) {
      if (x == '#') {
        procLine.push_back(Marker(true, false));
      } else if (x == '^') {
        procLine.push_back(Marker(false, true));
      } else {
        procLine.push_back(Marker(false, false));
      }
    }
    rows.push_back(procLine);
  }

  file.close();
  vector<vector<Marker>> temp = rows;
  int y, x;
  findGuard(rows, y, x);

  cout << "Unique Places Visited: " << guardRoute(rows, y, x) << "\n";

  cout << "Blockades Available: " << blockade(rows, y, x) << "\n";
}
