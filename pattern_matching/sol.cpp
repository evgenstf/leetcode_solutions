#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
  bool isMatch(const std::string& line, const std::string& pattern) const {
    if (!prefix_and_suffix_match(line, pattern)) {
      return false;
    }
    auto splitted_pattern = split_pattern(pattern);
    size_t position = 0;
    for (const auto& pattern_part : splitted_pattern) {
      position = find(line, pattern_part, position);
      if (position == std::string::npos) {
        return false;
      }
      position += pattern_part.size();
    }
    // std::clog << "position: " << position << " line.size() : " << line.size() << std::endl;
    return pattern.back() == '*' || (position == line.size() || splitted_pattern.size() != 1);
  }

private:
  bool prefix_and_suffix_match(const std::string& line, const std::string& pattern) const {
    for (size_t i = 0; i < pattern.size() && pattern[i] != '*'; ++i) {
      if (i >= line.size() || (pattern[i] != '.' && line[i] != pattern[i])) {
        return false;
      }
    }
    for (size_t i = 0; i < pattern.size() && pattern[pattern.size() - i - 1] != '*'; ++i) {
      if (
          i >= line.size() ||
          (
            pattern[pattern.size() - i - 1] != '.' &&
            line[line.size() - i - 1] != pattern[pattern.size() - i - 1]
          )
      ) {
        return false;
      }
    }
    return true;
  }

  std::vector<std::string> split_pattern(const std::string& pattern) const {
    std::vector<std::string> result;
    for (size_t i = 0; i < pattern.size(); ++i) {
      std::string pattern_part;
      while (i < pattern.size() && pattern[i] != '*') {
        pattern_part.push_back(pattern[i++]);
      }
      if (!pattern_part.empty()) {
        result.push_back(std::move(pattern_part));
      }
    }
    return result;
  }

  size_t find(
      const std::string& line,
      const std::string& pattern_part,
      size_t start_position
  ) const {
    for (size_t line_position = start_position; line_position < line.size(); ++line_position) {
      bool match = true;
      for (
          size_t pattern_part_position = 0;
          pattern_part_position < pattern_part.size();
          ++pattern_part_position
      ) {
        if (
            line_position + pattern_part_position >= line.size() ||
            (
             pattern_part[pattern_part_position] != line[line_position + pattern_part_position] &&
              pattern_part[pattern_part_position] != '.'
            )
        ) {
          match = false;
          break;
        }
      }
      if (match) {
        return line_position;
      }
    }
    return std::string::npos;
  }
};

void test(const std::string& line, const std::string pattern, bool expected_answer) {
  Solution solution;
  auto answer = solution.isMatch(line, pattern);
  std::clog << "[::test]: line: " << line <<
      " pattern: " << pattern <<
      " answer: " << (answer ? "true" : "false") << std::endl;
  if (expected_answer != answer) {
    std::clog << "FAILED!\n";
  }
}

int main() {
  test("aaa", "*", true);
  test("aaa", "a*a", true);
  test("aaa", "a*.a", true);
  test("aaa", "a.a", true);
  test("aaa", "..", false);
  test("aaa", "...", true);
  test("aaa", "..*", true);
  test("aaa", "*a*", true);
  test("aaa", "*b*", false);
  test("aaa", "*...*", true);
  test("aaa", "*....*", false);
  test("aaa", "....", false);
}
