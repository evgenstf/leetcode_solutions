#include <iostream>
#include <vector>

using namespace std;

class Solution {
public: 
  double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    auto A = nums1;
    auto B = nums2;
    if (A.size() < B.size()) {
      A = nums2;
      B = nums1;
    }
    if (B.empty()) {
      return (A[A.size() / 2] + A[(A.size() - 1) / 2]) / 2.0;
    }
    int half_len = (A.size() + B.size() + 1) / 2;
    // clog << "A.size(): " << A.size() << " B.size(): " << B.size() << " half_len: " << half_len << endl;
    int l = half_len - B.size() - 1;
    int r = half_len + 1;
    while (l + 1 < r) {
      int a_index = (l + r) / 2;
      int b_index = half_len - a_index - (A.size() + B.size()) % 2;
      b_index = min(b_index, int(B.size()));
      clog << "l: " << l << " r: " << r << " a_index: " << a_index << " b_index: " << b_index << endl;
      if (a_index < A.size() && b_index > 0 && A[a_index] < B[b_index - 1]) {
        l = a_index;
        continue;
      }
      if (b_index < B.size() && a_index > 0 && B[b_index] < A[a_index - 1]) {
        r = a_index;
        continue;
      }
      break;
    }
    int a_index = (l + r) / 2;
    int b_index = half_len - a_index - (A.size() + B.size()) % 2;
    clog << "l: " << l << " r: " << r << " a_index: " << a_index << " b_index: " << b_index << endl;
    if ((A.size() + B.size()) % 2) {
      /*
      if (b_index == 0) {
        return A[a_index - 1];
      }
      if (a_index == 0) {
        return B[b_index - 1];
      }
      return max(A[a_index - 1], B[b_index - 1]);
      */
      if (b_index >= B.size()) {
        return A[a_index];
      }
      if (a_index >= A.size()) {
        return B[b_index];
      }
      return min(A[a_index], B[b_index]);
    } else {
      int left = -1000000000;
      int right = 1000000000;
      if (a_index > 0) {
        left = A[a_index - 1];
      }
      if (b_index > 0) {
        left = max(left, B[b_index - 1]);
      }
      if (a_index < A.size()) {
        right = A[a_index];
      }
      if (b_index < B.size()) {
        right = min(right, B[b_index]);
      }
      return (left + right) / 2.0;
    }
  }

private:
  std::pair<const vector<int>&, const vector<int>&> sort_vectors_by_size(
      const vector<int>& left, const vector<int>& right) {
    if (left.size() > right.size()) {
      return make_pair(left, right);
    } else {
      return make_pair(right, left);
    }
  }
};

void test(Solution& solution, const vector<int>& A, const vector<int>& B) {
  clog << "[::test]:\n";
  clog << "  A: ";
  for (auto x : A) {
    clog << x << ' ';
  }
  clog << "\n";
  clog << "  B: ";
  for (auto x : B) {
    clog << x << ' ';
  }
  clog << "\n";
  clog << "  answer: " << solution.findMedianSortedArrays(A, B) << "\n";
}

int main() {
  Solution solution;
  test(solution, {1, 3}, {2});
  test(solution, {1}, {2, 3, 4, 5, 6, 7, 8});
  test(solution, {1}, {2, 3});
  test(solution, {1, 2}, {-1, 3});
  test(solution, {1}, {2, 3, 4, 5, 6, 7});
  test(solution, {1, 2}, {3, 4});
}
