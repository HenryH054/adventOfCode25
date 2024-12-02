#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int checkRow(std::vector<int> nums) {
  int skip = -1;
  bool ascend;

  if (nums[0] - nums[1] > 0) {
    ascend = true;
  } else if (nums[0] - nums[1] < 0) {
    ascend = false;
  } else {
    skip = 1;
    return skip;
  }

  for (int j = 1; j <= nums.size() - 1; j++) {
    int dlt = nums[j - 1] - nums[j];
    if ((dlt <= 0 || dlt > 3) && ascend) {
      skip = j;
      break;
    } else if ((dlt >= 0 || dlt < -3) && !ascend) {
      skip = j;
      break;
    }
  }
  return skip;
}

int checkRow(std::vector<int> nums, int i) {
  nums.erase(nums.begin() + i);
  return checkRow(nums);
}

int safeOrUnsafe(std::vector<std::vector<int>> vals) {
  int totSafe = 0;
  for (std::vector<int> i : vals) {
    if (!checkRow(i)) {
      totSafe++;
    }
  }

  return totSafe;
}

int safeOrUnsafeDampened(std::vector<std::vector<int>> &vals) {
  int totSafe = 0;
  for (std::vector<int> i : vals) {
    int j = checkRow(i);
    if (j >= 0) {
      if (checkRow(i, j) < 0) {
        totSafe++;
      } else if (checkRow(i, j - 1) < 0) {
        totSafe++;
      } else if (j-1 == 1 && checkRow(i, 0) < 0) {
        totSafe++;
      }
    } else {
      totSafe++;
    }
  }

  return totSafe;
}

int main() {
  std::vector<std::vector<int>> row;

  std::ifstream file("input");

  if (!file) {
    std::cerr << "This file don't exist dweeb" << std::endl;
    return 1;
  }

  std::string line;

  while (getline(file, line)) {
    std::istringstream iss(line);
    int number;
    std::vector<int> val;
    while (iss >> number) {
      val.push_back(number);
    }
    row.push_back(val);
  }

  std::cout << "Safe rows: " << safeOrUnsafe(row) << "\n";
  std::cout << "Safe rows With Dampening: " << safeOrUnsafeDampened(row)
            << "\n";
  file.close();

  return 0;
}
