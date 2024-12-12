#include <array>
#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>
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
  cout << rows[y][x] << ": ";
  long area = 0;
  int offset[2];
  vector<array<size_t, 2>> stack;
  stack.push_back({y, x});
  checked[y][x] = true;
  int i, j;
  int corners = 0;
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
        checked[yOff][xOff] = true;
      }
    }
    cout << "Finding sides at " << i << ", " << j << " Current Sides: " << corners << endl;
    bool flag = false;
    if (count == 4) {
      // if all sides have no related "crop" then we have 4 sides
      corners += 4;
    }
    if (count == 2) {
      // if count is equal to two than check if they are continuous if so than
      // we have another corner
      cout << "we got a twofer" << endl;
      if (sideChecker[0] && sideChecker[1]) {
        cout << "Continuous Sides +2" << endl;
        corners++;
      } else if (sideChecker[1] && sideChecker[2]) {
        cout << "Continuous Sides +2" << endl;
        corners++;
      } else if (sideChecker[2] && sideChecker[3]) {
        cout << "Continuous Sides +2" << endl;
        corners++;
      } else if (sideChecker[3] && sideChecker[0]) {
        cout << "Continuous Sides +2" << endl;
        corners++;
      } else {
        cout << "has been flagged" << endl;
        flag = true;
      }
    }
    if (count == 3) {
      // when count is three we have two guranteed corners on the outside
      // in addition we have two possible inside corners, in order to simplify
      // things we will ONLY check inside corners in the downward direction
      // as things are written downward is on case 2
      corners += 2;
      cout << "Three empty Sides +2" << endl;
      if ((!sideChecker[2] || !sideChecker[3]) && i - 1 >= 0 &&
          i - 1 < height && j - 1 >= 0 && j - 1 < width &&
          rows[i][j] == rows[i - 1][j - 1]) {
        cout << "Inside corner on bottom right Sides +1" << endl;
        corners++;
      }
      if ((!sideChecker[2] || !sideChecker[1]) && i - 1 >= 0 &&
          i - 1 < height && j + 1 >= 0 && j + 1 < width &&
          rows[i][j] == rows[i - 1][j + 1]) {
        cout << "Inside corner on bottom left Sides +1" << endl;
        corners++;
      }
    }
    if (count == 1 || flag) {
      // when count is one there's a possibility for one inside corner to exist
      // if a square exists down at an angle but not next to it.
      cout << "count == 1 or flag hit" << endl;
      if (!sideChecker[1] && i - 1 >= 0 && i - 1 < height && j - 1 >= 0 &&
          j - 1 < width && rows[i][j] == rows[i - 1][j - 1]) {
        cout << "Inside corner on bottom right" << endl;
        corners++;
      }
      if (!sideChecker[3] && i - 1 >= 0 && i - 1 < height && j + 1 < 0 &&
          j + 1 >= width && rows[i][j] == rows[i - 1][j + 1]) {
        cout << "Inside corner on bottom left" << endl;
        corners++;
      }
    }
  }

  cout << corners;
  cout << endl;
  long price = 0;
  return 0;
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

  ifstream file("input2");

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
