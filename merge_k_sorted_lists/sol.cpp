#include <optional>
#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*> lists) { 
    ListNode* head = nullptr;
    ListNode* previous_node = nullptr;
    auto next_node_index = get_minimal_node_index(lists);
    while (next_node_index.has_value()) {
      auto* next_node = lists[next_node_index.value()];
      lists[next_node_index.value()] = next_node->next;
      if (!head) {
        head = next_node;
      }
      if (previous_node) {
        previous_node->next = next_node;
      }
      previous_node = next_node;
      next_node_index = get_minimal_node_index(lists);
    }
    return head;
  }

private:
  std::optional<size_t> get_minimal_node_index(const vector<ListNode*>& nodes) {
    std::optional<size_t> result = std::nullopt;
    for (size_t i = 0; i < nodes.size(); ++i) {
      if (
          nodes[i] &&
          (!result.has_value() || nodes[i]->val < nodes[result.value()]->val)
      ) {
        result = i;
      }
    }
    return result;
  }
};



void print_list(ListNode* head) {
  while (head) {
    clog << head->val << " -> ";
    head = head->next;
  }
  clog << "NULL\n";
}

void test(const vector<ListNode*>& lists) {
  Solution solution;
  clog << "[::test]:" << endl;
  for (const auto& node : lists) {
    clog << "  ";
    print_list(node);
  }
  auto answer = solution.mergeKLists(lists);
  clog << "answer: ";
  print_list(answer);
}

auto generate_list(const vector<int> &numbers) {
  ListNode* head = new ListNode(numbers.back());
  for (int i = numbers.size() - 2; i >= 0; --i) {
    ListNode* new_head = new ListNode(numbers[i]);
    new_head->next = head;
    head = new_head;
  }
  return head;
}

int main() {
  test(
    {
      generate_list({1, 2, 3}),
      generate_list({2, 2, 2})
    }
  );
}
