#pragma once

#include <vector>

class ForceMatrix {
public:
  ForceMatrix(int size);
  const int size;
  std::vector<std::vector<double>> values;
  void fill_zero();
  void fill_random();
  void set(int row, int col, double value);
  double get(int row, int col);
  ForceMatrix deepCopy();
};
