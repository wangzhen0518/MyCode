#include <time.h>

#include <fstream>
#include <iostream>
#include <random>

int main() {
  using namespace std;
  string filename("test_file");
  ofstream fout(filename);
  int n = 100;
  int min = 10;
  int max = 100;
  fout << n << endl;

  srand(time(nullptr));
  for (int i = 0; i < n; i++) fout << rand() % (max - min + 1) + min << endl;
  return 0;
}