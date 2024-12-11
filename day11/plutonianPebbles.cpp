#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

long part2Rules(unordered_map<long, long> &map, int blinks) {
  long size = 0;
  for (int i = 0; i < blinks; ++i) {
    unordered_map<long, long> occurences;
    size = 0;
    for (auto i : map) {
      size += i.second;
    }
    for (auto j : map) {
      stringstream num;
      num << j.first;
      string number;
      int tempSize;
      if (j.first == 0) {
        occurences[1] += j.second;
      } else if ((tempSize = (number = num.str()).size()) % 2 == 0) {
        int halfOne = stoi(number.substr(tempSize / 2));
        int halfTwo = stoi(number.substr(0, tempSize / 2));
        occurences[halfOne] += j.second;
        occurences[halfTwo] += j.second;
      } else {
        occurences[j.first * 2024] += j.second;
      }
    }
    map = occurences;
  }
  size = 0;
  for (auto i : map) {
    size += i.second;
  }
  return size;
}

void part1Rules(vector<long> &table, int blinks) {
  for (int i = 0; i < blinks; ++i) {
    int j = 0;
    int size = table.size();
    while (j < size) {
      stringstream num;
      num << table[j];
      int size;
      string number;
      if (table[j] == 0) {
        table[j] = 1;
        j++;
      } else if ((size = (number = num.str()).size()) % 2 == 0) {
        table[j] = atoi(number.substr(size / 2).c_str());
        auto pos = table.begin() + j;
        table.push_back(atoi(number.substr(0, size / 2).c_str()));
        j++;
      } else {
        table[j] *= 2024;
        j++;
      }
    }
  }
}

int main() {
  vector<long> input;

  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;

  while (getline(file, line)) {
    size_t start = 0, end;
    while ((end = line.find(' ', start)) != string::npos) {
      input.push_back(stol(line.substr(start, end - start)));
      start = end + 1;
    }
    input.push_back(stol(line.substr(start, end - start)));
  }

  file.close();

  unordered_map<long, long> map;
  for (long i : input) {
    map[i]++;
  }

  part1Rules(input, 25);
  long sizing = part2Rules(map, 75);

  cout << input.size() << endl;
  cout << sizing << endl;

  return 0;
}
