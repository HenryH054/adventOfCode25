#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
  vector<string> rows;

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

  size_t queue;
  unordered_map<char, vector<array<int, 2>>> hashMap;
  ulong height = rows.size(), width = rows[0].size();
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char let;
      if ((let = rows[i][j]) != '.') {
        hashMap[let].push_back(array<int, 2>{i, j});
      }
    }
  }

  vector<array<int, 2>> antinodes;
  vector<array<int, 2>> uniqueCheck;
  for (const auto &i : hashMap) {
    ulong size = i.second.size();
    for (size_t j = 0; j < size; ++j) {
      for (size_t k = 0; k < size; ++k) {
        if (j == k) {
          continue;
        }
        int y = i.second[j][0];
        int x = i.second[j][1];
        int cy = y - i.second[k][0];
        int cx = x - i.second[k][1];
        y -= cy;
        x -= cx;
        while (y >= 0 && y < height && x >= 0 && x < width) {
          // cout << y << " " << x << endl;
          antinodes.push_back(array<int, 2>{y, x});
          y -= cy;
          x -= cx;
        }
      }
    }
  }

  int unique = 0;
  for (const array<int, 2> coords : antinodes) {
    // cout << "\nAntinode at: " << coords[0] << ", " << coords[1];
    bool flag = false;
    for (const array<int, 2> check : uniqueCheck) {
      if (check == coords) {
        flag = true;
        // cout << "tossing, antinode or structure exists";
        break;
      }
    }
    if (flag) {
      continue;
    }
    unique++;
    uniqueCheck.push_back(coords);
  }

  cout << unique;

  return 0;
}
