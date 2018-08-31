#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool isMatch(const string& str, const string& pattern) {
    if (str.empty()) {
        for (auto c : pattern) {
            if (c != '*') {
                return false;
            }
        }
        return true;
    }
    vector<vector<bool>> dp(pattern.size() + 1, vector<bool>(str.size() + 1));
    dp[0][0] = true; 
    for (size_t i = 1; i < pattern.size() + 1; ++i) {
        for (size_t j = 1; j < str.size() + 1; ++j) {
          if (pattern[i - 1] == '?' || pattern[i - 1] == str[j - 1]) {
            dp[i][j] = dp[i - 1][j - 1];
          }
          if (pattern[i -  1] == '*') {
            dp[i][j] = dp[i - 1][j - 1] | dp[i][j - 1] | dp[i - 1][j];
            dp[i][0] = dp[i - 1][0];
          }
        }
    }
    /*
    for (size_t i = 0; i < pattern.size() + 1; ++i) {
      for (size_t j = 0; j < str.size() + 1; ++j) {
        clog << dp[i][j] << " \n"[j == str.size()];
      }
    }
    */
    return dp[pattern.size()][str.size()];
  }
};

void test(Solution& solution, const string& str, const string& pattern) {
  cout << "[::test]: str: " << str << " pattern: " << pattern <<
      " answer: " << (solution.isMatch(str, pattern) ? "true" : "false") << endl;
}

int main() {
  Solution solution;
  test(solution, "", "*");
  test(solution, "aa", "a");
  test(solution, "aa", "*");
  test(solution, "cb", "?a");
  test(solution, "adceb", "*a*b");
  test(solution, "acdcb", "*a*c?b");
  cout << "____________\n";
  test(solution, "aabcd", "?a??*");
  test(solution, "aabcd", "?a??*");
  test(solution, "aabcd", "?a???*");
  test(solution, "aabcd", "?a????*");
}
