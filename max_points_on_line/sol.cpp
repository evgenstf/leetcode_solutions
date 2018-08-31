#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Point {
  int x, y;
};


const long double eps = 1e-19;
const long double inf = 1e18;

struct Line {
  long double k, b;
};

bool operator<(const Line& left, const Line& right) {
  if (left.k + eps < right.k) {
    return true;
  }
  if (left.k - eps > right.k) {
    return false;
  }
  return left.b + eps < right.b;
}

bool operator<(const Point& left, const Point& right) {
  return make_pair(left.x, left.y) < make_pair(right.x, right.y);
}

class Solution {
public: 
  int maxPoints(const vector<Point>& points) {
    for (const auto& point : points) {
      ++point_count_[point];
    }
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = i + 1; j < points.size(); ++j) {
        process_points_pair(points[i], points[j]);
      }
    }
    int ans = min(1, int(points.size()));
    for (const auto& line_and_points_pairs : points_pairs_by_line_) {
      int local_ans = 0;
      //clog << "line: k: " << line_and_points_pairs.first.k <<
      //    " b: " << line_and_points_pairs.first.b <<
      //    " points_count: " << line_and_points_pairs.second.size() << endl;
      //clog << "points: ";
      for (const auto& point : line_and_points_pairs.second) {
      //  clog << "(" << point.x << ", " << point.y << ") ";
        local_ans += point_count_[point];
      }
//      clog << endl;
//      clog << endl;
      ans = max(ans, local_ans);
    }
    return ans;
  }

private:
  void process_points_pair(const Point& left, const Point& right) {
    Line line = line_by_points_pair(left, right);
//    clog.precision(20);
 //   clog << "add line: k: " << fixed << line.k << " b: " << line.b << endl;
 //   clog << "points: (" << left.x << ", " << left.y << ") (" <<
 //     right.x << ", " << right.y << ")\n\n";
    points_pairs_by_line_[line].insert(left);
    points_pairs_by_line_[line].insert(right);
  }

  Line line_by_points_pair(const Point& left, const Point& right) {
    if (abs(left.x - right.x) < eps) {
      return {inf, (long double)left.x};
    }
    long double k = static_cast<long double>(right.y - left.y) / static_cast<long double>(right.x - left.x);
    long double b = static_cast<long double>(right.y) - static_cast<long double>(right.x * k); 
    return {k, b};
  }

  map<Line, set<Point>> points_pairs_by_line_;
  map<Point, int> point_count_;
};

void test(const vector<Point>& points) {
  Solution solution;
  clog << "[::test]:\n";
  clog << "  points ";
  for (auto point : points) {
    clog << '(' << point.x << ' ' << point.y << ") ";
  }
  clog << "\n";
  auto answer = solution.maxPoints(points);
  clog << "  answer: " << answer << "\n";
}

int main() {
  test({{0,0},{94911151,94911150},{94911152,94911151}});
  /*
  test({{0,9},{138,429},{115,359},{115,359},{-30,-102},{230,709},{-150,-686},{-135,-613},{-60,-248},{-161,-481},{207,639},{23,79},{-230,-691},{-115,-341},{92,289},{60,336},{-105,-467},{135,701},{-90,-394},{-184,-551},{150,774}});
  test({{0,-12},{5,2},{2,5},{0,-5},{1,5},{2,-2},{5,-4},{3,4},{-2,4},{-1,4},{0,-5},{0,-8},{-2,-1},{0,-11},{0,-9}});
  test({{3, 10}, {0, 2}, {0, 2}, {3, 10}});
  test({{3, 10}, {3, 10}, {0, 2}, {0, 2}});
  test({{1, 1}, {1, 1}});
  test({{1, 1}, {2, 2}, {3, 3}});
  test({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}});
  */
}
