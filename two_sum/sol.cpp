#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  auto twoSum(const vector<int>& numbers, int target) {
    map<int, int> counts;
    for (auto c : numbers) {
      counts[c]++;
    }
    multiset<int> answer;
    for (auto c : numbers) {
      auto brother = target - c;
      counts[c]--;
      if (counts[brother] > 0) {
        answer.insert(c);
        answer.insert(brother);
        break;
      }
      counts[c]++;
    }
    vector<int> indices;
    for (int i = 0; i < numbers.size(); ++i) {
      auto it = answer.find(numbers[i]);
      if (it != answer.end()) {
        answer.erase(it);
        indices.push_back(i);
      }
    }
    return indices;
  }
};

void test(const vector<int>& numbers, int target) {
  Solution solution;
  auto answer = solution.twoSum(numbers, target);
  clog << "[::test]: numbers: ";
  for (auto x : numbers) {
    clog << x << ' ';
  }
  clog << "target: " << target << " answer: ";
  for (auto x : answer) {
    clog << x << ' ';
  }
  clog << endl;
}

int main() {
  test({2, 7, 11, 15}, 9);
  test({2, 2, 11, 15}, 4);
}
