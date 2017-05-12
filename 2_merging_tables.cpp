#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		// Find parent
		std::vector<int> updates;
		while (this->sets[table].parent != table) {
			updates.push_back(table);
			table = sets[table].parent;
		}
		for (int i = 0; i < updates.size(); i++) {
			this->sets[updates[i]].parent = table;
		}
		return table;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			// merge two components
			this->sets[realDestination].size += this->sets[realSource].size;
			this->sets[realSource].size = 0;
			// use union by rank heuristic
			while (source != getParent(source)) {
				this->sets[source].parent = realDestination;
				source = getParent(source);
			}
			this->sets[realSource].parent = realDestination;
            // update max_table_size
            max_table_size = (max_table_size > this->sets[realDestination].size) ? max_table_size : this->sets[realDestination].size;
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	std::vector<int> maxs;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
		--destination;
        --source;
		
		tables.merge(destination, source);
	    maxs.push_back(tables.max_table_size);
	}

	for (int i = 0; i < maxs.size(); i++) {
		std::cout << maxs[i] << std::endl;
	}

	return 0;
}
