#include "common.h"
#include "decrypt.h"
#include "encrypt.h"

int main() {
  string input_key = "Thats my Kung Fu";
  string input_message = "Two One Nine Two";
  /*tie(input_key, input_message) = init_key_text();*/

  two_d_matrix key;
  three_d_matrix text;

  tie(key, text) = init_matricies(input_key, input_message);
  print_matricies_hex(key, text);

  key_exp(key);
  cout << endl;
  print_matricies_hex(key, text);
  return 0;
}
