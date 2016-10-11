#include "bubble_sort.h"

BubbleSort::BubbleSort(std::vector<int> data) {
  this->data = data;
}

std::vector<int> BubbleSort::getData() {
  return this->data;
}

void BubbleSort::sort() {
  bool swapp = true;
  while(swapp) {
    swapp = false;

    for (int i = 0; i < this->data.size()-1; i++) {
      if (this->data[i]>this->data[i+1] ) {
        this->data[i] += this->data[i+1];
        this->data[i+1] = this->data[i] - this->data[i+1];
        this->data[i] -=this->data[i+1];
        swapp = true;
      }
    }
  }
}