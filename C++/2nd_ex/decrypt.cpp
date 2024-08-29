#include "decrypt.h"

void inv_sub_bytes(three_d_matrix &state) {
  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      for (size_t col = 0; col < Nb; col++) {
        state[i][row][col] =
            invs_box[state[i][row][col] / 16][state[i][row][col] % 16];
      }
    }
  }
}

void shift_right(three_d_matrix &state) {
  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t row = 0; row < Nk; row++) {
      rotate(state[i][row].rbegin(), state[i][row].rbegin() + row,
             state[i][row].rend());
    }
  }
}

unsigned char gmul(unsigned char a, unsigned char b) {
  unsigned char p = 0;
  unsigned char senior_bit = 0;
  for (int i = 0; i < 8; i++) {
    if (b & 1) {
      p ^= a;
    }
    senior_bit = a & 0x80;
    a <<= 1;
    if (senior_bit) {
      a ^= 0x1B;
    }
    b >>= 1;
  }
  return p;
}

void inv_mix_columns(three_d_matrix &state) {
  size_t blocks = state.size();
  vector<unsigned char> col(Nb);

  for (size_t i = 0; i < blocks; i++) {
    for (size_t j = 0; j < Nb; j++) {

      for (size_t k = 0; k < Nb; k++) {
        col[k] = state[i][k][j];
      }

      state[i][0][j] = gmul(col[0], 0x0e) ^ gmul(col[1], 0x0b) ^
                       gmul(col[2], 0x0d) ^ gmul(col[3], 0x09);
      state[i][1][j] = gmul(col[0], 0x09) ^ gmul(col[1], 0x0e) ^
                       gmul(col[2], 0x0b) ^ gmul(col[3], 0x0d);
      state[i][2][j] = gmul(col[0], 0x0d) ^ gmul(col[1], 0x09) ^
                       gmul(col[2], 0x0e) ^ gmul(col[3], 0x0b);
      state[i][3][j] = gmul(col[0], 0x0b) ^ gmul(col[1], 0x0d) ^
                       gmul(col[2], 0x09) ^ gmul(col[3], 0x0e);
    }
  }
}
