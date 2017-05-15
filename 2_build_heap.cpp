/*
  Convert an array into a heap using O(N) swaps.
  Idea is to repair the heap property starting after the
  leaves by calling sift down to each element. We repair
  the property as we go up the tree, ensuring the lower
  trees are heaps before we reach higher trees.

  Input:  
         1 <= n <= 100000; 0 <= i, j <= n-1; 
         0 <= a0, a1, ..., an <= 10^9. All are distinct.
  Output: first line of the output contains a single integer
          m (total number of swaps) where 0 <= m <= 4n
          The next m lines contain the swap operations used
          to convert the array into a heap.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int parent(int i) {
    return (i-1)/2;
  }

  int leftChild(int i) {
    return 2*i + 1;
  }

  int rightChild(int i) {
    return 2 * (i+1);
  }

  void siftDown(int i) {
    int minIndex = i;
    int left = leftChild(i);
    int size = data_.size();
    if ((left < size) && data_[left] < data_[minIndex]) {
      minIndex = left;
    }
    int right = rightChild(i);
    if (right < size && data_[right] < data_[minIndex]) {
      minIndex = right;
    }
    if (i != minIndex) {
      std::pair <int,int> swapped;
      swapped = std::make_pair (i,minIndex);
      swaps_.push_back(swapped);
      swap(data_[i], data_[minIndex]);
      siftDown(minIndex);
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    int size = data_.size();
    // Starts in the middle of the array and 
    // down to element at index 0 since the 
    // trees rooted at leaves are heaps already.
    for (int i = size/2; i >= 0; i--) {
      siftDown(i);
    }
  }
  

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
