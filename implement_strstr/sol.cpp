#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  int strStr(const string& haystack, const string& needle) {
    auto position = haystack.find(needle);
    return position == string::npos ? -1 : position;
  }
};

void test(const string& haystack, const string& needle) {
  Solution solution;
  clog << "[::test]:\n";
  clog << "  haystack: " << haystack << " needle: " << needle;
  clog << "\n";
  auto answer = solution.strStr(haystack, needle);
  clog << "  answer: " << answer << "\n";
}

int main() {
  test("hello", "ll");
  test("aaaaaa", "bba");
}
