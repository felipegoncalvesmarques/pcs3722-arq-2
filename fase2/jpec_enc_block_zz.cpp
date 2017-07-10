#include "systemc.h"
#include "jpec.h"
#include <stdint.h>

const int jpec_zz[64] = {
	 0,  1,  8, 16,  9,  2,  3, 10,
	17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
};

// Hello_world is module name
SC_MODULE (jpec_enc_block_zz) {

  sc_in<int> quant[BLOCK_SIZE];
  sc_out<int> zz_block[BLOCK_SIZE];
  sc_out<int> len;

  SC_CTOR (jpec_enc_block_zz) {
    SC_METHOD(inc_func);
    for (int i = 0; i < BLOCK_SIZE; i++) {
      sensitive << quant[i];
    }
  }

  void inc_func() {
    int i_len = 0;
    for (int i = 0; i < BLOCK_SIZE; i++) {
      zz_block[i].write(quant[jpec_zz[i]].read());
      i_len = i + 1;
    }
    len.write(i_len);
  }

};

