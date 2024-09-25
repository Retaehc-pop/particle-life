#include "forceMatrix.hpp"
#include <random>

ForceMatrix::ForceMatrix(int n) : size(n) {
  values.resize(n, std::vector<double>(n, 0));
};

void ForceMatrix::fill_zero() {
  for (auto &row : values) {
    for (auto &val : row) {
      val = 0;
    }
  }
}

void ForceMatrix::fill_random() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for (auto &row : values) {
    for (auto &val : row) {
      val = dist(mt);
    }
  }
}

void ForceMatrix::set(int row, int col, double value) {
  values[row][col] = value;
}

double ForceMatrix::get(int row, int col) { return values[row][col]; }

ForceMatrix ForceMatrix::deepCopy() {
  ForceMatrix fm(size);
  fm.values = values;
  return fm;
}
