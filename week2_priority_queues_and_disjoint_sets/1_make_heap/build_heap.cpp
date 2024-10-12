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

  void GenerateSwaps() {
    swaps_.clear(); int n = data_.size();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i=n/2-1; i>=0 ;i--){
      int minindex = i;
      while(minindex<n/2){
        int l = 2*minindex+1, r=2*minindex+2, tempindex=minindex;
      
      if (data_[tempindex]>data_[l]) tempindex =l;
      if(r<n){
        if (data_[tempindex]>data_[r]) tempindex =r;
      }
      if (tempindex == minindex) break;

      swaps_.push_back(make_pair(minindex,tempindex));
      swap(data_[minindex],data_[tempindex]);
      minindex = tempindex;
      }
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
