#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <string> 

using namespace std;

class Solution {
public:
  int myAtoi(string ss) {
    vector<char> str(ss.begin(), ss.end());
    reverse(str.begin(), str.end());
    while (!str.empty() && str[str.size() - 1] == ' ') {
      str.pop_back();
    }
    long long answer = 0;
    long long sgn = 1;
    while (!str.empty() && (str[str.size() - 1] == '-' || str[str.size() - 1] == '+')) {
      if (str[str.size() - 1] == '-') {
        sgn *= -1;
        str.pop_back();
        break;
      }
      if (str[str.size() - 1] == '+') {
        sgn *= 1;
        str.pop_back();
        break;
      }
    }
    reverse(str.begin(), str.end());
    for (auto c : str) {
      if (c < '0' || '9' < c) {
        break;
      }
      answer *= 10;
      answer += c - '0';
      if (answer * sgn < std::numeric_limits<int>::min()) {
        return std::numeric_limits<int>::min();
      }
      if (answer * sgn > std::numeric_limits<int>::max()) {
        return std::numeric_limits<int>::max();
      }
    }
    return answer * sgn;
  }
};

void test(string str) {
  Solution solution;
  auto answer = solution.myAtoi(str);
  clog << "[::test]: str: " << str << " answer: " << answer << endl;
}

int main() {
  test("123");
  test("-42");
  test("+1");
  test("-+1");
  test("--1");
  test("+-2");
}
