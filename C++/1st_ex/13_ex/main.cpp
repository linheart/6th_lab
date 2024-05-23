#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

#define M 5
#define N 7

using namespace std;
using vectors = vector<vector<int>>;

void out_matrix(vectors &);
int gen_rand_num();
void init(vectors &);
void max_min_el(vectors &, vector<int> &);

int main() {
  vectors matrix(M, vector<int>(N, 0));
  vector<int> nums;
  while (nums.empty()) {
    init(matrix);
    max_min_el(matrix, nums);
  }

  out_matrix(matrix);

  for (auto it : nums)
    cout << it << ' ';
  cout << endl;
  return 0;
}

void max_min_el(vectors &matrix, vector<int> &nums) {
  for (auto i : matrix) {
    int min_in_row = *min_element(i.begin(), i.end());
    int j = find(i.begin(), i.end(), min_in_row) - i.begin();
    int row = 0;

    for (; row < M && matrix[row][j] <= i[j]; row++)
      ;

    if (row == M)
      nums.push_back(i[j]);
  }
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
  uniform_int_distribution<> dis(0, 1000);
  return dis(gen);
}

void init(vectors &matrix) {
  unordered_set<int> nums;
  while (nums.size() < M * N)
    nums.insert(gen_rand_num());

  auto it = nums.begin();

  int index = 0;
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++) {
      matrix[i][j] = *it;
      it++;
    }
}
