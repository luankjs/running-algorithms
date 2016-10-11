#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <cstdlib>
#include <cstdio>

using namespace std;

class BubbleSort{
  private:
    std::vector<int> data;

  public:
    BubbleSort(std::vector<int> data);
    std::vector<int> getData();
    void sort();
};

#endif