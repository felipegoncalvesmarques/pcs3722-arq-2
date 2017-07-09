#include "systemc.h"
#include "jpec.h"
#include <stdint.h>

const float coeff[7] = {
	0.49039, 0.46194, 0.41573, 0.35355,
	0.27779, 0.19134, 0.09755
};

// Hello_world is module name
SC_MODULE (jpec_enc_block_dct) {

  sc_in<uint8_t> block[BLOCK_SIZE];
  sc_in<uint8_t> width, height;
  sc_out<float> dct_block[BLOCK_SIZE];

  float tmp[BLOCK_SIZE];

  SC_CTOR (jpec_enc_block_dct) {
    SC_METHOD(inc_func);
    sensitive << width << height;
    for (int i = 0; i < BLOCK_SIZE; i++) {
      sensitive << block[i];
    }
  }

  void inc_func() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      dct_block[i].write(0.1);
    }
  }
};

