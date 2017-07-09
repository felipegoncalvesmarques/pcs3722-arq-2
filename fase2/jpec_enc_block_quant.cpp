#include "systemc.h"
#include "jpec.h"
#include <stdint.h>

const float coeff[7] = {
	0.49039, 0.46194, 0.41573, 0.35355,
	0.27779, 0.19134, 0.09755
};

// Hello_world is module name
SC_MODULE (jpec_enc_block_quant) {

  sc_in<float> dct[BLOCK_SIZE];
  sc_in<int> dqt[BLOCK_SIZE];
  sc_out<float> quant[BLOCK_SIZE];

  float tmp[BLOCK_SIZE];

  SC_CTOR (jpec_enc_block_quant) {
    SC_METHOD(inc_func);
    for (int i = 0; i < BLOCK_SIZE; i++) {
      sensitive << dct[i];
      sensitive << dqt[i];
    }
  }

  void inc_func() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
      quant[i].write(dct[i].read()/dqt.read());
    }
  }
};

