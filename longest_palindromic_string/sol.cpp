#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  auto longestPalindrome(const string& str) {
    string answer;
    for (int i = 0; i < str.size(); ++i) {
      int half_len = 0;
      for (; i - half_len >= 0 && i + half_len < str.size(); ++half_len) {
        if (str[i - half_len] != str[i + half_len]) {
          break;
        }
      }
      --half_len;
      if (answer.size() < half_len * 2 + 1) {
        answer = str.substr(i - half_len, half_len * 2 + 1);
      }
    }
    for (int i = 0; i < int(str.size()) - 1; ++i) {
      int half_len = 0;
      for (; i - half_len >= 0 && i + half_len + 1 < str.size(); ++half_len) {
        if (str[i - half_len] != str[i + 1 + half_len]) {
          break;
        }
      }
      --half_len;
      if (answer.size() < half_len * 2 + 2) {
        answer = str.substr(i - half_len, half_len * 2 + 2);
      }
    }
    return answer;
  }
};

void test(const string& str) {
  Solution solution;
  auto answer = solution.longestPalindrome(str);
  clog << "[::test]: str: " << str << " answer: " << answer << endl;
}

int main() {
  test("babad");
  test("cbbd");
  test("");
  test("s");
  test("abccba");
}
