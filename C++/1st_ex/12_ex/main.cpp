#include <iostream>
#include <vector>

using namespace std;
using vectors = vector<vector<int>>;

void out_matrix(vectors &);
void init(vectors &, int);
void under_diag(vectors &);
void above_diag(vectors &, int, int);

int main() {
  int N;
  cin >> N;
  vectors matrix(N, vector<int>(N, 0));
  init(matrix, N);
  out_matrix(matrix);
  return 0;
}

void out_matrix(vectors &matrix) {
  for (auto row : matrix) {
    for (auto column : row) {
      if (column == 0)
        cout << "000 ";
      else
        cout << column << ' ';
    }
    cout << endl;
  }
}

void under_diag(vectors &matrix, int i, int N) {
  for (int row = i + 1; row < N; row++)
    matrix[row][i] = 100 + i;
}

void above_diag(vectors &matrix, int i, int N) {
  for (int row = 0; row < i; row++)
    matrix[row][i] = 100 + N - 1 - i;
}

void init(vectors &matrix, int N) {
  for (int i = 0, j = 0; i < N; i++, j++) {
    under_diag(matrix, i, N);
    above_diag(matrix, i, N);
  }
}
