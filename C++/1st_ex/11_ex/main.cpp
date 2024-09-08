#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vectors = vector<vector<int>>;

#define M 5
#define N 6

void out_matrix(vectors &);
int gen_rand_num();
void init(vectors &);
bool is_prime(int);
int find_max_prime(vectors &);

int main() {
  vectors matrix(M, vector<int>(N, 0));
  init(matrix);
  out_matrix(matrix);
  int res = find_max_prime(matrix);

  if (res) {
    cout << res << endl;
  } else {
    cout << "There's no prime nums" << endl;
  }
  return 0;
}

bool is_prime(int num) {
  if (num == 2 || num == 3 || num == 5 || num == 7) {
    return true;
  }
  if (num < 2 || num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) {
    return false;
  }
  return true;
}

int find_max_prime(vectors &matrix) {
  vector<int> prime_nums(48, 0);
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) {
      if (is_prime(matrix[i][j])) prime_nums[matrix[i][j]]++;
    }
  }

  int max_count = *max_element(prime_nums.begin(), prime_nums.end());
  auto it = find(prime_nums.begin(), prime_nums.end(), max_count);

  if (it != prime_nums.end()) {
    return it - prime_nums.begin();
  }

  return 0;
}

void out_matrix(vectors &matrix) {
  for (auto row : matrix) {
    for (auto column : row) {
      cout << column << ' ';
    }
    cout << endl;
  }
}

int gen_rand_num() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, 50);
  return dis(gen);
}

void init(vectors &matrix) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = gen_rand_num();
    }
  }
}
