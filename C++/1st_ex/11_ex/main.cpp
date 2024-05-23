#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vectors = vector<vector<int>>;

#define M 5
#define N 5

void out_matrix(vectors &);
int gen_rand_num();
void init(vectors &);
bool is_prime(int);
int find_max_prime(vectors &);

int main() {
  vectors matrix(M, vector<int>(N, 0));

  init(matrix);
  out_matrix(matrix);
	cout << find_max_prime(matrix) << endl;

  return 0;
}

bool is_prime(int num) {
  if (num <= 1 || num % 2 == 0 || num % 3 == 0)
    return false;
  if (num <= 3)
    return true;

  for (int i = 5; i < sqrt(num); i += 6)
    if (num % i == 0 || num % (i + 2) == 0)
      return false;
  return true;
}

int find_max_prime(vectors &matrix) {
	vector<int> prime_nums(47, 0);
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++) {
			if (is_prime(matrix[i][j]))
				prime_nums[matrix[i][j]]++;
		}
	int max_count = *max_element(prime_nums.begin(), prime_nums.end());

	int i = 0;
	for (; prime_nums[i] != max_count; i++)
		;

	return i;
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
  uniform_int_distribution<> dis(0, 50);
  return dis(gen);
}

void init(vectors &matrix) {
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
			matrix[i][j] = gen_rand_num();
}
