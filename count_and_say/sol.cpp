#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
  string countAndSay(int n) {
    string now = "1";
    for (int i = 1; i < n; ++i) {
      string next;
      size_t index = 0;
      while (index < now.size()) {
        auto digit = now[index];
        auto count = 0;
        while (index < now.size() && now[index] == digit) {
          ++count;
          ++index;
        }
        next = next + to_string(count) + digit;
      }
      now.swap(next);
    }
    return now;
  }
};

void test(int n) {
  Solution solution;
  auto answer = solution.countAndSay(n);
  clog << "[::test]: n: " << n << " answer: " << answer << endl;
}

int main() {
  test(1);
  test(5);
}
