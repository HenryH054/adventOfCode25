#include <exception>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int search(vector<string> rows, string word, int direction, int y, int x) {
  int direct[2];
  switch (direction) {
  case 0:
    // up direction
    direct[0] = -1;
    direct[1] = 0;
    break;
  case 1:
    // up-right direction
    direct[0] = -1;
    direct[1] = 1;
    break;
  case 2:
    // right direction
    direct[0] = 0;
    direct[1] = 1;
    break;
  case 3:
    // down-right direction
    direct[0] = 1;
    direct[1] = 1;
    break;
  case 4:
    // down direction
    direct[0] = 1;
    direct[1] = 0;
    break;
  case 5:
    // down-left direction
    direct[0] = 1;
    direct[1] = -1;
    break;
  case 6:
    // left direction
    direct[0] = 0;
    direct[1] = -1;
    break;
  case 7:
    // up-left direction
    direct[0] = -1;
    direct[1] = -1;
    break;
  }
  for (int i = 0; i < word.size(); i++) {
    try {

      if (word[i] == rows.at(y).at(x)) {
        y += direct[0];
        x += direct[1];
      } else {
        return 0;
      }
    } catch (const exception &e) {
      return 0;
    }
  }
  return 1;
}

int search(vector<string> rows, string word) {
  int matches = 0;
  int numDirections = 8;
  for (int y = 0; y < rows.size(); y++) {
    for (int x = 0; x < rows[y].size(); x++) {
      if (rows[y][x] == word[0]) {
        vector<future<int>> futures;
        for (int i = 0; i < numDirections; i++) {
          futures.push_back(async(launch::async, [rows, word, i, y, x]() {
            return search(rows, word, i, y, x);
          }));
        }
        for (int i = 0; i < numDirections; i++) {
          matches += futures[i].get();
        }
      }
    }
  }

  return matches;
}

int crossSearch(vector<string> rows, int direction, int y, int x) {
  string direct;
  switch (direction) {
  case 0:
    direct = "MMSS";
    break;
  case 1:
    direct = "SMMS";
    break;
  case 2:
    direct = "SSMM";
    break;
  case 3:
    direct = "MSSM";
    break;
  }
  try {
    if (rows.at(y - 1).at(x - 1) == direct[0] &&
        rows.at(y - 1).at(x + 1) == direct[1] &&
        rows.at(y + 1).at(x + 1) == direct[2] &&
        rows.at(y + 1).at(x - 1) == direct[3]) {
      return 1;
    }
  } catch (const exception &e) {
    return 0;
  }
  return 0;
}
int crossSearch(vector<string> rows, string word) {
  int matches = 0;
  int numDirections = 4;
  for (int y = 0; y < rows.size(); y++) {
    for (int x = 0; x < rows[y].size(); x++) {
      if (rows[y][x] == word[1]) {
        vector<future<int>> futures;
        for (int i = 0; i < numDirections; i++) {
          futures.push_back(async(launch::async, [rows, i, y, x]() {
            return crossSearch(rows, i, y, x);
          }));
        }
        for (int i = 0; i < numDirections; i++) {
          matches += futures[i].get();
        }
      }
    }
  }

  return matches;
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

  cout << "Matches: " << crossSearch(rows, "MAS") << "\n";
}
