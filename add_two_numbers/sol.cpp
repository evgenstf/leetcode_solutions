#include <iostream>
#include <limits>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  auto addTwoNumbers(ListNode* l1, ListNode* l2) {
    auto answer_head = new ListNode(l1->val + l2->val);
    auto answer_index = answer_head;
    l1 = l1->next;
    l2 = l2->next;
    while (l1 || l2) {
      answer_index->next = new ListNode(0);
      answer_index = answer_index->next;
      if (l1) {
        answer_index->val += l1->val;
        l1 = l1->next;
      }
      if (l2) {
        answer_index->val += l2->val;
        l2 = l2->next;
      }
    }
    answer_index = answer_head;
    while (answer_index) {
      if (answer_index->val >= 10) {
        if (!answer_index->next) {
          answer_index->next = new ListNode(0);
        }
        answer_index->next->val += answer_index->val / 10;
        answer_index->val %= 10;
      }
      answer_index = answer_index->next;
    }
    return answer_head;
  }
};

void print_number(ListNode* head) {
  while (head) {
    clog << head->val << " -> ";
    head = head->next;
  }
  clog << "NULL\n";
}

void test(ListNode* l1, ListNode* l2) {
  Solution solution;
  clog << "[::test]:" << endl;
  clog << "l1: ";
  print_number(l1);
  clog << "l2: ";
  print_number(l2);
  auto answer = solution.addTwoNumbers(l1, l2);
  clog << "answer: ";
  print_number(answer);
}

auto generate_number(const string&& number) {
  ListNode* head = new ListNode(number.back() - '0');
  auto tail = head;
  for (int i = number.size() - 2; i >= 0; --i) {
    tail->next = new ListNode(number[i] - '0');
    tail = tail->next;
  }
  return head;
}

int main() {
  test(generate_number("1"), generate_number("9999"));
}
