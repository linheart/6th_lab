#include "common.h"
#include "decrypt.h"
#include "encrypt.h"

int main() {
  string input_key = "Thats my Kung Fu";
  string input_message = "Two One Nine Two";

  two_d_matrix round_key = init_key_matrix(input_key);
  three_d_matrix state = init_text_matrix(input_message);
  three_d_matrix ext_keys;

  key_exp(round_key, ext_keys);

  for (size_t i = 0; i < Nr - 1; i++) {
    xor_matricies(ext_keys[i], state);
    sub_bytes(state);
    shift_left(state);
    mix_columns(state);
  }

  xor_matricies(ext_keys[Nr - 1], state);
  sub_bytes(state);
  shift_left(state);
  xor_matricies(ext_keys[Nr], state);

  size_t blocks = state.size();
  for (size_t i = 0; i < blocks; i++) {
    for (size_t j = 0; j < Nb; j++) {
      for (size_t k = 0; k < Nb; k++) {
        cout << hex << static_cast<int>(state[i][k][j]) << ' ';
      }
    }
  }

  return 0;
}
