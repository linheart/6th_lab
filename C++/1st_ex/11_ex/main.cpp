#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vectors = vector<vector<int>>;

#define M 10
#define N 10

void mult_el(vector<int> &, vectors);
void out_matrix(vectors &);
int gen_rand_num();
void init(vectors &);

int main() {
  vectors matrix(M);
  vector<int> arr(N, 1);

  init(matrix);
  out_matrix(matrix);

  mult_el(arr, matrix);
  cout << endl;
  for (auto it : arr)
    cout << it << ' ';
  cout << endl;
  return 0;
}

void mult_el(vector<int> &arr, vectors matrix) {
  for (int column = 0; column < N; column++)
    for (int row = 0; row < M; row++)
      arr[column] *= matrix[row][column];
}

void out_matrix(vectors &matrix) {
  for (auto row : matrix) {
    for (auto column : row)
      cout << column << ' ';
    cout << endl;
  }
}

int gen_rand_num() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 10);
  return dis(gen);
}

void init(vectors &matrix) {
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      matrix[i].push_back(gen_rand_num());
}
