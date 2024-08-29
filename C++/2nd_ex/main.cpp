#include "common.h"
#include "decrypt.h"
#include "encrypt.h"

int main() {
  string input_key = init_key();
  string input_text = init_text();

  two_d_matrix round_key = init_key_matrix(input_key);
  three_d_matrix state = init_text_matrix(input_text);
  three_d_matrix ext_keys;

  key_exp(round_key, ext_keys);
  xor_matricies(ext_keys[0], state);

  for (size_t i = 1; i < Nr; i++) {
    sub_bytes(state);
    shift_left(state);
    mix_columns(state);
    xor_matricies(ext_keys[i], state);
  }

  sub_bytes(state);
  shift_left(state);
  xor_matricies(ext_keys[Nr], state);

  cout << "Cipher text: ";
  print_text(state);

  xor_matricies(ext_keys[Nr], state);

  for (int i = Nr - 1; i >= 1; i--) {
    shift_right(state);
    inv_sub_bytes(state);
    xor_matricies(ext_keys[i], state);
    inv_mix_columns(state);
  }

  shift_right(state);
  inv_sub_bytes(state);
  xor_matricies(ext_keys[0], state);

  cout << "Original text: ";
  print_text(state);

  return 0;
}
