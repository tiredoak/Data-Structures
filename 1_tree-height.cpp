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
	q.push(-1);
	int node = root;
	int height = 1;
	while (!q.empty()) {
		node = q.front();
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