/*
	Compute height of a given tree. Height of a rooted tree is
	the maximum depth of a node, or the maximum distance from a
	leaf to the root. Input needn't be a binary tree.
	Idea if to apply breadth-first search using queue and add
	a sentinel value (-1) to signal a change of level. Sentinel
	is only added to the queue when the previous one is extracted.

	Input: first line contains number of nodes, n.
		   second line contains n integer numbers from -1 to n - 1
		   which are parents of nodes. If the ith one is -1, node i 
		   is the root otherwise it's the 0-base index of the parent
		   of the ith node. It is guaranted that there is exactly one
		   root and that input represents a tree.
		   1 <= n <= 10^5
	Output: output the height of the tree.
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::queue;

struct Node {
	int key;
	int parent;
};

int tree_height(vector<vector<Node> > tree, int root) {
	if (tree.empty()) return 0;

	queue<int> q;
	q.push(root);
	// Add first sentinel value
	q.push(-1);
	int node = root;
	int height = 1;
	while (!q.empty()) {
		node = q.front();
		// Queue only contains the sentinel value
		if (q.size() == 1 && q.front() == -1) return height;
		if (node == -1) {
			height++;
			q.push(-1);
			q.pop();
			node = q.front();		
		}
		// Remove item from queue
		q.pop();
		if (!tree[node].empty()) {
			for (int i = 0; i < tree[node].size(); i++) {
				q.push(tree[node][i].key);
			}
		}	
	}
	height--;
	return height;
}


int main() {
  std::ios_base::sync_with_stdio(0);
  // Number of nodes to consider
  int n;
  std::cin >> n;
  int root = 0;
  Node temp;
  // Tree structure
  vector<vector<Node> > tree(n);
  for (int i = 0; i < n; i++) {
  	int parent;
  	std::cin >> parent;
  	if (parent == -1) {
  		root = i;
  	} else {
  		temp.key = i;
  		temp.parent = parent;
  		tree[parent].push_back(temp);
  	}
  }
  std::cout << tree_height(tree, root) << std::endl;
  return 0;
}