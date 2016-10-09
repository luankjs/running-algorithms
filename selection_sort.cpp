#include "selection_sort.h"

SelectionSort::SelectionSort(std::vector<int> data) {
  this->original_data = data;
}

std::vector<int> SelectionSort::getOriginalData() {
  return this->original_data;
}

std::vector<int> SelectionSort::getSortedData() {
  return this->sorted_data;
}

void SelectionSort::sort() {
  this->sorted_data = this->original_data;

  for( std::vector<int>::iterator it = this->sorted_data.begin(); it != this->sorted_data.end()-1; ++it )
  {
    std::iter_swap( it, std::min_element( it, this->sorted_data.end() ) );
  }
}