#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

uint64_t orConcat(vector<int64_t> &nums) {
  size_t size = nums.size() - 2;
  size_t ops[size];
  for (size_t i = 0; i < size; i++) {
    ops[i] = 0;
  }
  for (size_t j = 0; j < pow(3, size + 1); j++) {
    long answer = nums[1];
    for (size_t i = 2; i < nums.size(); i++) {
      if (ops[i - 2] == 0) {
        answer += nums[i];
      } else if (ops[i - 2] == 1) {
        answer *= nums[i];
      } else {
        stringstream ss;
        ss << answer << nums[i];
        ss >> answer;
      }
    }
    size_t carry = 1;
    for (size_t k = 0; k < size; ++k) {
      ops[k] += carry;
      if (ops[k] == 3) {
        ops[k] = 0;
        carry = 1;
      } else {
        carry = 0;
        break;
      }
    }
    if (answer == nums[0]) {
      return nums[0];
    }
  }

  return 0;
}

uint64_t addOrMultiply(vector<int64_t> &nums) {
  size_t size = nums.size() - 2;
  for (size_t j = 0; j < 1 << size; j++) {
    size_t iteration = j;
    long answer = nums[1];
    for (size_t i = 2; i < nums.size(); i++) {
      if (iteration & 1) {
        answer *= nums[i];
      } else {
        answer += nums[i];
      }
      iteration >>= 1;
    }
    if (answer == nums[0]) {
      return nums[0];
    }
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

  uint64_t sumPt1 = 0, countPt1 = 0, sumPt2 = 0, countPt2 = 0;
  for (int i = 0; i < rows.size(); i++) {
    size_t start = 0, end;
    vector<int64_t> row;
    while ((end = rows[i].find(' ', start)) != string::npos) {
      row.push_back(stol(rows[i].substr(start, end - start)));
      start = end + 1;
    }
    row.push_back(stol(rows[i].substr(start, end - start)));

    uint64_t pt1 = 0, pt2 = 0;
    if ((pt1 = addOrMultiply(row))) {
      countPt1++;
      countPt2++;
    } else if ((pt2 = orConcat(row))) {
      countPt2++;
    } else {
    }
    sumPt1 += pt1;
    sumPt2 += pt1 + pt2;
  }
  cout << "Part 1:\nSummation: " << sumPt1 << "\nCorrect: " << countPt1
       << "\nPart 2:\nSummation:" << sumPt2 << "\nCorrect: " << countPt2;

  return 0;
}
