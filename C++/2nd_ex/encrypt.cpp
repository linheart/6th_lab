#include "encrypt.h"
#include "common.h"

void sub_bytes(three_d_matrix &state) {
  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      for (size_t col = 0; col < Nb; col++) {
        state[i][row][col] =
            s_box[state[i][row][col] / 16][state[i][row][col] % 16];
      }
    }
  }
}

void shift_left(three_d_matrix &state) {
  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      rotate(state[i][row].begin(), state[i][row].begin() + row,
             state[i][row].end());
    }
  }
}

void mix_columns(three_d_matrix &state) {
  size_t blocks = state.size();
  vector<unsigned char> col(Nb);
  vector<unsigned char> tmp(Nb);

  for (size_t i = 0; i < blocks; i++) {
    for (size_t j = 0; j < Nb; j++) {
      for (size_t k = 0; k < Nb; k++) {
        col[k] = state[i][k][j];
        tmp[k] = (state[i][k][j] << 1);
        if (state[i][k][j] & 0x80) {
          tmp[k] ^= 0x1B;
        }
      }

      state[i][0][j] = tmp[0] ^ col[1] ^ tmp[1] ^ col[2] ^ col[3];
      state[i][1][j] = col[0] ^ tmp[1] ^ col[2] ^ tmp[2] ^ col[3];
      state[i][2][j] = col[0] ^ col[1] ^ tmp[2] ^ col[3] ^ tmp[3];
      state[i][3][j] = col[0] ^ tmp[0] ^ col[1] ^ col[2] ^ tmp[3];
    }
  }
}
