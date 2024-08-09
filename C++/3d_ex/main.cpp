#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;
using vectors = vector<vector<double>>;

const double EPS = 1e-3;

vector<double> gaussian_elim(const vectors &);
void forward_elim(vectors &);
size_t find_main_el(const vectors &, const size_t);
vector<double> back_sub(const vectors &);
void print_canonical_form(const vectors &, const vector<double> &);
bool check_diagonal_dominance(const vectors &A);
void simple_iterations(const vectors &, const vector<double> &, int);
void print_matrix(const vectors &);

int main() {
  vectors matrix = {{-0.77, -0.04, 0.21, -18.0, -1.24},
                    {0.25, -1.23, 0.16, -0.09, 1.12},
                    {-0.21, 0.16, 0.80, -0.13, 2.56},
                    {0.15, -1.31, 0.06, 1.12, -0.77}};

  vector<double> res = gaussian_elim(matrix);

  vectors A = {{-0.77, -0.04, 0.21, -18.0},
               {0.25, -1.23, 0.16, -0.09},
               {-0.21, 0.16, 0.80, -0.13},
               {0.15, -1.31, 0.06, 1.12}};
  vector<double> b = {-1.24, 1.12, 2.56, -0.77};
  print_canonical_form(A, b);

  if (!check_diagonal_dominance(A)) {
    cout << "\nThe system does not converge" << endl;
  }

  cout << "\nN" << setw(10) << "x1" << setw(10) << "x2" << setw(10) << "x3"
       << setw(10) << "x4" << setw(10) << "εn" << endl;

  simple_iterations(A, b, 10);
  return 0;
}

vector<double> gaussian_elim(const vectors &matrix) {
  vectors matrix_copy = matrix;
  cout << "Forward elimination:" << endl;
  forward_elim(matrix_copy);
  print_matrix(matrix_copy);
  cout << "\nBack substitution:\n";
  return back_sub(matrix_copy);
}

void forward_elim(vectors &matrix) {
  size_t n = matrix.size();
  for (size_t j = 0; j < n - 1; j++) {
    size_t i = find_main_el(matrix, j);

    if (i != j) {
      matrix[j].swap(matrix[i]);
    }

    for (size_t row = j + 1; row < n; row++) {
      double tmp = matrix[row][j] / matrix[j][j];
      for (size_t col = j; col < n + 1; col++) {
        matrix[row][col] -= tmp * matrix[j][col];
      }
    }
  }
}

size_t find_main_el(const vectors &matrix, const size_t index) {
  size_t n = matrix.size();
  size_t max_el_index = index;
  for (size_t i = index; i < n; i++) {
    if (fabs(matrix[i][index]) > fabs(matrix[max_el_index][index])) {
      max_el_index = i;
    }
  }
  return max_el_index;
}

vector<double> back_sub(const vectors &matrix) {
  size_t n = matrix.size();
  vector<double> xn(n, 0.);
  for (int i = n - 1; i >= 0; i--) {
    double sum = 0.;
    for (int j = i + 1; j < n; j++) {
      sum += matrix[i][j] * xn[j];
    }
    xn[i] = (matrix[i][n] - sum) / matrix[i][i];
    cout << "x" << i + 1 << " = " << xn[i] << endl;
  }
  return xn;
}

void print_canonical_form(const vectors &A, const vector<double> &b) {
  size_t n = A.size();
  cout << "\nCanonical form:" << endl;
  for (size_t i = 0; i < n; i++) {
    cout << "x" << i + 1 << " = ";
    bool first = true;
    for (size_t j = 0; j < n; ++j) {
      if (i != j) {
        double coef = -A[i][j] / A[i][i];
        if (!first && coef >= 0) {
          cout << "+ ";
        } else if (coef < 0) {
          cout << "-";
          if (!first) {
            cout << ' ';
          }
        }
        cout << fixed << setprecision(3) << fabs(coef) << 'x' << j + 1 << ' ';
        first = false;
      }
    }
    double const_term = b[i] / A[i][i];
    if (const_term >= 0) {
      cout << "+ " << const_term;
    } else {
      cout << "- " << fabs(const_term);
    }
    cout << endl;
  }
}

bool check_diagonal_dominance(const vectors &A) {
  size_t n = A.size();
  bool isDominant = true;

  for (size_t i = 0; i < n; ++i) {
    double diag = fabs(A[i][i]);
    double sum = 0.0;
    for (size_t j = 0; j < n; ++j) {
      if (i != j) {
        sum += fabs(A[i][j]);
      }
    }
    if (diag <= sum) {
      isDominant = false;
    }
  }
  return isDominant;
}

void simple_iterations(const vectors &A, const vector<double> &b,
                       int max_iterations) {
  size_t n = A.size();
  double diff = 1.;
  vector<double> x(n, 0.0);
  vector<double> x_new(n);

  for (size_t iter = 0; iter < max_iterations && diff > EPS; ++iter) {
    for (size_t i = 0; i < n; i++) {
      double sum = b[i];
      for (size_t j = 0; j < n; j++) {
        if (i != j) {
          sum -= A[i][j] * x[j];
        }
      }
      x_new[i] = sum / A[i][i];
    }

    for (size_t i = 0; i < n; i++) {
      if (fabs(x_new[i] - x[i]) > diff) {
        diff = fabs(x_new[i] - x[i]);
      }
    }

    x = x_new;

    cout << iter + 1;
    for (size_t i = 0; i < n; i++) {
      cout << fixed << setprecision(3) << setw(10) << x[i];
    }
    cout << setw(10) << diff << endl;
  }
}

void print_matrix(const vectors &matrix) {
  for (auto i : matrix) {
    for (auto j : i) {
      cout << j << ' ';
    }
    cout << endl;
  }
}