#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  struct Thread{
    long long next_free_time;
    int index;
  };

  int leftchild(int i){
    return (2*i+1);
  }

  int rightchild(int i){
    return (2*i+2);
  }

  void siftdown(vector<Thread> &threads, int place){
    int minindex = place;
    int indexlimit = num_workers_/2;
    
    while (minindex<indexlimit){
      int l = leftchild(minindex), r = rightchild(minindex), tempmin=minindex;
      if(threads[l].next_free_time<threads[tempmin].next_free_time){
        tempmin = l;
      }
      else if(threads[l].next_free_time == threads[tempmin].next_free_time && threads[l].index<threads[tempmin].index){
        tempmin = l;
      }

      if (r<num_workers_){
        if(threads[r].next_free_time<threads[tempmin].next_free_time){
          tempmin = r;
        }
        else if(threads[r].next_free_time == threads[tempmin].next_free_time && threads[r].index<threads[tempmin].index){
          tempmin = r;
        }
      }
      if (tempmin==minindex) return;
      std::swap(threads[minindex],threads[tempmin]);
      minindex = tempmin;
    }
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<Thread> threads(num_workers_);
    
    for (int i=0; i<num_workers_;i++){
      threads[i].next_free_time = 0;
      threads[i].index = i;
    }

    for (int i = 0; i < jobs_.size(); ++i) {
      assigned_workers_[i] = threads[0].index;
      start_times_[i] = threads[0].next_free_time;
      threads[0].next_free_time += jobs_[i];
      siftdown(threads,0);
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
