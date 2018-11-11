#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
  int removeElement(vector<int>& nums, int val) {
    int i = 0;
    int j = 0;
    while (j < nums.size()) {
      while (i < nums.size() && nums[i] != val) {
        ++i;
      }
      j = i + 1;
      while (j < nums.size() && nums[j] == val) {
        ++j;
      }
      if (j < nums.size()) {
        nums[i] = nums[j];
        nums[j] = val;
        ++i;
      }
    }
    return i;
  }
};

void test(vector<int> nums, int val) {
  clog << "val: " << val << " nums: ";
  for (auto x : nums) {
    clog << x << ' ';
  }
  clog << endl;
  Solution solution;
  auto length = solution.removeElement(nums, val);
  clog << "result: length: " << length << " nums: ";
  for (auto x : nums) {
    clog << x << ' ';
  }
  clog << endl;
  clog << endl;
}

int main() {
  test({1, 2, 3}, 1);
  test({1, 1, 1}, 1);
  test({3, 2, 2, 3}, 3);
  test({0,1,2,2,3,0,4,2}, 2);
  test({2}, 3);
}
