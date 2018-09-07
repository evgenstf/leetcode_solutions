#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  auto convert(const string& str, int rows_count) {
    string answer;
    if (rows_count == 0 || str.empty()) {
      return answer;
    }
    size_t str_index = 0; 
    int column = 0;
    vector<vector<char>> dt(rows_count, vector<char>(str.size(), '\0'));
    while (str_index < str.size()) {
      int i = 0;
      int j = column;
      while (str_index < str.size() && i < rows_count) {
        dt[i][j] = str[str_index++];
        ++i;
      }
      ++j;
      i = rows_count - 2;
      while (str_index < str.size() && i > 0) {
        dt[i][j] = str[str_index++];
        --i;
        ++j;
      }
      column = j;
    }
    for (const auto& row : dt) {
      for (auto c : row) {
        if (c != '\0') {
          answer.push_back(c);
        }
      }
    }
    return answer;
  }
};

void test(const string& str, int rows_count) {
  Solution solution;
  auto answer = solution.convert(str, rows_count);
  clog << "[::test]: str: " << str << " rows_count: " << rows_count <<
      " answer: " << answer << endl;
}

int main() {
  test("", 3);
  test("A", 1);
  test("AB", 1);
  test("PAYPALISHIRING", 3);
  test("PAYPALISHIRING", 4);
}
