#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <csignal>
#include "merge_sort.h"
#include "selection_sort.h"
#include "bubble_sort.h"

using namespace std;

pid_t id;

std::vector<int> generateRandomArray(int size) {
  std::vector<int> vector;

  srand((unsigned)time(0));

  for (int i = 0; i < size; ++i) {
    int number = rand() % (size*10);

    vector.push_back(number);
  }

  return vector;
}

void handleTimeout(int sig) {
  switch (id) {
    case -1:
      exit(1);
    case 0:
      cout << "Entrada muito grande! Tente algo menor." << endl;
      kill(getppid(), SIGKILL);
      exit(1);
    default:
      cout << "Entrada muito grande! Tente algo menor." << endl;
      kill(id, SIGKILL);
      exit(1);
  }
}

int main(int argc, char* argv[]) {
  std::vector<int> input;
  std::vector<int> data;

  if (argc != 2) {
    cout << "Você não inseriu os parâmetros corretamente." << endl;
    cout << "Exemplo: ./RunningAlgorithms 10" << endl;
    exit(1);
  }

  int size_of_array = atoi(argv[1]);
  
  signal(SIGALRM, handleTimeout);

  input = generateRandomArray(size_of_array);

  id = fork();

  MergeSort merge = MergeSort(input);
  BubbleSort bubble = BubbleSort(input);
  
  switch (id) {
    case -1:
      exit(1);
    case 0:
      alarm(15);
      merge.runSort();
      cout << "MergeSort foi mais rápido!!" << endl;
      kill(getppid(), SIGKILL);
      exit(1);
    default:
      alarm(15);
      bubble.sort();
      cout << "BubbleSort foi mais rápido!!" << endl;
      kill(id, SIGKILL);
      exit(1);
  }
}