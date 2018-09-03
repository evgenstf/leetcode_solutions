#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  auto longestCommonPrefix(const vector<string>& strings) {
    if (strings.empty()) {
      return string();
    }
    string common_prefix = strings.front();
    for (const auto& str : strings) {
      int i = 0;
      for (; i < min(str.size(), common_prefix.size()); ++i) {
        if (str[i] != common_prefix[i]) {
          break;
        }
      }
      while (common_prefix.size() > i) {
        common_prefix.pop_back();
      }
    }
    return common_prefix;
  }
};

void test(const vector<string>& strings) {
  Solution solution;
  auto answer = solution.longestCommonPrefix(strings);
  clog << "[::test]: string: ";
  for (auto str : strings) {
    clog << str << ' ';
  }
  clog << "answer: " << answer;
  clog << endl;
}

int main() {
  test({"flower", "flow", "flight"});
  test({"dog", "racecar", "car"});
  test({});
}
