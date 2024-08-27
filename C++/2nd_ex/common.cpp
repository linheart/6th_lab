#include "common.h"
#include "decrypt.h"
#include "encrypt.h"
#include <algorithm>
#include <ios>
#include <limits>

void print_matricies_hex(const two_d_matrix &key, const three_d_matrix &text) {
  for (auto row : key) {
    for (auto col : row) {
      cout << hex << static_cast<int>(col) << ' ';
    }
    cout << "\n";
  }
}
void print_hex(const string &text) {
  for (auto symbol : text) {
    cout << hex << static_cast<int>(symbol) << ' ';
  }
}

string init_key() {
  string key;

  while (true) {
    cout << "Input a key with a maximum length of 16 characters: ";
    getline(cin, key);

    if (key.size() > 16) {
      cout << "The length exceeds the allowed value" << endl;
      /*cin.ignore(numeric_limits<streamsize>::max(), '\n');*/
      continue;
    }
    return key;
  }
}

string init_text() {
  string text;
  cout << "Input a plaintext: ";
  getline(cin, text);
  return text;
}
pair<two_d_matrix, three_d_matrix> init_matricies(const string &input_key,
                                                  const string &input_text) {
  two_d_matrix key(Nk, vector<unsigned char>(Nb, 0));
  three_d_matrix text(input_text.size() + 1,
                      two_d_matrix(Nb, vector<unsigned char>(4, 0)));

  for (int i = 0; i < Nk; i++) {
    for (int j = 0; j < Nb; j++) {
      key[j][i] = input_key[i * 4 + j];
    }
  }

  return {key, text};
}

void key_exp(two_d_matrix &key) {
  vector<unsigned char> tmp(Nb);
  transform(key.begin(), key.end(), tmp.begin(),
            [](const vector<unsigned char> &row) { return row[0]; });

  for (size_t i = 0; i < Nb; i++) {
    key[i][0] =
        s_box[key[(i + 1) % 4][Nb - 1] / 16][key[(i + 1) % 4][Nb - 1] % 16];
    key[i][0] ^= r_con[0][i];
    key[i][0] ^= tmp[i];
  }

  for (size_t i = 0; i < Nb; i++) {
    for (size_t j = 1; j < Nb; j++) {
      key[i][j] = key[i][j - 1] ^ key[i][j];
    }
  }
}
