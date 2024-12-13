#include <array>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

long searchLocal(vector<string> &rows, bool **checked, size_t height,
                 size_t width, size_t y, size_t x) {
  long area = 0;
  long perm = 0;
  int offset[2];
  vector<array<size_t, 2>> stack;
  stack.push_back({y, x});
  checked[y][x] = true;
  int i, j;
  while (stack.size() > 0) {
    array<size_t, 2> arr = stack.back();
    i = arr[0];
    j = arr[1];
    stack.pop_back();
    area++;
    for (int k = 0; k < 4; k++) {
      switch (k) {
      case 0:
        offset[0] = -1;
        offset[1] = 0;
        break;
      case 1:
        offset[0] = 1;
        offset[1] = 0;
        break;
      case 2:
        offset[0] = 0;
        offset[1] = 1;
        break;
      case 3:
        offset[0] = 0;
        offset[1] = -1;
        break;
      }
      size_t yOff = i + offset[0], xOff = j + offset[1];
      if (yOff < 0 || yOff >= height || xOff < 0 || xOff >= width ||
          rows[i][j] != rows[yOff][xOff]) {
        perm++;
      } else if (!checked[yOff][xOff]) {
        stack.push_back({yOff, xOff});
        checked[yOff][xOff] = true;
      }
    }
  };

  long price = perm * area;
  return price;
}

long pricing(vector<string> &rows, bool **checked, size_t height,
             size_t width) {
  long price = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (!checked[i][j]) {
        price += searchLocal(rows, checked, height, width, i, j);
      }
    }
  }
  return price;
}

long bulkSearchLocal(vector<string> &rows, bool **checked, size_t height,
                     size_t width, size_t y, size_t x) {
  long area = 0;
  int offset[2];
  vector<array<size_t, 2>> stack;
  vector<array<size_t, 2>> shape;
  stack.push_back({y, x});
  shape.push_back({y, x});
  checked[y][x] = true;
  int i, j;
  while (stack.size() > 0) {
    array<size_t, 2> arr = stack.back();
    i = arr[0];
    j = arr[1];
    stack.pop_back();
    area++;
    bool sideChecker[] = {false, false, false, false};
    int count = 0;
    for (int k = 0; k < 4; k++) {
      switch (k) {
      case 0:
        offset[0] = 1;
        offset[1] = 0;
        break;
      case 1:
        offset[0] = 0;
        offset[1] = 1;
        break;
      case 2:
        offset[0] = -1;
        offset[1] = 0;
        break;
      case 3:
        offset[0] = 0;
        offset[1] = -1;
        break;
      }
      size_t yOff = i + offset[0], xOff = j + offset[1];
      if (yOff < 0 || yOff >= height || xOff < 0 || xOff >= width ||
          rows[i][j] != rows[yOff][xOff]) {
        sideChecker[k] = true;
        count++;
      } else if (!checked[yOff][xOff]) {
        stack.push_back({yOff, xOff});
        shape.push_back({yOff, xOff});
        checked[yOff][xOff] = true;
      }
    }
  }
  size_t xMin = shape[0][1], xMax = shape[0][1], yMin = shape[0][0],
         yMax = shape[0][0];
  for (const auto &i : shape) {
    if (i[1] < xMin) {
      xMin = i[1];
    }
    if (i[1] > xMax) {
      xMax = i[1];
    }
    if (i[0] < yMin) {
      yMin = i[0];
    }
    if (i[0] > yMax) {
      yMax = i[0];
    }
  }
  size_t ySize = yMax - yMin + 1, xSize = xMax - xMin + 1;
  vector<vector<bool>> shapeMap(ySize, vector<bool>(xSize));
  for (const auto &i : shape) {
    shapeMap[i[0] - yMin][i[1] - xMin] = true;
  }

  bool topCont = false;
  bool botCont = false;
  size_t sides = 0;
  for (int i = 0; i < ySize; ++i) {
    topCont = false;
    botCont = false;
    for (int j = 0; j < xSize; ++j) {
      if (shapeMap[i][j] && (i - 1 < 0 || !shapeMap[i - 1][j])) {
        if (!topCont) {
          sides++;
        }
        topCont = true;
      } else if (topCont) {
        topCont = false;
      }
      if (shapeMap[i][j] && (i + 1 >= ySize || !shapeMap[i + 1][j])) {
        if (!botCont) {
          sides++;
        }
        botCont = true;
      } else if (botCont) {
        botCont = false;
      }
    }
  }
  bool leftCont = false;
  bool rightCont = false;
  for (int i = 0; i < xSize; ++i) {
    leftCont = false;
    rightCont = false;
    for (int j = 0; j < ySize; ++j) {
      if (shapeMap[j][i] && (i - 1 < 0 || !shapeMap[j][i - 1])) {
        if (!leftCont) {
          sides++;
        }
        leftCont = true;
      } else if (leftCont) {
        leftCont = false;
      }
      if (shapeMap[j][i] && (i + 1 >= xSize || !shapeMap[j][i + 1])) {
        if (!rightCont) {
          sides++;
        }
        rightCont = true;
      } else if (rightCont) {
        rightCont = false;
      }
    }
  }
  long price = sides * area;
  return price;
}

long bulkPricing(vector<string> &rows, bool **checked, size_t height,
                 size_t width) {
  long price = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (!checked[i][j]) {
        price += bulkSearchLocal(rows, checked, height, width, i, j);
      }
    }
  }
  return price;
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

  size_t height = rows.size();
  size_t width = rows[0].size();

  bool **checked = new bool *[height];
  for (int i = 0; i < height; i++) {
    checked[i] = new bool[width]();
  }

  // cout << pricing(rows, checked, height, width) << endl;

  cout << bulkPricing(rows, checked, height, width) << endl;
  for (int i = 0; i < height; i++) {
    delete[] (checked[i]);
  }
  delete[] (checked);
  return 0;
}
