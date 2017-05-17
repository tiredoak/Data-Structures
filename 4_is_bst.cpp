/*
  Given a binary tree with integers as its keys, test whether it is a correct 
  binary search tree.

  Input: The first line contains the number of vertices 𝑛. The vertices of the 
         tree are numbered from 0 to 𝑛 − 1. Vertex 0 is the root.
         The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order.
         Each of these lines contains three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖 and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the
         key of the 𝑖-th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left child of the 𝑖-th 
         vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖-th vertex. If 𝑖 
         doesn’t have left or right child (or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 
         (or both) will be equal to −1.
  Output: If the given binary tree is a correct binary search tree (see the 
          definition in the problem description), output one word “CORRECT” (without
          quotes). Otherwise, output one word “INCORRECT” (without quotes).
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool is_valid(const vector<Node>& tree, int root, long long min, long long max) {
  // Empty trees are correct
  if (tree.size() == 0) return true;
  // Leaf node
  if (tree[root].left == -1 && tree[root].right == -1 &&
      tree[root].key < max && tree[root].key > min) {
    return true;
  }
  if (tree[root].key > min && tree[root].key < max) {
    // If there are no left branches or right branches we assume true
    bool left = true, right = true;
    if (tree[root].left != -1) {
      left = false;
      left = is_valid(tree, tree[root].left, min, tree[root].key);
    }
    if (tree[root].right != -1) {
      right = false;
      right = is_valid(tree, tree[root].right, tree[root].key, max);
    }
    if (left && right) return true;
  }
  return false;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  // No infinity in long long so this is used given problem
  // constraints
  return is_valid(tree, 0, -10000000000, 10000000000);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
