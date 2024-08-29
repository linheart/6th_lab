#include "common.h"

void print_text(three_d_matrix &text) {
  size_t blocks = text.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t j = 0; j < Nb; j++) {
      for (size_t k = 0; k < Nb; k++) {
        cout << text[i][k][j];
      }
    }
  }
  cout << endl;
}

string init_key() {
  string key;

  while (true) {
    cout << "Input a key with a maximum length of 16 characters: ";
    getline(cin, key);

    if (key.size() > 16) {
      cout << "The length exceeds the allowed value" << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
  size_t size = input_key.size();
  size_t index = 0;
  for (size_t i = 0; i < Nk; i++) {
    for (size_t j = 0; j < Nb && index < size; j++) {
      key[j][i] = input_key[index++];
    }
  }
  if (size < 4 * Nb) {
    key[3][Nb - 1] = 1;
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
