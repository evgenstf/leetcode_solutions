#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  bool isPalindrome(int x) {
    auto str = to_string(x);
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] != str[str.size() - i - 1]) {
        return false;
      }
    }
    return true;
  }
};

void test(int x) {
  Solution solution;
  auto answer = solution.isPalindrome(x);
  clog << "[::test]: x: " << x << " answer: " << answer << endl;
}

int main() {
  test(121);
  test(-121);
  test(10);
}
