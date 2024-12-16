#include <array>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

long modulo(long x, long y) {
  long result = x % y;
  if (result < 0) {
    result = y + result;
  }
  return result;
}

void printTree(vector<vector<int>> map, int xStart, int yStart) {
  int treeX = 15, treeY = 19;
  for (int i = -14; i < treeY; ++i) {
    for (int j = -16; j < treeX; ++j) {
      if (map[yStart + i][xStart + j]) {
        cout << "W";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
}

long quadrantCounter(long height, long width, long iterations,
                     vector<array<long, 4>> robots) {
  long midW = width / 2, midH = height / 2, q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  long x, y;
  vector<vector<int>> map = vector(height, vector(width, int()));
  // cout << midW << "  " << midH << endl;
  for (array<long, 4> i : robots) {
    x = modulo(i[0] + (i[2] * iterations), width);
    y = modulo(i[1] + (i[3] * iterations), height);
    map[y][x] += 1;
    if (x > midW && y < midH) {
      q1++;
    } else if (x < midW && y < midH) {
      q2++;
    } else if (x < midW && y > midH) {
      q3++;
    } else if (x > midW && y > midH) {
      q4++;
    } else {
    }
  }
  int size = 31;
  int tree[31] = {0};
  bool treeFound = false;
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      for (int k = 1; k < size; ++k) {
        tree[k - 1] = tree[k];
      }
      tree[size - 1] = map[i][j];
      tree[size - 1] = map[i][j];
      bool flag = true;
      for (int k : tree) {
        if (!k) {
          flag = false;
          break;
        }
      }
      if (flag) {
        treeFound = !treeFound;
        if (treeFound) {
          printTree(map, i, j);
        }
      }
    }
  }
  return q1 * q2 * q3 * q4;
}

int main() {
  vector<string> rows;
  long height = 103, width = 101;

  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;

  while (getline(file, line)) {
    rows.push_back(line);
  }

  file.close();

  vector<array<long, 4>> robots;

  long start, end, px, py, vx, vy;
  for (string i : rows) {
    start = i.find("p=") + 2;
    end = i.find(",");
    px = stol(i.substr(start, end - start));
    start = ++end;
    end = i.find(" ");
    py = stol(i.substr(start, end - start));
    start = i.find("v=") + 2;
    end = i.find_last_of(",");
    vx = stol(i.substr(start, end - start));
    start = ++end;
    vy = stol(i.substr(start));
    robots.push_back({px, py, vx, vy});
  }

  for (long i = 1; i < 10000; ++i) {
    cout << endl << "Iteraion: " << i << endl;
    quadrantCounter(height, width, i, robots);
  }

  return 0;
}
