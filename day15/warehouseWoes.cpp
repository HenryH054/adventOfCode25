#include <array>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void direction(int move[2], char direction) {
  switch (direction - 0) {
  case 94:
    move[0] = -1;
    move[1] = 0;
    break;
  case 62:
    move[0] = 0;
    move[1] = 1;
    break;
  case 118:
    move[0] = 1;
    move[1] = 0;
    break;
  case 60:
    move[0] = 0;
    move[1] = -1;
    break;
  }
}

long robotMove(vector<string> rows, int coord[2], size_t instruct) {
  int move[2];
  int iteration = 0;
  for (int i = instruct; i < rows.size(); ++i) {
    for (int j = 0; j < rows[i].size(); ++j) {
      direction(move, rows[i][j]);
      int y = coord[0], x = coord[1], crates = 0;
      while (true) {
        y += move[0];
        x += move[1];
        if (rows[y][x] == '.') {
          while (crates) {
            rows[y][x] = 'O';
            y -= move[0];
            x -= move[1];
            --crates;
          }
          rows[coord[0]][coord[1]] = '.';
          rows[y][x] = '@';
          coord[0] += move[0];
          coord[1] += move[1];
          break;
        } else if (rows[y][x] == 'O') {
          ++crates;
        } else if (rows[y][x] == '#') {
          break;
        }
      }
    }
  }

  long checksum = 0;

  for (int i = 0; i < instruct; ++i) {
    for (int j = 0; j < rows[i].size(); ++j) {
      if (rows[i][j] == 'O') {
        checksum += 100 * i + j;
      }
    }
  }

  return checksum;
}

long doubleRobotMove(vector<string> &rows, int coord[2], size_t instruct) {
  int move[2];
  int iteration = 0;
  for (int i = instruct; i < rows.size(); ++i) {
    for (int j = 0; j < rows[i].size(); ++j) {
      direction(move, rows[i][j]);
      int y = coord[0] + move[0], x = coord[1] + move[1];
      vector<array<int, 2>> q;
      int crates = 0;
      int crateCount = 0;
      bool crateFlag;
      if (move[1] == 1) {
        crateFlag = true;
      } else {
        crateFlag = false;
      }
      while (true) {
        // if we ever hit a wall the chain is dead regardless of what else is
        // happening
        if (rows[y][x] == '#') {
          break;
        }
        // if we are moving up or down we'll initizialize a queue and iterate
        // through until the queue is empty, if any can't move we'll break
        else if (move[0] != 0) {
          if (rows[y][x] == '.' && crates == 0) {
            for (int k = q.size() - 1; k >= 0; k--) {
              rows[q[k][0]][q[k][1]] = '.';
            }
            crateFlag = false;
            for (int k = q.size() - 1; k >= 0; k--) {

              if (crateFlag) {
                rows[q[k][0] + move[0]][q[k][1]] = '[';
              } else {
                rows[q[k][0] + move[0]][q[k][1]] = ']';
              }
              crateFlag = !crateFlag;
            }
            y = coord[0];
            x = coord[1];
            rows[y][x] = '.';
            y += move[0];
            x += move[1];
            rows[y][x] = '@';
            coord[0] = y;
            coord[1] = x;
            break;
          } else if (rows[y][x] == '.') {
            --crates;
            y = q[crateCount][0];
            x = q[crateCount][1];
            ++crateCount;
          } else if (rows[y][x] == '[') {
            q.push_back({y, x});
            q.push_back({y, x + 1});
            ++crates;
            ++crates;
          } else if (rows[y][x] == ']') {
            q.push_back({y, x - 1});
            q.push_back({y, x});
            ++crates;
            ++crates;
          }
        }
        // if we are moving side to side there is less logic needed
        else if (move[1] != 0) {
          if (rows[y][x] == '.') {
            while (crates) {
              if (crateFlag) {
                rows[y][x] = ']';
              } else {
                rows[y][x] = '[';
              }
              crateFlag = !crateFlag;
              --crates;
              x -= move[1];
            }
            rows[y - move[0]][x - move[1]] = '.';
            rows[y][x] = '@';
            coord[1] = x;
            break;
          }
          if (rows[y][x] == '[' || rows[y][x] == ']') {
            ++crates;
          }
        }
        y += move[0];
        x += move[1];
      }
    }
  }

  long checksum = 0;

  for (int i = 0; i < instruct; ++i) {
    for (int j = 0; j < rows[i].size(); ++j) {
      if (rows[i][j] == '[') {
        checksum += 100 * i + j;
      }
    }
  }

  return checksum;
}
void doubleUp(vector<string> &rows, size_t instruct) {
  for (int i = instruct - 1; i >= 0; --i) {
    for (int j = rows[i].size(); j >= 0; --j) {
      if (rows[i][j] == '@') {
        rows[i].insert(j + 1, 1, '.');
      } else if (rows[i][j] == 'O') {
        rows[i][j] = ']';
        rows[i].insert(j, 1, '[');
      } else if (rows[i][j] == '#') {
        rows[i][j] = '#';
        rows[i].insert(j, 1, '#');
      } else if (rows[i][j] == '.') {
        rows[i][j] = '.';
        rows[i].insert(j, 1, '.');
      }
    }
  }
}

int main() {
  vector<string> rows;

  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;
  size_t cnt = 0, instruct;
  while (getline(file, line)) {
    ++cnt;
    rows.push_back(line);
    if (line == "") {
      instruct = cnt;
    }
  }

  file.close();

  bool flag = false;
  int coord[2];
  int coord2[2];
  for (int i = 0; i < instruct; i++) {
    for (int j = 0; j < rows[0].size(); ++j) {
      if (rows[i][j] == '@') {
        coord[0] = i;
        coord[1] = j;
        coord2[0] = i;
        coord2[1] = j;
        flag = true;
        break;
      }
    }
    if (flag) {
      break;
    }
  }

  // cout << robotMove(rows, coord, instruct) << endl;
  doubleUp(rows, instruct);
  coord2[1] = coord2[1] * 2;
  cout << doubleRobotMove(rows, coord2, instruct) << endl;
}
