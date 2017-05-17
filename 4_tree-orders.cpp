/*
  Traverse binary tree using in-order, pre-order and post-order traversals.

  Input: first line contains the number of vertices n (vertices are numbered
         from 0 to n-1 and vertex 0 is the root). The next 𝑛 lines contain 
         information about vertices 0, 1, ..., 𝑛−1 in order. Each of these lines
         contains three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖 and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖-th
         vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left child of the 𝑖-th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖
         is the index of the right child of the 𝑖-th vertex. If 𝑖 doesn’t left or 
         right child (or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 (or both) will be 
         equal to −1.
  Output: Print three lines. The first line should contain the keys of the 
          vertices in the in-order traversal of the tree. The second line should
          contain the keys of the vertices in the pre-order traversal of the tree.
          The third line should contain the keys of the vertices in the post-order 
          traversal of the tree.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order_traversal(int root, vector<int> &result) {
    // No left or right branches left to explore
    if (left[root] == -1 && right[root] == -1) {
      result.push_back(key[root]);
      return;
    }
    // Explore left branch
    if (left[root] != -1) {
      in_order_traversal(left[root], result);
    }
    // Print
    result.push_back(key[root]);
    // Explore right branch
    if (right[root] != -1) {
      in_order_traversal(right[root], result); 
    }
  }

  vector <int> in_order() {
    vector<int> result;
    in_order_traversal(0, result);
    return result;
  }

  void pre_order_traversal(int root, vector<int> &result) {
    // No left or right branches left to explore
    if (left[root] == -1 && right[root] == -1) {
      result.push_back(key[root]);
      return;
    }
    // Print
    result.push_back(key[root]);
    // Explore left branch
    if (left[root] != -1) {
      pre_order_traversal(left[root], result);
    }
    // Explore right branch
    if (right[root] != -1) {
      pre_order_traversal(right[root], result);
    }
  }

  vector <int> pre_order() {
    vector<int> result;    
    pre_order_traversal(0, result);
    return result;
  }

  void post_order_traversal(int root, vector<int> &result) {
    // No left or right branches left to explore
    if (left[root] == -1 && right[root] == -1) {
      result.push_back(key[root]);
      return;
    }
    // Explore left branch
    if (left[root] != -1) {
      post_order_traversal(left[root], result);
    }
    // Explore right branch
    if (right[root] != -1) {
      post_order_traversal(right[root], result);
    }
    // Print
    result.push_back(key[root]);
  }

  vector <int> post_order() {
    vector<int> result;
    post_order_traversal(0, result);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

