#include <iostream>
#include <limits>

using namespace std;

class Solution {
public:
  int reverse(int x) {
    if (x == 0) {
      return 0;
    }
    int sgn = x / abs(x);
    x = abs(x);
    long long result = 0;
    while (x) {
      result *= 10;
      result += x % 10;
      x /= 10;
    }
    if (result < numeric_limits<int>::min() || numeric_limits<int>::max() < result) {
      return 0;
    }
    return result * sgn;
  }
};

void test(int x) {
  Solution solution;
  auto answer = solution.reverse(x);
  clog << "[::test]: x: " << x << " answer: " << answer << endl;
}

int main() {
  test(123);
  test(-123);
  test(120);
  test(0);
  test(1534236469);
}
