#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void fileLayout(vector<string> &files, string &diskMap) {
  bool file = true;
  size_t id = 0;
  for (char &i : diskMap) {
    for (size_t j = 0; j < (i - '0'); ++j) {
      if (file) {
        files.push_back(to_string(id));
      } else {
        files.push_back(".");
      }
    }
    if (file) {
      ++id;
    }
    file = !file;
  }
}

long fragment(string &diskMap) {
  long checksum = 0;
  vector<string> fragmented;
  fileLayout(fragmented, diskMap);

  size_t start = 0, end = fragmented.size() - 1;
  do {
    while (fragmented[end] == ".") {
      --end;
    }
    if (fragmented[start] == ".") {
      fragmented[start] = fragmented[end];
      fragmented[end] = ".";
    }
    ++start;
  } while (start < end);

  for (size_t i = 0; i < end + 1; ++i) {
    checksum += i * stol(fragmented[i]);
  }

  return checksum;
}

long optFragment(string &diskMap) {
  long checksum = 0;
  vector<string> frag;
  fileLayout(frag, diskMap);
  size_t fragSize = frag.size(), endIndex = fragSize, startIndex;
  string muteIndex = diskMap;

  for (size_t i = diskMap.size() - 1; i > 0; i -= 2) {
    size_t fileLength = diskMap[i] - '0';
    endIndex -= fileLength;
    if (i + 1 < diskMap.size()) {
      endIndex -= diskMap[i + 1] - '0';
    }
    startIndex = 0;
    for (size_t j = 1; j <= i; j += 2) {
      startIndex += diskMap[j - 1] - '0';
      if (fileLength <= muteIndex[j] - '0') {
        muteIndex[j] -= fileLength;
        while (frag[startIndex] != ".") {
          startIndex++;
        }
        for (size_t k = 0; k < fileLength; k++) {
          frag[startIndex + k] = frag[endIndex + k];
          frag[endIndex + k] = ".";
        }
        break;
      }
      startIndex += diskMap[j] - '0';
    }
  }

  for (size_t i = 0; i < fragSize; ++i) {
    if (frag[i] == ".") {
      continue;
    }
    checksum += i * stoi(frag[i]);
  }
  return checksum;
}

int main() {
  ifstream file("input");

  if (!file) {
    cerr << "This file don't exist dweeb\n";
    return 1;
  }

  string line;
  getline(file, line);
  file.close();

  cout << optFragment(line);

  return 0;
}
