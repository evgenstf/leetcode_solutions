#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  int removeDuplicates(vector<int>& numbers) {
    if (numbers.empty()) {
      return 0;
    }
    int result = 1;
    int index = 1;
    for (int i = 1; i < numbers.size(); ++i) {
      if (numbers[i] != numbers[i - 1]) {
        result++;
        numbers[index++] = numbers[i];
      }
    }
    return result;
  }
};

void test(const vector<int>& numbers) {
  Solution solution;
  auto answer = solution.removeDuplicates(numbers);
  clog << "[::test]: numbers: ";
  for (auto x : numbers) {
    clog << x << ' ';
  }
  clog << " answer: " << answer << std::endl;
}

int main() {
  test({2, 7, 11, 15});
  test({1, 1, 2});
  test({0, 0, 1, 1, 1, 2, 2, 3, 3, 4});
  test({});
}
