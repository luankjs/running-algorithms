#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

class SelectionSort{
   private:
      std::vector<int> original_data;
      std::vector<int> sorted_data;

   public:
      SelectionSort(std::vector<int> data);
      std::vector<int> getOriginalData();
      std::vector<int> getSortedData();
      void sort();
};

#endif