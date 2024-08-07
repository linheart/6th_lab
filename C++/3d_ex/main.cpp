#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
using vectors = vector<vector<double>>;

vectors matrix = {{-0.77, -0.04, 0.21, -18.0, -1.24},
                  {0.25, -1.23, 0.16, -0.09, 1.12},
                  {-0.21, 0.16, 0.80, -0.13, 2.56},
                  {0.15, -1.31, 0.06, 1.12, -0.77}};

#define MATRIX_SIZE matrix.size()

vector<double> gaussian_elim();
void forward_elim(vectors &);
size_t find_main_el(const vectors &, const size_t);
vector<double> back_sub(const vectors &);

int main() {
  vector<double> res = gaussian_elim();
  for (auto it : res) {
    cout << it << ' ';
  }
  return 0;
}

vector<double> gaussian_elim() {
  vectors matrix_copy = matrix;
  forward_elim(matrix_copy);
  cout << "Forward elimination:" << endl;
  for (auto i : matrix_copy) {
    for (auto j : i) {
      cout << j << ' ';
    }
    cout << endl;
  }
  return back_sub(matrix_copy);
}

void forward_elim(vectors &matrix) {
  for (size_t j = 0; j < MATRIX_SIZE - 1; j++) {
    size_t i = find_main_el(matrix, j);
    if (i != j) {
      matrix[j].swap(matrix[i]);
    }

    for (size_t row = j + 1; row < MATRIX_SIZE; row++) {
      double tmp = matrix[row][j] / matrix[j][j];
      for (size_t col = j; col < MATRIX_SIZE + 1; col++) {
        matrix[row][col] -= tmp * matrix[j][col];
      }
    }
  }
}

size_t find_main_el(const vectors &matrix, const size_t index) {
  size_t max_el_index = index;
  for (size_t i = index; i < MATRIX_SIZE; i++) {
    if (fabs(matrix[i][index]) > fabs(matrix[max_el_index][index])) {
      max_el_index = i;
    }
  }
  return max_el_index;
}

vector<double> back_sub(const vectors &matrix) {
  vector<double> xn(MATRIX_SIZE, 0.);
  for (int i = MATRIX_SIZE - 1; i >= 0; i--) {
    double sum = 0.;
    for (int j = i + 1; j < MATRIX_SIZE; j++) {
      sum += matrix[i][j] * xn[j];
    }
    xn[i] = (matrix[i][MATRIX_SIZE] - sum) / matrix[i][i];
    cout << "x" << i + 1 << " = " << xn[i] << endl;
  }
  return xn;
}