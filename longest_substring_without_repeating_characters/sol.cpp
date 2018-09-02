#include <iostream>
#include <set>
#include <string>

using namespace std;

class Solution {
public: 
  int lengthOfLongestSubstring(const string& str) {
    set<char> chars;
    size_t l = 0;
    size_t r = 0;
    size_t ans = 0;
    while (r < str.size()) {
      while (chars.find(str[r]) != chars.end()) {
        chars.erase(str[l++]);
      }
      chars.insert(str[r++]);
      ans = max(ans, r - l);
    }
    return ans;
  }
};

void test(const string& str) {
  Solution solution;
  auto answer = solution.lengthOfLongestSubstring(str);
  clog << "[::test]: str: " << str << " answer: " << answer << endl;
}

int main() {
  test("abcabcbb");
  test("bbbbb");
  test("pwwkew");
  test("");
  test("a");
}
