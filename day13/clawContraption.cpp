#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long linearPossible(double &ax, double &ay, double &bx, double &by, double &px,
                    double &py, long offset) {
  cout << ax << ", " << ay << endl
       << bx << ", " << by << endl
       << px << ", " << py << endl;
  px += offset;
  py += offset;
  double A = (px * by - bx * py) / (ax * by - bx * ay);
  double B = (ax * py - px * ay) / (ax * by - bx * ay);

  if (floor(A) == A && floor(B) == B) {
    return A * 3 + B;
  } else {
    return 0;
  }
}

long possible(size_t ax, size_t ay, size_t bx, size_t by, size_t px, size_t py,
              size_t max) {
  long price = 400;
  long cost = 0;
  bool flag = false;
  for (int i = 0; i <= max; ++i) {
    for (int j = 0; j <= max; ++j) {
      if (ax * i + bx * j == px && ay * i + by * j == py &&
          (cost = i * 3 + j) < price) {
        price = cost;
        flag = true;
      }
    }
  }
  if (flag) {
    return price;
  }
  return 0;
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

  vector<array<size_t, 6>> problem;
  long price = 0;
  long cost = 0;
  for (int i = 0; i < rows.size(); i += 4) {
    double ax, ay, bx, by, px, py;
    size_t start, end;
    start = rows[i].find('+') + 1;
    end = rows[i].find(',');
    ax = stod(rows[i].substr(start, end - start));
    start = end + 4;
    ay = stod(rows[i].substr(start));
    start = rows[i + 1].find('+') + 1;
    end = rows[i + 1].find(',');
    bx = stod(rows[i + 1].substr(start, end - start));
    start = end + 4;
    by = stod(rows[i + 1].substr(start));
    start = rows[i + 2].find('=') + 1;
    end = rows[i + 2].find(',');
    px = stod(rows[i + 2].substr(start, end - start));
    start = end + 4;
    py = stod(rows[i + 2].substr(start));
    cout << "Machine " << i / 4 + 1 << ":" << endl;
    if ((cost = linearPossible(ax, ay, bx, by, px, py, 10000000000000))) {
      price += cost;
    }
  }

  cout << price;
  return 0;
}
