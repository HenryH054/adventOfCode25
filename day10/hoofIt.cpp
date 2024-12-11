#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <vector>
using namespace std;

int trailMakerHelper(vector<string> &map, array<int, 2> yx, int height,
                     int width, char curr, char safeThrowaway) {
  if (curr == '9') {
    map[yx[0]][yx[1]] = safeThrowaway;
    return 1;
  }
  int offsetY, offsetX, paths = 0;
  for (int i = 0; i < 4; ++i) {
    switch (i) {
    case 0:
      offsetY = yx[0];
      offsetX = yx[1] + 1;
      break;
    case 1:
      offsetY = yx[0];
      offsetX = yx[1] - 1;
      break;
    case 2:
      offsetY = yx[0] + 1;
      offsetX = yx[1];
      break;
    case 3:
      offsetY = yx[0] - 1;
      offsetX = yx[1];
      break;
    }
    if (offsetY < height && offsetY >= 0 && offsetX < width && offsetX >= 0 &&
        map[offsetY][offsetX] == curr + 1) {
      paths += trailMakerHelper(map, array<int, 2>{offsetY, offsetX}, height,
                                width, curr + 1, safeThrowaway);
    }
  }
  return paths;
}

int trailMaker(vector<string> &map) {
  int paths = 0;
  int height = map.size(), width = map[0].size();
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] == '0') {
        vector<string> tempMap = map;
        paths += trailMakerHelper(tempMap, array<int, 2>{i, j}, height, width,
                                  '0', 'a');
      }
    }
  }

  return paths;
}

int trailRater(vector<string> &map) {
  int paths = 0;
  int height = map.size(), width = map[0].size();
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; j++) {
      if (map[i][j] == '0') {
        paths +=
            trailMakerHelper(map, array<int, 2>{i, j}, height, width, '0', '9');
      }
    }
  }

  return paths;
}
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

  cout << trailMaker(rows) << endl;
  cout << trailRater(rows) << endl;

  return 0;
}
