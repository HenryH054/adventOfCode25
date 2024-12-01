#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

void merge(std::vector<int> &lyst, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++) {
    L[i] = lyst[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = lyst[mid + 1 + j];
  }

  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      lyst[k++] = L[i++];
    } else {
      lyst[k++] = R[j++];
    }
  }

  while (i < n1) {
    lyst[k++] = L[i++];
  }
  while (j < n2) {
    lyst[k++] = R[j++];
  }
}

void mergeSort(std::vector<int> &lyst, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  mergeSort(lyst, left, mid);
  mergeSort(lyst, mid + 1, right);
  merge(lyst, left, mid, right);
}

int compareVector(std::vector<int> &l1, std::vector<int> &l2) {
  int dlt = 0;
  for (int i = 0; i < l1.size() && i < l2.size(); i++) {
    dlt += abs(l1[i] - l2[i]);
  }
  return dlt;
}

int similarityScore(std::vector<int> &l1, std::vector<int> &l2) {
  int x = 0, j = 0, acc = 0, score = 0;
  while (x < l1.size() && j < l1.size()) {
    if (l1[x] > l2[j]) {
      j++;
    } else if (l1[x] == l2[j]) {
      acc++;
      j++;
    } else if (l1[x] < l2[j]) {
      score += l1[x] * acc;
      x++;
      if (l1[x - 1] != l1[x]) {
        acc = 0;
      }
    }
  }
  return score;
}

int main() {
  std::vector<int> l1, l2;

  std::ifstream file("input");

  if (!file) {
    std::cerr << "This file don't exist dweeb" << std::endl;
    return 1;
  }

  std::string line;

  while (getline(file, line)) {
    size_t delim_pos = line.find("  ");

    std::string v1 = line.substr(0, delim_pos);
    std::string v2 = line.substr(delim_pos + 3);

    l1.push_back(std::stoi(v1));
    l2.push_back(std::stoi(v2));
  }

  file.close();

  int n1 = l1.size();
  int n2 = l2.size();
  mergeSort(l1, 0, n1 - 1);
  mergeSort(l2, 0, n2 - 1);
  std::cout << "Difference in ID: " << compareVector(l1, l2)
            << "\nSimilarity in ID: " << similarityScore(l1, l2) << "\n";
  return 0;
}
