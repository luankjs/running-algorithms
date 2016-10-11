#include "merge_sort.h"

MergeSort::MergeSort(std::vector<int> data) {
  this->original_data = data;
}

std::vector<int> MergeSort::getOriginalData() {
  return this->original_data;
}

std::vector<int> MergeSort::getSortedData() {
  return this->sorted_data;
}

std::vector<int> MergeSort::runSort(std::vector<int>& data) {
  if(data.size() == 1) {
    return data;
  }

  std::vector<int>::iterator middle = data.begin() + (data.size() / 2);

  vector<int> left(data.begin(), middle);
  vector<int> right(middle, data.end());

  left = runSort(left);
  right = runSort(right);

  return merge(left, right);
}

std::vector<int> MergeSort::merge(const std::vector<int>& left, const std::vector<int>& right)
{
  std::vector<int> result;
  unsigned left_it = 0, right_it = 0;

  while(left_it < left.size() && right_it < right.size()) {
      if(left[left_it] < right[right_it]) {
          result.push_back(left[left_it]);
          left_it++;
      } else {
          result.push_back(right[right_it]);
          right_it++;
      }
  }

  while(left_it < left.size()) {
      result.push_back(left[left_it]);
      left_it++;
  }

  while(right_it < right.size()) {
      result.push_back(right[right_it]);
      right_it++;
  }

  return result;
}

void MergeSort::sort() {
  this->sorted_data = runSort(this->original_data);
}
