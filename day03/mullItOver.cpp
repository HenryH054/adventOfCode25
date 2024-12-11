#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> Match(vector<string> &row, regex pattern) {
  smatch match;
  vector<string> matches;

  for (string x : row) {
    string::const_iterator searchStart(x.cbegin());

    while (regex_search(searchStart, x.cend(), match, pattern)) {
      matches.push_back(match[0]);
      searchStart = match.suffix().first;
    }
  }
  return matches;
}

vector<string> Match(string row, regex pattern) {
  smatch match;
  vector<string> matches;

  string::const_iterator searchStart(row.cbegin());

  while (regex_search(searchStart, row.cend(), match, pattern)) {
    matches.push_back(match[0]);
    searchStart = match.suffix().first;
  }
  return matches;
}

int main() {
  vector<string> row;

  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;

  while (getline(file, line)) {
    row.push_back(line);
  }

  file.close();

  // Part 1 of Advent of Code
  regex pattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
  vector<string> matches = Match(row, pattern);
  int sum = 0;
  for (string i : matches) {
    regex digits("[0-9]{1,3}");
    vector<string> nums = Match(i, digits);
    sum += stoi(nums[0]) * stoi(nums[1]);
  }
  cout << "Part 1: " << sum;

  // Part 2 of Advent of Code
  pattern = ("(mul\\([0-9]{1,3},[0-9]{1,3}\\))|(do\\(\\))|(don't\\(\\))");
  matches = Match(row, pattern);
  sum = 0;
  bool flag = true;
  for (string i : matches) {
    if (i == "do()") {
      flag = true;
    } else if (i == "don't()") {
      flag = false;
    } else if (flag) {
      regex digits("[0-9]{1,3}");
      vector<string> nums = Match(i, digits);
      sum += stoi(nums[0]) * stoi(nums[1]);
    }
  }
  cout << "\nPart 2: " << sum << "\n";

  return 0;
}
