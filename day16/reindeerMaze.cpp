#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

// from S check which directions are valid to start, go that way
// from the start go in a straight line adding one to a score per 
long solveMap(vector<string> &maze) {
  map<array<int, 2>, long> score;
  long start[2], end[2];
  for (int i = 0; i < maze.size(); ++i) {
    for (int j = 0; j < maze[i].size(); ++j) {
      if (maze[i][j] == 'S') {
        start[0] = i;
        start[1] = j;
      } else if (maze[i][j] == 'E') {
        end[0] = i;
        end[1] = j;
      }
    }
  }
  return 0;
}

int main() {

  ifstream file("input2");
  if (!file) {
    cerr << "File DNE" << endl;
  }
  vector<string> input;
  string line;
  while (getline(file, line)) {
    input.push_back(line);
  }
  file.close();

  for (string &i : input) {
    cout << i << endl;
  }

  solveMap(input);

  return 0;
}
