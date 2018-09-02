#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  int romanToInt(const string& roman_number) {
    int result = 0;
    size_t index = 0;
    while (index < roman_number.size()) {
      if (index + 1 < roman_number.size()) {
        if (roman_number[index] == 'I' && roman_number[index + 1] == 'V') {
          index += 2;
          result += 4;
          continue;
        }
        if (roman_number[index] == 'I' && roman_number[index + 1] == 'X') {
          index += 2;
          result += 9;
          continue;
        }
        if (roman_number[index] == 'X' && roman_number[index + 1] == 'L') {
          index += 2;
          result += 40;
          continue;
        }
        if (roman_number[index] == 'X' && roman_number[index + 1] == 'C') {
          index += 2;
          result += 90;
          continue;
        }
        if (roman_number[index] == 'C' && roman_number[index + 1] == 'D') {
          index += 2;
          result += 400;
          continue;
        }
        if (roman_number[index] == 'C' && roman_number[index + 1] == 'M') {
          index += 2;
          result += 900;
          continue;
        }
      }
      switch (roman_number[index]) {
        case 'I':
          result += 1;
          break;
        case 'V':
          result += 5;
          break;
        case 'X':
          result += 10;
          break;
        case 'L':
          result += 50;
          break;
        case 'C':
          result += 100;
          break;
        case 'D':
          result += 500;
          break;
        case 'M':
          result += 1000;
          break;
      }
      ++index;
    }
    return result;
  }
};

void test(const string& roman_number) {
  Solution solution;
  auto answer = solution.romanToInt(roman_number);
  clog << "[::test]: roman_number: " << roman_number << " answer: " << answer << endl;
}

int main() {
  test("III");
  test("IV");
  test("IX");
  test("LVIII");
  test("MCMXCIV");
}
