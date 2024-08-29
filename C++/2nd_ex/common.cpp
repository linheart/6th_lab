#include "common.h"
#include <cmath>

void print_matricies_hex(const two_d_matrix &key, const three_d_matrix &text) {
  for (auto row : key) {
    for (auto col : row) {
      cout << hex << static_cast<int>(col) << ' ';
    }
    cout << "\n";
  }

  cout << endl;
  for (auto block : text) {
    for (auto row : block) {
      for (auto col : row) {
        cout << hex << static_cast<int>(col) << ' ';
      }
      cout << endl;
    }
    cout << endl;
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
two_d_matrix init_key_matrix(const string &input_key) {
  two_d_matrix key(Nk, vector<unsigned char>(Nb, 0));
  for (int i = 0; i < Nk; i++) {
    for (int j = 0; j < Nb; j++) {
      key[j][i] = input_key[i * 4 + j];
    }
  }
  return key;
}

three_d_matrix init_text_matrix(const string &input_text) {
  size_t blocks = static_cast<size_t>(ceil(input_text.size() / 16.));
  three_d_matrix state(blocks, two_d_matrix(Nb, vector<unsigned char>(4, 0)));
  size_t size = input_text.size();
  size_t index = 0;

  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      for (size_t col = 0; col < Nb && index < size; col++) {
        state[i][col][row] = input_text[index++];
      }
    }
  }

  if (size % Nb) {
    state[blocks - 1][3][Nb - 1] = static_cast<unsigned char>(size);
  }
  return state;
}

void key_exp(const two_d_matrix &key, three_d_matrix &ext_keys) {
  ext_keys.push_back(key);
  two_d_matrix state;
  vector<unsigned char> tmp(Nb);

  for (size_t rnd = 1; rnd <= Nr; rnd++) {
    state = ext_keys[rnd - 1];

    for (size_t i = 0; i < Nb; i++) {
      tmp[i] = state[(i + 1) % 4][Nb - 1];
      tmp[i] = s_box[tmp[i] / 16][tmp[i] % 16];
      tmp[i] ^= r_con[rnd - 1][i];
    }

    for (size_t i = 0; i < Nb; i++) {
      state[i][0] ^= tmp[i];
    }
    for (size_t col = 1; col < Nb; col++) {
      for (size_t row = 0; row < Nb; row++) {
        state[row][col] ^= state[row][col - 1];
      }
    }
    ext_keys.push_back(state);
  }
}

void xor_matricies(const two_d_matrix &round_key, three_d_matrix &state) {
  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      for (size_t col = 0; col < Nb; col++) {
        state[i][row][col] ^= round_key[row][col];
      }
    }
  }
}
