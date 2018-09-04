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
  auto mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* head = next_min(l1, l2);
    ListNode* tail = head;
    while (tail) {
      tail->next = next_min(l1, l2);
      tail = tail->next;
    }
    return head;
  }

private:
  ListNode* next_min(ListNode*& l1, ListNode*& l2) {
    if ((!l1 && l2) || (l1 && l2 && l2->val < l1->val)) {
      auto answer = new ListNode(l2->val);
      l2 = l2->next;
      return answer;
    } else if ((l1 && !l2) || (l1 && l2 && l1->val <= l2->val)) {
      auto answer = new ListNode(l1->val);
      l1 = l1->next;
      return answer;
    }
    return NULL;
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
  auto answer = solution.mergeTwoLists(l1, l2);
  clog << "answer: ";
  print_number(answer);
}

auto generate_number(const string&& number) {
  ListNode* head = new ListNode(number.front() - '0');
  auto tail = head;
  for (int i = 1; i < number.size(); ++i) {
    tail->next = new ListNode(number[i] - '0');
    tail = tail->next;
  }
  return head;
}

int main() {
  test(generate_number("124"), generate_number("134"));
  test(generate_number("12345"), generate_number("139"));
  test(NULL, NULL);
}
