#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Solution {
public:
  bool isValid(const string& str) {
    stack<char> brackets;
    for (auto c : str) {
      switch (c) {
        case '(':
        case '[':
        case '{':
          brackets.push(c);
          break;
        case ')':
          if (brackets.empty() || brackets.top() != '(') {
            return 0;
          }
          brackets.pop();
          break;
        case ']':
          if (brackets.empty() || brackets.top() != '[') {
            return 0;
          }
          brackets.pop();
          break;
        case '}':
          if (brackets.empty() || brackets.top() != '{') {
            return 0;
          }
          brackets.pop();
          break;
      }
    }
    return brackets.empty();
  }
};

void test(const string& str) {
  Solution solution;
  auto answer = solution.isValid(str);
  clog << "[::test]: str: " << str << " answer: " << answer << endl;
}

int main() {
  test("()");
  test("");
  test("()[]{}");
  test("(]");
  test("([)]");
  test("{[]}");
}
