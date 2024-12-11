#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
int confirmRule(unordered_map<int, vector<int>> &hash, vector<int> &row) {
  for (int i = 0; i < row.size(); i++) {
    for (int j = 0; j < row.size(); j++) {
      if (j == i) {
        continue;
      }
      for (int x : hash[row[i]]) {
        if (row[j] == x && j < i) {
          return 0;
        }
      }
    }
  }
  return row.at(row.size() / 2);
}

int updateByRule(unordered_map<int, vector<int>> &hash, vector<int> &row) {
  for (int i = 0; i < row.size(); i++) {
    for (int j = 0; j < row.size(); j++) {
      if (j == i) {
        continue;
      }
      for (int x : hash[row[i]]) {
        if (row[j] == x && j < i) {
          int temp = row[j];
          row[j] = row[i];
          row[i] = temp;
          updateByRule(hash, row);
        }
      }
    }
  }
  return row.at(row.size() / 2);
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

  size_t queue;
  unordered_map<int, vector<int>> hashMap;
  for (int i = 0; i < rows.size(); i++) {
    if (rows[i] == "") {
      queue = i;
      break;
    }
    size_t delimit = rows[i].find('|');
    int val1 = stoi(rows[i].substr(0, delimit));
    int val2 = stoi(rows[i].substr(delimit + 1));
    hashMap[val1].push_back(val2);
  }

  size_t correct = 0, changed = 0;
  int val;
  for (int i = queue + 1; i < rows.size(); i++) {
    size_t start = 0, end;
    vector<int> row;
    while ((end = rows[i].find(',', start)) != string::npos) {
      row.push_back(stoi(rows[i].substr(start, end - start)));
      start = end + 1;
    }
    row.push_back(stoi(rows[i].substr(start, end - start)));
    if (!(val = confirmRule(hashMap, row))) {
      changed += updateByRule(hashMap, row);
    }
    correct += val;
  }
  cout << "Amount Correct: " << correct;
  cout << "\nMiddles of Altered: " << changed;
}
