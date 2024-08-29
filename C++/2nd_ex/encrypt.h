#ifndef ENCRYPT_H // ENCRYPT_H
#define ENCRYPT_H

#include "common.h"

void sub_bytes(three_d_matrix &);
void shift_left(three_d_matrix &);
void mix_columns(three_d_matrix &);

#endif // ENCRYPT_H
