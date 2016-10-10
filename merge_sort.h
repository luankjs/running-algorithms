#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

class MergeSort{
  private:
    std::vector<int> original_data;
    std::vector<int> sorted_data;

  public:
    MergeSort(std::vector<int> data);
    std::vector<int> getOriginalData();
    std::vector<int> getSortedData();
    std::vector<int> sort(std::vector<int>& data);
    std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right);
    void runSort();
};

#endif