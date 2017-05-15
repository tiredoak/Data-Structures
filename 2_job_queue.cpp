/*
  Simulate a program which is parallelized and uses n independent
  threads to process the given list of m jobs.

  Input: first line contains integers n and m.
         second line contains m integers ti - the times in seconds
         it takes any thread to process the ith job.
         The times are given in the same order as they are in the list
         from which threads take jobs. Threads are indexed starting at
         0.
         1 <= n <= 10^5; 1 <= m <= 10^5; 0 <= ti <= 10^9
  Output: output exactly m lines. i-th line (0-based index)
          should contain two space separated integers - the
          0-based index of the thread which will process the
          i-th job and the time in seconds when it will start
          processing that job.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::pair;

struct pair_compare {
  bool operator()(const std::pair<int,long long> &a, const std::pair<int,long long> &b) {
    int thread_a = std::get<0>(a);
    int thread_b = std::get<0>(b);
    long long start_a = std::get<1>(a);
    long long start_b = std::get<1>(b);
    return (start_a > start_b) || ((start_a == start_b) && (thread_a > thread_b));
  }
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  // Priority queue for threads
  std::priority_queue<pair<int,long long>,vector<pair<int,long long> >, pair_compare> thread_store;
  

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> jobs_[i];
    // Create priority queue
    for (int i = 0; i < num_workers_; i++) {
      thread_store.push(std::make_pair(i, 0));
    }
  }

  void AssignJobs() {
    int jobs_size = jobs_.size();
    for (int i = 0; i < jobs_size; i++) {
      // Log the threads and start times
      std::pair<int, long long> thread_pair = thread_store.top();
      int thread = thread_pair.first;
      long long start_time = thread_pair.second;
      assigned_workers_.push_back(thread);
      start_times_.push_back(start_time);
      // Remove the thread
      thread_store.pop();
      // Add again with new start time
      start_time += jobs_[i];
      thread_store.push(std::make_pair(thread, start_time));
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
