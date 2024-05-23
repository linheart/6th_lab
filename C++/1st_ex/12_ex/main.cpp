#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vectors = vector<vector<int>>;

#define N 5

void out_matrix(vectors &);
int gen_rand_num();
void init(vectors &);

int main() {
  vectors matrix(N);
  init(matrix);
  out_matrix(matrix);
  return 0;
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
  uniform_int_distribution<> dis(1, 100);
  return dis(gen);
}

void init(vectors &matrix) {
  int num = 10;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < i + 1; j++) {
      matrix[i].push_back(num);
      num += 2;
    }
}
